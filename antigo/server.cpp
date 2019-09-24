#include <iostream>
#include "socket.h"



bool ServerSocket::connected = false;


ServerSocket & ServerSocket::tcpConnection (const int sock_domain = PF_INET) {
  static ServerSocket instance;
  if (instance.connection) delete instance.connection;
  instance.sock_domain = sock_domain;
  instance.connection = new types::TCPSocket(sock_domain);

  return instance;
}

ServerSocket & ServerSocket::udpConnection (const int sock_domain = PF_INET) {
  static ServerSocket instance;
  if (instance.connection) delete instance.connection;
  instance.sock_domain = sock_domain;
  instance.connection = new types::UDPSocket(sock_domain);

  return instance;
}


int ServerSocket::connectSocket (const int PORT, const int BACKLOG_QUEUE_SIZE = 5) {

  if (!connected) {
    // int socket_fd = this->connection->getSocketFD();

    // close(socket_fd);

    // bzero((char *) &this->server_addr, sizeof(this->server_addr));

    // this->server_addr.sin_family = sock_domain;
    // this->server_addr.sin_port = this->port_number =  htons(PORT);
    // // ip da maquina que o servidor está rodando
    // this->server_addr.sin_addr.s_addr = INADDR_ANY;


    // if (bind(socket_fd, 
    //         (struct sockaddr*) &this->server_addr, 
    //         sizeof (this->server_addr)) < 0) {

    //           std::cerr << "Erro no binding" << std::endl;
    //           throw "ERROR: Erro no binding";
    //           return -1;
    // }

    // listen(socket_fd, BACKLOG_QUEUE_SIZE);

    connected = true;
  }

  return 0;
}

int ServerSocket::waitConnection () {
  int response_fd;


  try {
    response_fd = this->connection->waitConnection();
  } catch (char * e) {
    throw e;
  }

  return response_fd;
}

std::string ServerSocket::readMessage (int SOURCE_SOCKFD, size_t SIZE = 1024) {
  
  std::string response;

  try {
    response = this->connection->readMessage(SOURCE_SOCKFD, SIZE);
  } catch (char * e) {
    throw e;
  }

  return response;
}

int ServerSocket::sendMessage (int RECEIVER_SOCKFD, const std::string MESSAGE) {
  int response;

  try {
    response = this->connection->sendMessage(RECEIVER_SOCKFD, MESSAGE);
  } catch (char * e) {
    throw e;
  }

  return response;
  // int sended_bytes = write(RECEIVER_SOCKFD, MESSAGE.c_str(), MESSAGE.length);

  // if (sended_bytes < 0) {
  //   std::cerr << "Erro ao fazer a escrita no socket" << std::endl;
  //   throw "ERROR: Erro ao fazer a escrita no socket";
  // }

  // return 0;
}

