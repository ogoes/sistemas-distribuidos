#include <iostream>
#include <string>
#include "socket.h"

using namespace types;


int SocketType::connectSocket (const int PORT) {
  int socket_fd = this->sock_fd;

  close(socket_fd);

  bzero((char *) &this->server_addr, sizeof(this->server_addr));

  this->server_addr.sin_family = this->sock_domain;
  this->server_addr.sin_port = this->port_number =  htons(PORT);
  // ip da maquina que o servidor está rodando
  this->server_addr.sin_addr.s_addr = INADDR_ANY;


  if (bind(socket_fd, 
          (struct sockaddr*) &this->server_addr, 
          sizeof (this->server_addr)) < 0) {

            std::cerr << "Erro no binding" << std::endl;
            throw "ERROR: Erro no binding";
            return -1;
  }

  return 0;
}

TCPSocket::TCPSocket (const int sock_domain) {
  close(sock_fd);
  sock_fd = socket(sock_domain, SOCK_STREAM, 0); // cria o socket
  if (sock_fd == -1) {
    std::cerr << "Erro ao criar socket TCP" << std::endl;
    throw "ERROR: Erro ao criar socket TCP";
  }
}
std::string TCPSocket::readMessage (int SOURCE_SOCKFD, size_t SIZE) {
  char buffer[SIZE];

  bzero(buffer, SIZE);
  int readed_bytes = read(SOURCE_SOCKFD, buffer, SIZE - 1);

  if (readed_bytes < 0) {
    std::cerr << "Erro ao fazer a leitura do socket" << std::endl;
    throw "ERROR: Erro ao fazer a leitura do socket";
  }

  return std::string(buffer);
}
int TCPSocket::sendMessage (int destination_fd, const std::string message) {}
int TCPSocket::connectTCPSocket (const int PORT, const int BACKLOG_QUEUE_SIZE = 5) {
  int response;
  try {
    response = connectSocket (PORT);
  } catch (char * e) {
    throw e;
  }
  listen(sock_fd, BACKLOG_QUEUE_SIZE);
  return 0;
}

int TCPSocket::waitConnection () {
  struct sockaddr_in source_addr;
  socklen_t source_sock_len = sizeof(source_addr);

  int socket_fd = this->sock_fd;


  int source_sockfd = accept(socket_fd,
                            (struct sockaddr *) &source_addr, 
                            &source_sock_len);

  if (source_sockfd < 0) {
    std::cerr << "Erro ao aceitar conexao" << std::endl;
    throw "ERROR: Erro ao aceitar conexao"; 
  }

  return source_sockfd;
}


UDPSocket::UDPSocket (const int sock_domain) {
  close(sock_fd);
  sock_fd = socket(sock_domain, SOCK_DGRAM, 0); // cria o socket
  if (sock_fd == -1) {
    std::cerr << "Erro ao criar socket UDP" << std::endl;
    throw "ERROR: Erro ao criar socket UDP";
  }
}
std::string UDPSocket::readMessage (int SOURCE_SOCKFD, size_t SIZE) {

}
int UDPSocket::sendMessage (int destination_fd, const std::string message) {
  
}
