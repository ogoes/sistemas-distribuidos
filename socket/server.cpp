#include "socket.h"


ServerSocket::ServerSocket (unsigned int PORT, io_context & context, tcp protocol): acceptor(context, tcp::endpoint(protocol, PORT)), socket(context) {
  this->tcp_protocol = protocol;
  this->PORT = PORT;
}


tcp::socket ServerSocket::acceptConnetion () {
  return this->acceptor.accept();
}

std::string ServerSocket::readMessage (tcp::socket & source_socket) {

  char buffer[1024];

  boost::system::error_code error;
  size_t length = source_socket.read_some(boost::asio::buffer(buffer), error);

  if (error)
    throw boost::system::system_error(error); // outro erro


  return std::string(buffer);
}

void ServerSocket::sendMessage (tcp::socket & destination_socket, const std::string message) {
  boost::asio::write(destination_socket, boost::asio::buffer(message.c_str(), message.size()));
}
