#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// socket includes
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "./protocol_buffer/handler.h"

#define SockAddress struct sockaddr
#define SockIn struct sockaddr_in

enum Representation { PROTOCOL_BUFFER = 1, JSON, XML };
enum Connection { CRUD = 1, NOTAS, ALUNOS, DISCIPLINAS, CLOSE };

typedef struct {
  int sockFd;
  SockIn in;
  int inLen;
} SockAttr;

typedef struct {
  int connection;             // CRUD = 1, NOTAS, ALUNOS, DISCIPLINAS, CLOSE
  int requestRepresentation;  // PROTOCOL_BUFFER(1), JSON(2), XML(3)
  unsigned int size;
  char *requestData;
} RequestHeader;

typedef struct {
  unsigned int responseSize;
  char *responseData;
} ResponseHeader;

RequestHeader *unwrapRequest(char *requestData) {
  unsigned char *request = (unsigned char *)requestData;
  int byteBegin = 0;

  int connection = (int)request[byteBegin++];
  int requestRepresentation = (int)request[byteBegin++];

  int HEXsize3 = (int)request[byteBegin++];
  int HEXsize2 = (int)request[byteBegin++];
  int HEXsize1 = (int)request[byteBegin++];
  int HEXsize0 = (int)request[byteBegin++];

  int size = (HEXsize3 << 24) | (HEXsize2 << 16) | (HEXsize1 << 8) | HEXsize0;

  RequestHeader *req = (RequestHeader *)malloc(sizeof(RequestHeader));

  if (size > 0) {
    req->requestData = (char *)calloc(size, sizeof(char));
  } else {
    req->requestData = nullptr;
  }
  req->connection = (Connection)connection;
  req->size = size;
  req->requestRepresentation = requestRepresentation;

  memcpy(req->requestData, request + byteBegin, size);

  return req;
}

ResponseHeader *unwrapResponse(const char *responseData) {
  unsigned char *response = (unsigned char *)responseData;

  int byteBegin = 0;

  int HEXsize3 = (int)response[byteBegin++];
  int HEXsize2 = (int)response[byteBegin++];
  int HEXsize1 = (int)response[byteBegin++];
  int HEXsize0 = (int)response[byteBegin++];

  unsigned int size =
      (HEXsize3 << 24) | (HEXsize2 << 16) | (HEXsize1 << 8) | (HEXsize0 << 0);

  ResponseHeader *res = (ResponseHeader *)malloc(sizeof(ResponseHeader));
  res->responseSize = size;
  res->responseData = (char *)calloc(res->responseSize, sizeof(char));

  memcpy(res->responseData, response + byteBegin, res->responseSize);

  // free((char *)responseData);
  return res;
}

void clientHandler(SockAttr client) {
  int buffer_size = 1024 * 64;  // 64KB
  char buffer[buffer_size + 1];
  bzero(buffer, buffer_size);

  read(client.sockFd, buffer, buffer_size);

  RequestHeader *req = unwrapRequest(buffer);

  const char *(*responseFunction)(int, char *);

  char *responseData;
  while (req->connection != CLOSE) {  // 0 -> close connection

    switch (req->requestRepresentation) {
      case PROTOCOL_BUFFER:
        // chama lib de protocol buffer
        responseFunction = PBHandler::middleware;
        break;
      case JSON:
        // chama lib de json
        // responseFunction = json::middleware;
        break;
      case XML:
        // chama lib de xml
        // responseFunction = xml::middleware;
        break;
      default:
        break;
    }

    const char *responseData =
        responseFunction(req->connection, req->requestData);

    ResponseHeader *res = unwrapResponse(responseData);

    write(client.sockFd, res->responseData, res->responseSize);

    free(res->responseData);
    free(res);

    free(req->requestData);
    free(req);

    bzero(buffer, buffer_size);
    read(client.sockFd, buffer, buffer_size);
    req = unwrapRequest(buffer);
  }

  std::cout << "closed" << std::endl;
  if (req->requestData) free(req->requestData);
  if (req) free(req);
  close(client.sockFd);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Modo de usar: ./server PORT" << std::endl;
    exit(1);
  }

  Database::open("server.db");

  Curso *C = new Curso(1, "BCC");
  Database::exec(C->creationSql().c_str());
  std::string (*function)(std::string) = Curso::retrieveSql;

  Disciplina *D =
      new Disciplina("TESTE", "Testando com o cu na mao", "eu mermo", 1);
  Database::exec(D->creationSql().c_str());

  Aluno *A = new Aluno(1921924, "Otavio", 6, 1);
  Database::exec(A->creationSql().c_str());

  int PORT = atoi(argv[1]);

  SockAttr server;
  server.inLen = sizeof(server.in);

  SockAttr client;

  server.sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (server.sockFd == -1) {
    std::cerr << "Erro ao criar o socket do servidor" << std::endl;
    exit(1);
  }
  bzero(&(server.in), server.inLen);

  server.in.sin_family = AF_INET;
  server.in.sin_addr.s_addr = htonl(INADDR_ANY);
  server.in.sin_port = htons(PORT);

  if ((bind(server.sockFd, (SockAddress *)&(server.in), server.inLen))) {
    close(server.sockFd);
    std::cerr << "Erro ao executar o bind" << std::endl;
    exit(1);
  }

  if ((listen(server.sockFd, 10))) {
    std::cerr << "Erro no listen" << std::endl;
    exit(1);
  }

  std::cout << "Server running at " << PORT << std::endl;

  client.inLen = sizeof(client.in);
  while (true) {
    client.sockFd = accept(server.sockFd, (SockAddress *)&(client.in),
                           (unsigned int *)&client.inLen);
    if (client.sockFd < 0)
      std::cout << "Erro ao aceitar nova conexão" << std::endl;

    std::thread(clientHandler, client).detach();
  }

  return 0;
}
