#include <iostream>
#include "socket.h"



int main (const int argc, const char * argv[]) {

  if (argc != 2) {
    std::cerr << "Modo de usar: server PORT" << std::endl;
    return 1;
  }

  ServerSocket * server = ServerSocket::TCP((unsigned int)std::atoi(argv[1]));

  std::cout << "Server running at " << argv[1] << std::endl;

  tcp::socket client = server->acceptConnetion();

  char  message[1024];

  do {

    memset(message, 0, sizeof message);1
    std::string recv = server->receiveMessage(client);
    std::cout << recv << std::endl << "==> ";
    std::cin.getline(message, 1024);
    server->sendMessage(client, message);

  } while (strcmp(message, "SAIR") != 0);
  client.close();
  return 0;
}
