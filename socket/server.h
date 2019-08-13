#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class ServerSocket {
	private:
		static ServerSocket* server; // singleton
		ServerSocket();

		static bool created;
		static bool connected;

		int port_number;
		int sock_fd;
		int new_sock_fd;
		int client_size;

		static int sock_domain;
		static int sock_type;

		struct sockaddr_in server_addr, client_addr;

	public:
		static void tcpConnection(); // define o tipo de conexao
		static void udpConnection();

		int createSocket(); // inicia socket
		int connectSocket(const int PORT); 

	protected:
};

