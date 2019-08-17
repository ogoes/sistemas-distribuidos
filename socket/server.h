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


		static bool connected;

		uint16_t port_number;
		int sock_fd;
		int new_sock_fd;

		static int sock_domain;
		static int sock_type;

		struct sockaddr_in server_addr;


		/**
		 * Retorne 0 se tudo ocorrer bem, lance uma excecao caso contrario
		*/
		int createSocket(); // inicia socket

	public:
		virtual ~ServerSocket();

		static ServerSocket * tcpConnection(); // define o tipo de conexao
		static ServerSocket * udpConnection();


		

		/**
		 * Retorne 0 se tudo ocorrer bem, lance uma excecao caso contrario
		 *
		 * @params
		 *	!PORT: porta onde o servidor estara disponivel
		 *  [BACKLOG_QUEUE_SIZE=5]: quantidade de conexoes permitidas, padrao 5
		 */
		int connectSocket(const int, const int);

		/**
		 * Retorne o sockfd conectado
		 */
		int waitConnection();

		/**
		 * Retorne a mensagem recebida
		 * 
		 * @params
		 *  !SOURCE_SOCKFD: file descriptor do socket que enviara a mensagem
		 *  [SIZE=1024]: tamanho em bytes que serao lidos
		 */
		std::string readMessage(int , size_t);

		/**
		 * Retorne 0 se der certo, lance uma excecao caso contrario
		 * 
		 * @params
		 *  !RECEIVER_SOCKFD: file descriptor do socket que recebera a mensagem
		 *  !MESSAGE: mensagem que será transmitida
		 */
		int sendMessage(int, const std::string);

	protected:
};

