#include "socket.h"

TCPSocket::~TCPSocket() {
  
}
TCPSocket::TCPSocket (io_context & context, tcp type, unsigned int PORT): acceptor(context, tcp::endpoint(type, PORT)), socket(context), resolver(context) {}
tcp::socket TCPSocket::acceptConnetion () {
  return this->acceptor.accept();
}
std::string TCPSocket::receiveMessage (tcp::socket & source_socket) {

  char buffer[4096];

  memset(buffer, 0, sizeof buffer);
  boost::system::error_code error;
  size_t length = source_socket.read_some(boost::asio::buffer(buffer), error);

  if (error)
    throw boost::system::system_error(error); // outro erro


  return std::string(buffer);
}
void TCPSocket::sendMessage (tcp::socket & destination_socket, const std::string message) {
  boost::asio::write(destination_socket, boost::asio::buffer(message.c_str(), message.size()));
}

tcp::socket ServerSocket::acceptConnetion () {
  if (socket_p == protocols::UDP) throw "ERRO: UDP protocol doesn't need to accept connections";

  return this->tcp_socket->acceptConnetion();
}
std::string ServerSocket::receiveMessage (tcp::socket & source_socket) {
  return this->tcp_socket->receiveMessage(source_socket);
}
void ServerSocket::sendMessage (tcp::socket & destination_socket, const std::string message) {
  this->tcp_socket->sendMessage(destination_socket, message);
}
ServerSocket::ServerSocket () {}
ServerSocket::~ServerSocket () {
  if (this->socket_p == protocols::TCP)
    delete this->tcp_socket;
  else
    delete this->udp_socket;
}

ServerSocket * ServerSocket::TCP (unsigned int PORT) {
  ServerSocket * instance = new ServerSocket();

  instance->tcp_socket = new TCPSocket(instance->_iocontext, tcp::v4(), PORT);
  instance->socket_p = protocols::TCP;
  return instance;
}

ServerSocket * ServerSocket::UDP (unsigned int PORT, udp type = udp::v4()) {
  // ServerSocket * instance = new ServerSocket();

  // instance->TCPSocket = new UDPSocket(instance->_iocontext, type, PORT);
  // instance->socket_p = protocols::UDP;
  // return instance;
  return NULL;
}
