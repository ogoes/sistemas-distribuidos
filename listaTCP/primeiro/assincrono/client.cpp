#include "../../../socket/socket.h"
#include <cstdio>
#include <functional>
#include <sys/ioctl.h>
#include <thread>
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

void receiveFunction (ClientSocket * client) {
  std::string recv;

  do {
    try {
      recv.clear ();
      recv = client->receiveMessage ();
    } catch (...) {
      std::cout << "Conexão encerrada" << std::endl;
      return;
    }
    showReceivedMessage (recv);
    // std::cout << recv << std::endl;
  } while (recv != "SAIR");
  exit (0);
}

void sendFunction (ClientSocket * client) {
  std::string message;

  do {
    std::getline (std::cin, message);
    try {
      client->sendMessage (message);
    } catch (...) {
      std::cout << "Conexão Finalizada" << std::endl;
      return;
    }
  } while (message != "SAIR");
}

int main (int argc, char * argv[]) {

  if (argc != 3) {
    std::cerr << "Erro: modo de usar --> ./client HOST PORT";
    exit (1);
  }

  ClientSocket * socket = ClientSocket::TCP (argv[1], argv[2]);

  std::thread receive (receiveFunction, socket);
  std::thread send (sendFunction, socket);

  send.join ();
  receive.join ();

  socket->finish ();
  delete socket;

  return 0;
}
