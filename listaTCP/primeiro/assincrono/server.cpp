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

void receiveFunction (ServerSocket * server, tcp::socket & socket) {
  std::string recv;

  do {
    try {
      recv.clear ();
      recv = server->receiveMessage (socket);
    } catch (...) {
      std::cout << "Conexão finalisada" << std::endl;
      return;
    }
    showReceivedMessage (recv);
    // std::cout << "Recebido: " << recv << std::endl;
  } while (recv != "SAIR");
  exit (0);
}

void sendFunction (ServerSocket * server, tcp::socket & socket) {
  std::string message;
  do {
    std::getline (std::cin, message);
    try {
      server->sendMessage (socket, message);
    } catch (...) {
      std::cout << "Conexão finalisada" << std::endl;
      return;
    }
  } while (message != "SAIR");
}

int main (int argc, char * argv[]) {

  if (argc != 2) {
    std::cerr << "Erro: Modo de usar -> ./server PORT";
    exit (1);
  }

  ServerSocket * server = ServerSocket::TCP (std::atoi (argv[1]));

  std::cout << "Servidor rodando na porta " << argv[1] << std::endl;
  tcp::socket client = server->acceptConnection ();

  std::thread receive (receiveFunction, server, std::ref (client));

  std::thread send (sendFunction, server, std::ref (client));

  receive.join ();
  send.join ();

  client.close ();
  server->finish ();

  client.close ();
}
