#include "socket.h"


ClientSocket::ClientSocket (io_context & context): connected_socket(context), resolver(context) {
}

tcp::socket & ClientSocket::connect (const char * HOST, const char * PORT) {
  boost::asio::connect(this->connected_socket, this->resolver.resolve(HOST, PORT));
  return connected_socket;
}

std::string ClientSocket::readMessage () {
  const unsigned int size = 4096;
  char buffer[size];

  boost::system::error_code error;  
  size_t length = this->connected_socket.read_some(boost::asio::buffer(buffer, size), error);

  if (error)
    throw boost::system::system_error(error); // outro erro

  return std::string(buffer);
}

void ClientSocket::sendMessage (std::string message) {
  boost::asio::write(this->connected_socket, boost::asio::buffer(message.c_str(), message.length()));
}

void ClientSocket::finish () {
  this->connected_socket.close();
}
