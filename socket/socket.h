#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_context;
using boost::asio::io_service;

class ServerSocket {
private: // attributes
  
  tcp tcp_protocol = tcp::v4();
  tcp::acceptor acceptor;

  tcp::socket socket;

  unsigned int PORT;


public: // statics
  ServerSocket(unsigned int /* PORT */, io_context &, tcp /* protocol */);

public:
  tcp::socket acceptConnetion ();
  std::string readMessage (tcp::socket /* source_socket */, const int /* SIZE */);
  void sendMessage (tcp::socket /* destonation_socket */, const std::string /* message */);


};


class ClientSocket {

};