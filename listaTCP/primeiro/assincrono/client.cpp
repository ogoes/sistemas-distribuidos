#include "../../../socket/socket.h"
#include <functional>
#include <thread>

int main (int argc, char * argv[]) {

  if (argc != 3) {
    std::cerr << "Erro: modo de usar --> ./client HOST PORT";
    exit (1);
  }

  ClientSocket * socket = ClientSocket::TCP (argv[1], argv[2]);

  std::thread receive (
      [](ClientSocket * client) {
        std::string recv;
        recv = client->receiveMessage ();
        std::cout << recv << std::endl;
      },
      socket);

  std::thread send (
      [](ClientSocket * client) {
        char message[1024];
        while (true) {

          memset (message, 0, sizeof message);
          std::cin.getline (message, 1024);
          client->sendMessage (message);
        }
      },
      socket);

  // send.detach ();
  // receive.detach ();
  //
  send.join ();
  receive.join ();

  return 0;
}
