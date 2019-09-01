#include "../../../socket/socket.h"
#include <string>

int main (int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "Erro: Modo de usar ~~> ./client <HOST> <PORT>" << std::endl;
    exit (1);
  }

  ClientSocket * socket = ClientSocket::TCP (argv[1], argv[2]);

  char message[1024];
  std::string recv;

  do {
    memset (message, 0, 1024);
    std::cout << "~> ";
    std::cin.getline (message, 1024);

    socket->sendMessage (message);

    try {
      recv.clear ();
      std::cout << recv << std::endl;
      recv = socket->receiveMessage ();
      std::cout << recv << std::endl;
    } catch (std::exception & e) {
      std::cout << "Conexão Finalisada" << std::endl;
      break;
    }

  } while (recv != "SAIR" || strcmp (message, "SAIR") == 0);

  socket->finish ();

  return 0;
}
