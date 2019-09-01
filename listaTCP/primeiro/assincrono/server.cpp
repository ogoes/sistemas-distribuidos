#include "../../../socket/socket.h"
#include <functional>
#include <thread>

int main (int argc, char * argv[]) {

  if (argc != 2) {
    std::cerr << "Erro: Modo de usar -> ./server PORT";
    exit (1);
  }

  ServerSocket * server = ServerSocket::TCP (std::atoi (argv[1]));

  std::cout << "Servidor rodando na porta " << argv[1] << std::endl;
  tcp::socket client = server->acceptConnection ();

  std::thread (
      [](ServerSocket * server, tcp::socket & socket) {
        std::string recv;

        // do {
        recv = server->receiveMessage (socket);
        std::cout << "Recebido: " << recv << std::endl;

        // std::terminate ();
      },
      server,
      std::ref (client))
      .detach ();

  std::thread send (
      [](ServerSocket * server, tcp::socket & socket) {
        char message[1024];
        memset (message, 0, sizeof message);

        std::cout << "Enviar: " << std::endl;
        std::cin.getline (message, sizeof message);

        while (/*strcmp (message, "SAIR") != 0*/ true) {
          server->sendMessage (socket, message);
          memset (message, 0, sizeof message);
          std::cout << "Enviar: " << std::endl;
          std::cin.getline (message, sizeof message);
        }

        // std::terminate ();
      },
      server,
      std::ref (client));

  std::cout << "asdasd" << std::endl;

  // receive.join();
  send.join ();

  client.close ();
}
