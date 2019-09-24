#include "../../socket/socket.h"
#include <cstdio> // para printar
#include <functional>
#include <iostream>
#include <sys/ioctl.h> // para printar
#include <thread>
#include <unistd.h> // para printar

void showReceivedMessage (std::string message) {
  struct winsize size;
  ioctl (STDOUT_FILENO, TIOCGWINSZ, &size);

  int spacesCount = message.length () - size.ws_col;
  spacesCount     = spacesCount > 0 ? spacesCount : -spacesCount;

  std::cout << std::endl;
  for (int i = 0; i < spacesCount; ++i)
    std::cout << ' ';
  std::cout << message << std::endl;
}

int main (int argc, char * argv[]) {

  if (argc != 3) {
    std::cerr << "O endereço do HOST e a PORTA devem ser informadas"
              << std::endl;
    return 1;
  }

  ClientSocket * client = ClientSocket::TCP (argv[1], argv[2]);

  std::string message;
  std::string recv;
  do {
    std::cout << "--> ";
    message.clear ();
    std::getline (std::cin, message);

    if (message == "PARAR") break;
    std::cout << "asdasd";
    client->sendMessage (message);

    try {
      recv = client->receiveMessage ();
    } catch (...) { break; }
  } while (true);

  client->finish ();

  return 8;
}
