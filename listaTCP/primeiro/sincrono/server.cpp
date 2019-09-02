#include "../../../socket/socket.h"
#include <cstdio>
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
  if (argc != 2) {
    std::cerr << "Erro, modo de usar ~~> ./server <PORT> " << std::endl;
    exit (1);
  }

  ServerSocket * server = ServerSocket::TCP (std::atoi (argv[1]));

  std::cout << "Server running at " << argv[1] << std::endl;

  tcp::socket client = server->acceptConnection ();

  std::string message;

  std::string recv = server->receiveMessage (client);

  while (recv != "SAIR") {

    // std::cout << recv << std::endl;
    showReceivedMessage (recv);

    std::getline (std::cin, message);

    server->sendMessage (client, message);

    try {
      recv = server->receiveMessage (client);
    } catch (...) {
      std::cout << "Conexão Finalisada" << std::endl;
      break;
    }
  }

  server->finish ();
  client.close ();
  return 0;
}
