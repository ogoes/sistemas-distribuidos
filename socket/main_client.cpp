#include "socket.h"


int main (const int argc, const char * argv[]) {

  if (argc != 3) {
    std::cerr << "Modo de usar: client HOST PORT" << std::endl;
    return 1;
  }

  io_context context;
  ClientSocket  * client = new ClientSocket(context);
  client->connect(argv[1], argv[2]);

  char message[1024];

  while (true) {
    std::cout << "==> ";
    std::cin.getline(message, 1024);
    client->sendMessage(message);

    std::string recv = client->readMessage();
    std::cout << recv << std::endl;
  }


  return 0;
}
