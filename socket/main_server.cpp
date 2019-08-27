#include <iostream>
#include "socket.h"



int main (const int argc, const char * argv[]) {

  if (argc != 2) {
    std::cerr << "Modo de usar: server PORT" << std::endl;
    return 1;
  }


  io_context io_context;
  ServerSocket * server = new ServerSocket(std::atoi(argv[1]), io_context, tcp::v4());

  std::cout << "Server running at " << argv[1] << std::endl;

  tcp::socket client = server->acceptConnetion();

  char  message[1024];
  std::string recv = server->readMessage(client);
  std::cout << recv << std::endl << "==> ";
  std::cin.getline(message, 1024);
  server->sendMessage(client, message);

  client.close();
  return 0;
}