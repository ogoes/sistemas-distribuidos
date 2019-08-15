#include <iostream>
#include "server.h"


ServerSocket * ServerSocket::server = NULL;

int ServerSocket::sock_domain = PF_INET;
int ServerSocket::sock_type = SOCK_STREAM; // padrao tcp

bool ServerSocket::connected = false;


ServerSocket * ServerSocket::tcpConnection () {
  if (!server) server = new ServerSocket();

  sock_type = SOCK_STREAM;

  /**
   * se for necessario mudar o tipo da conexao depois de criada
   * eh preciso criar uma nova conexao
  */
  server->createSocket();
  connected = false;

  return server;
}

ServerSocket * ServerSocket::udpConnection () {
  if (!server) server = new ServerSocket();

  sock_type = SOCK_DGRAM;

  server->createSocket();
  connected = false;

  return server;
}

int ServerSocket::createSocket () {
  if (!server) server = new ServerSocket();

  close(server->sock_fd);
  server->sock_fd = socket(sock_domain, sock_type, 0); // cria o socket
  if (server->sock_fd == -1) {
    std::cerr << "Erro ao criar socket" << std::endl;
    throw "ERROR: Erro ao criar socket";
  }
  
  return 0;
}

int ServerSocket::connectSocket (const int PORT, const int BACKLOG_QUEUE_SIZE = 5) {

  if (!connected) {
    close(this->sock_fd);

    bzero((char *) &this->server_addr, sizeof(server->server_addr));

    this->server_addr.sin_family = sock_domain;
    this->server_addr.sin_port = this->port_number =  htons(PORT);
    // ip da maquina que o servidor está rodando
    this->server_addr.sin_addr.s_addr = INADDR_ANY;


    if (bind(this->sock_fd, 
            (struct sockaddr*) &this->server_addr, 
            sizeof (this->server_addr)) < 0) {

              std::cerr << "Erro no binding" << std::endl;
              throw "ERROR: Erro no binding";
              return -1;
    }

    listen(this->sock_fd, BACKLOG_QUEUE_SIZE);

    connected = true;
  }

  return 0;
}

int ServerSocket::waitConnection () {
  struct sockaddr_in source_addr;
  socklen_t source_sock_len = sizeof(source_addr);

  int source_sockfd = accept(this->sock_fd,
                            (struct sockaddr *) &source_addr, 
                            &source_sock_len);

  if (source_sockfd < 0) {
    std::cerr << "Erro ao aceitar conexao" << std::endl;
    throw "ERROR: Erro ao aceitar conexao"; 
  }

  return source_sockfd;
}

std::string ServerSocket::readMessage (int SOURCE_SOCKFD, size_t SIZE = 1024) {
  char buffer[SIZE];

  bzero(buffer, SIZE);
  int readed_bytes = read(SOURCE_SOCKFD, buffer, SIZE - 1);

  if (readed_bytes < 0) {
    std::cerr << "Erro ao fazer a leitura do socket" << std::endl;
    throw "ERROR: Erro ao fazer a leitura do socket";
  }

  return std::string(buffer);
}

int ServerSocket::sendMessage (int RECEIVER_SOCKFD, const std::string MESSAGE) {
  int sended_bytes = write(RECEIVER_SOCKFD, MESSAGE.c_str(), MESSAGE.length);

  if (sended_bytes < 0) {
    std::cerr << "Erro ao fazer a escrita no socket" << std::endl;
    throw "ERROR: Erro ao fazer a escrita no socket";
  }

  return 0;
}

