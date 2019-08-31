#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

using boost::asio::io_context;



enum protocols { TCP = 1, UDP };



class TCPSocket {
private:

  // tipo de endereçamento usado, padrão IPv4
  tcp tcp_protocol = tcp::v4();

  // necessário para o servidor aceitar conexões
  tcp::acceptor acceptor;

  // identificador do socket
  tcp::socket socket;

  // necessário para o cliente conectar-se com o servidor1
  tcp::resolver resolver;

  unsigned int PORT;

public: //! server

  ~ TCPSocket ();
  tcp::socket acceptConnetion ();
  TCPSocket (io_context & /* context */, tcp /* type */, unsigned int /* PORT */);
  std::string receiveMessage (tcp::socket & /* source_socket */);
  void sendMessage (tcp::socket & /* destination_socket */, const std::string /* message */);


public: //! client
  TCPSocket (io_context & /* context */);
  void connect(const char * /* HOST */, const char * /* PORT */);
  std::string receiveMessage();
  void sendMessage(const std::string /* message */);
};
class UDPSocket {};

/**
 * Classe responsável por criar um servidor que responde por protocolos (TCP/UDP)
 */
class ServerSocket {
private: // attributes

  TCPSocket * tcp_socket;
  UDPSocket * udp_socket;

  // identifica qual protocolo de comunicação (TCP/UDP)
  int socket_p = 0;

  // necessario para a biblioteca
  io_context _iocontext;

  // método construtor privado pois a instŴnciação é feita por métodos fábrica
  ServerSocket ();

  /**
   * Métodos responsáveis por criarem o objeto com base no protocolo de comunicação (TCP/UDP) que 
   * o servidor usará
   * 
   * @param
   * PORT: inteiro que identifica a porta que será "ouvida" pelo servidor
   * [type]: identifica a versão do IP usado (IPv4/IPv6)
   * 
   * @return
   * instância de ServerSocket já configurado
   */
public: // estaticos
  static ServerSocket * TCP (unsigned int /* PORT */);
  static ServerSocket * TCP (unsigned int /* PORT */, tcp & /* type */);
  static ServerSocket * UDP (unsigned int /* PORT */);
  static ServerSocket * UDP (unsigned int /* PORT */, udp  /* type */);

public: // métodos

  // destrutor da classe
  ~ ServerSocket ();

  /**
   * Aceita a conexão de um cliente
   * BLOQUEANTE: A execução do programa é "pausada" até que uma conexão seja estabelecida
   * 
   * @return
   * soquete TCP (Não é necessário para conexões UDP) que identifica o cliente que acabou de conectar-se ao servidor
   * 
   */
  tcp::socket acceptConnetion ();

  /**
   * Recebe uma mensagem de um processo
   * BLOQUEANTE: A execução do programa é "pausada" até que a mensagem seja recebida
   * 
   * @param
   * source_socket: soquete do processo que enviará a mensagem
   * 
   */
  std::string receiveMessage (tcp::socket &/* source_socket */);

  /**
   * Método responsável por enviar uma messagem para o processo conectado com o servidor
   *
   * @param
   * destination_socket: socket do processo que receberá a mensagem
   * message: string contendo a mensagem a ser enviada
   * 
   */
  void sendMessage (tcp::socket & /* destination_socket */, const std::string /* message */);
};



/**
 * Cada instância poderá se comunicar com apenas um servidor
 * Se trata de uma abordagem bloqueante, assim o programa "espera" o recebimento da mensagem
 * Cabe ao programador tratar o multiprocessamento/assincronismo se necessário
 */
class ClientSocket {

private: // atributos

  
  // indica qual protocolo de comunicação a instancia está usando
  int socket_p = 0;

  // necessário para a biblioteca
  io_context context;

  // instancia de um socket tcp
  TCPSocket * tcp_socket;

  // método construtor privado pois existe os métodos fabricas (TCP / UDP)
  ClientSocket ();


public: // métodos

  /**
   * Métodos responsáveis por definir qual protocolo de comunicação (TCP/UDP) a instância usará.
   * 
   * @param
   * const char * HOST: endereço IP (IPv4/IPv6) host que está executando o servidor
   * const char * PORT: porta aberta pelo servidor
   *
   * @return
   * instância de ClientSocket
   *
   * DESIGN PATTERN --> Factory Method
   */
  static ClientSocket * TCP (const char * /* HOST */, const char * /* PORT */);
  static ClientSocket * UDP (const char * /* HOST */, const char * /* PORT */);

  /**
   * Método resposável por receber uma mensagem do servidor conectado
   * BLOQUEANTE: A execução do programa é "pausada" até que a mensagem seja recebida
   *
   * @param
   *
   * @return
   * Uma string contendo a mensagem enviada pelo servidor
   */
  std::string receiveMessage ();

  /**
   * Método responsável por enviar uma mensagem o servidor conectado
   *
   * @param
   * A mensagem a ser enviada: string
   *
   * @return
   *
   */
  void sendMessage (std::string);

  /**
   * Método responsável por finalizar a comunicação entre o soquete cliente e o servidor
   *
   * @param
   *
   * @return
   *
  */
  void finish();
};
