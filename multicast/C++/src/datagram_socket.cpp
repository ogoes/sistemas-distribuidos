#include "datagram_socket.h"

DatagramSocket::DatagramSocket () {
  if ((send_socket = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
    throw "Erro ao criar o socket de envio";
  }

  if ((recv_socket = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
    close (send_socket);
    throw "Erro ao criar o socket";
  }

  sock_in.sin_family = AF_INET;
  sock_in.sin_port   = 6799;

  // sock_in.sin_port        = 0; // qualquer porta dinponível
  sock_in.sin_addr.s_addr = INADDR_ANY;

  if (bind (send_socket, ( struct sockaddr * ) &sock_in, sizeof (sock_in)) <
      0) {
    close (send_socket);
    throw "Erro ao tentar executar o bind da porta ";
  }

  port = -1;

  unsigned int namelen = sizeof (sock_in);
  getsockname (send_socket, ( struct sockaddr * ) &sock_in, &namelen);
  port = sock_in.sin_port;
}
DatagramSocket::~DatagramSocket () {
  close (send_socket);
  close (recv_socket);
}

void DatagramSocket::sendMessage (std::string addr,
                                  int port,
                                  const char * msg) {

  struct sockaddr_in target;

  target.sin_family      = AF_INET;
  target.sin_port        = port;
  target.sin_addr.s_addr = inet_addr (addr.c_str ());

  if (sendto (send_socket,
              msg,
              (strlen (msg) + 1),
              0,
              ( struct sockaddr * ) &target,
              sizeof (target)) < 0) {
    throw "Erro ao enviar mensagem";
  }
}
MessageInformation DatagramSocket::receiveMessage (const int size) {
  MessageInformation message_info;

  struct sockaddr_in sender_sock_in;
  unsigned int sender_addr_size = sizeof (sender_sock_in);

  char buffer[size];

  if (recvfrom (recv_socket,
                buffer,
                sizeof (buffer),
                0,
                ( struct sockaddr * ) &sender_sock_in,
                &sender_addr_size) < 0) {
    throw "eero ao receber mensagem";
  }

  message_info.message_bytes = ( char * ) calloc (size, sizeof (char));
  for (int i = 0; i < size; ++i) {
    message_info.message_bytes[i] = buffer[i];
  }

  message_info.sender_port = ntohs (sender_sock_in.sin_port),
  message_info.sender_address =
      std::string (inet_ntoa (sender_sock_in.sin_addr));

  return message_info;
}

std::string DatagramSocket::getAddress () {
  return std::string (inet_ntoa (sock_in.sin_addr));
}
