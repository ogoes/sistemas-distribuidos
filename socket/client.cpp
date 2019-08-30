#include "socket.h"

TCPSocket::TCPSocket (io_context & context): acceptor(context), socket(context), resolver(context) {
  // free(acceptor);
}
std::string TCPSocket::receiveMessage () {

  const unsigned int size = 4096;
  char buffer[size];

  boost::system::error_code error;  
  size_t length = this->socket.read_some(boost::asio::buffer(buffer, size), error);

  if (error)
    throw boost::system::system_error(error); // outro erro

  return std::string(buffer);
}
void TCPSocket::sendMessage (const std::string message) {
  boost::asio::write(this->socket, boost::asio::buffer(message.c_str(), message.length()));
}
void TCPSocket::connect (const char * HOST, const char * PORT) {
  boost::asio::connect(this->socket, this->resolver.resolve(HOST, PORT));
}
TCPSocket::~TCPSocket() {
  
}



ClientSocket * ClientSocket::TCP (const char * HOST, const char * PORT) {
  ClientSocket * instance = new ClientSocket();

  instance->tcp_socket = new TCPSocket(instance->context);
  instance->tcp_socket->connect(HOST, PORT);
  instance->socket_p = protocols::TCP;

  return instance;
}
// ClientSocket * ClientSocket::TCP (const char * /* HOST */, const char * /* PORT */, tcp /* type */) {}
// ClientSocket * ClientSocket::UDP (const char * /* HOST */, const char * /* PORT */) {}
// ClientSocket * ClientSocket::UDP (const char * /* HOST */, const char * /* PORT */, udp /* type */) {}

// ClientSocket::ClientSocket (io_context & context): connected_socket(context), resolver(context) {
// }

// tcp::socket & ClientSocket::connect (const char * HOST, const char * PORT) {
//   boost::asio::connect(this->connected_socket, this->resolver.resolve(HOST, PORT));
//   return connected_socket;
// }

std::string ClientSocket::receiveMessage () {

  if (this->socket_p == protocols::TCP) {
    return this->tcp_socket->receiveMessage();
  }

  return "ASd";
}

void ClientSocket::sendMessage (std::string message) {
  if (this->socket_p == protocols::TCP) this->tcp_socket->sendMessage(message);
}

ClientSocket::ClientSocket () {

}

