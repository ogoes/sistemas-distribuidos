#include "../../../socket/socket.h"
#include <cstdio>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

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
    std::cerr << "Erro: Modo de usar ~~> ./client <HOST> <PORT>" << std::endl;
    exit (1);
  }

  ClientSocket * socket = ClientSocket::TCP (argv[1], argv[2]);

  std::string message;
  std::string recv;

  do {
    std::getline (std::cin, message);

    socket->sendMessage (message);

    try {
      recv = socket->receiveMessage ();
    } catch (...) {
      std::cout << "Conexão Finalisada" << std::endl;
      break;
    }

    showReceivedMessage (recv);

  } while (recv != "SAIR" && message != "SAIR");

  socket->finish ();

  return 0;
}
