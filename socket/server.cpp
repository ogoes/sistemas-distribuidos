#include <iostream>
#include "server.h"


ServerSocket * ServerSocket::server = NULL;

int ServerSocket::sock_domain = PF_INET;
int ServerSocket::sock_type = SOCK_STREAM; // padrao tcp

bool ServerSocket::created = false;
bool ServerSocket::connected = false;


void ServerSocket::tcpConnection () {
  if (!server) server = new ServerSocket();

  sock_type = SOCK_STREAM;

  /*
    * se for necessario mudar o tipo da conexao depois de criada
    * eh preciso criar uma nova conexao
  */
  if (created) server->createSocket();
}

void ServerSocket::udpConnection () {
  if (!server) server = new ServerSocket();

  sock_type = SOCK_DGRAM;

  if (created) server->createSocket();
}

int ServerSocket::createSocket () {
  if (!server) server = new ServerSocket();

  server->sock_fd = socket(sock_domain, sock_type, 0); // cria o socket
  if (server->sock_fd == -1) {
    std::cerr << "Erro ao criar socket" << std::endl;
    exit(1);
  }
  
  created = true;
  return 0;
}

int ServerSocket::connectSocket (const int PORT) {

  if (!server) {
    server = new ServerSocket();
    server->createSocket();
  }

  if (!connected) {

    bzero((char *) &server->server_addr, sizeof(server->server_addr));

    server->server_addr.sin_family = sock_domain;
    server->server_addr.sin_port = htons(PORT);
    // ip da maquina que o servidor está rodando
    server->server_addr.sin_addr.s_addr = INADDR_ANY;


    if (bind(server->sock_fd, 
            (struct sockaddr*) &server->server_addr, 
            sizeof (server->server_addr)) < 0) {

              std::cerr << "Erro no binding" << std::endl;
              exit(1);
    }

    connected = true;
  }
}



int main () {

  


  return 0;
}
