#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


namespace types {

	class SocketType {
		protected: //! methods
			/**
			 * Retorne 0 se tudo ocorrer bem, lance uma excecao caso contrario
			*/
			virtual int createSocket(); // inicia socket
		
			virtual int getSocketFD () = 0;
			int connectSocket (const int /*PORT*/);

		protected: //! attributes
			struct sockaddr_in server_addr;
			int sock_fd;
			int sock_domain;
			uint16_t port_number;

		public:
			virtual int waitConnection();
				/**
			 * Retorne a mensagem recebida
			 * 
			 * @params
			 *  !SOURCE_SOCKFD: file descriptor do socket que enviara a mensagem
			 *  [SIZE=1024]: tamanho em bytes que serao lidos
			 */
			virtual std::string readMessage(int , size_t) = 0;

			/**
			 * Retorne 0 se der certo, lance uma excecao caso contrario
			 * 
			 * @params
			 *  !RECEIVER_SOCKFD: file descriptor do socket que recebera a mensagem
			 *  !MESSAGE: mensagem que será transmitida
			 */
			virtual int sendMessage(int, const std::string) = 0;


	};


	class TCPSocket: public SocketType {
		public:
			TCPSocket (const int);
			~ TCPSocket () {};
			std::string readMessage(int , size_t);
			int sendMessage(int, const std::string);
			int getSocketFD ();

			/**
			 * Retorne o sockfd conectado
			 */
			int waitConnection();

			int connectTCPSocket (const int , const int );

	};


	class UDPSocket: public SocketType {
		public:
			UDPSocket (const int);
			~ UDPSocket () {};
			std::string readMessage(int , size_t);
			int sendMessage(int, const std::string);
			int getSocketFD ();
	};
};




class ServerSocket {
	private:
		types::SocketType * connection = 0;


		static bool connected;

		uint16_t port_number;
		int sock_domain;

		struct sockaddr_in server_addr;


	public:
		virtual ~ServerSocket();

		static ServerSocket & tcpConnection(const int); // define o tipo de conexao
		static ServerSocket & udpConnection(const int);

		/**
		 * Retorne 0 se tudo ocorrer bem, lance uma excecao caso contrario
		 *
		 * @params
		 *	!PORT: porta onde o servidor estara disponivel
		 *  [BACKLOG_QUEUE_SIZE=5]: quantidade de conexoes permitidas, padrao 5
		 */
		int connectSocket(const int, const int);

		std::string ServerSocket::readMessage (int , size_t);
		int ServerSocket::sendMessage (int , const std::string);
		int waitConnection ();

	protected:
};

class ClientSocket {
	private:
		ClientSocket ();
	public:
	protected:

};
