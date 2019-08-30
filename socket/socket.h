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
  tcp tcp_protocol = tcp::v4();
  tcp::acceptor acceptor;

  tcp::socket socket;
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


class ServerSocket {
private: // attributes

  TCPSocket * tcp_socket;
  UDPSocket * udp_socket;

  int socket_p = 0;
  io_context _iocontext;

  ServerSocket ();

public: // statics
  static ServerSocket * TCP (unsigned int /* PORT */);
  static ServerSocket * TCP (unsigned int /* PORT */, tcp & /* type */);
  static ServerSocket * UDP (unsigned int /* PORT */);
  static ServerSocket * UDP (unsigned int /* PORT */, udp /* type */);

public:

  ~ ServerSocket ();
  tcp::socket acceptConnetion ();
  std::string readMessage (tcp::socket &/* source_socket */);
  void sendMessage (tcp::socket & /* destination_socket */, const std::string /* message */);
};


class ClientSocket {

private:

  int socket_p = 0;

  io_context context;

  TCPSocket * tcp_socket;

  ClientSocket ();


public:
  static ClientSocket * TCP (const char * /* HOST */, const char * /* PORT */);
  static ClientSocket * UDP (const char * /* HOST */, const char * /* PORT */);

  std::string receiveMessage ();
  void sendMessage (std::string);
  void finish();
};
