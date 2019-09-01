#include "../../../socket/socket.h"

int main (int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Erro, modo de usar ~~> ./server <PORT> " << std::endl;
    exit (1);
  }

  ServerSocket * server = ServerSocket::TCP (std::atoi (argv[1]));

  std::cout << "Server running at " << argv[1] << std::endl;

  tcp::socket client = server->acceptConnection ();

  char message[1024];
  memset (message, 0, sizeof message);

  std::string recv = server->receiveMessage (client);

  while (recv != "SAIR") {

    memset (message, 0, sizeof message);

    std::cout << recv << std::endl;

    std::cout << "~> ";
    std::cin.getline (message, 1024);

    server->sendMessage (client, message);

    try {
      recv.erase (0, recv.length ());
      recv = server->receiveMessage (client);
    } catch (std::exception & e) {
      std::cout << "Conexão Finalisada" << std::endl;
      break;
    }
  }

  server->finish ();
  client.close ();
  return 0;
}
