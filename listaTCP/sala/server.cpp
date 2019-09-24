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

void clientHandler (ServerSocket * server, tcp::socket & client) {
  std::string recv;

  do {
    try {
      recv = server->receiveMessage (client);
    } catch (...) { break; }

    if (recv == "PARAR") break;

    showReceivedMessage (recv);

    server->sendMessage (client, recv + ":OK");
  } while (true);

  client.close ();
}

int main (int argc, char * argv[]) {
  if (argc != 2) {
    std::cout << "É preciso informar a PORTA" << std::endl;
    return 1;
  }

  ServerSocket * server = ServerSocket::TCP (std::atoi (argv[1]));

  while (true) {
    tcp::socket client = server->acceptConnection ();
    std::thread (clientHandler, server, std::ref (client)).detach ();
  }

  server->finish ();

  return 0;
}
