#include "multicast_socket.h"

MulticastSocket::MulticastSocket (const char * address, int port)
    : port (port), group_addr (address) {

  /**
   * Sender socket
   */

  send_socket = socket (AF_INET, SOCK_DGRAM, 0);
  if (send_socket < 0) throw "Erro ao criar o socket de envio";

  memset (( char * ) &send_sock_in, 0, sizeof (send_sock_in));
  memset (( char * ) &recv_sock_in, 0, sizeof (recv_sock_in));

  send_sock_in.sin_family = recv_sock_in.sin_family = AF_INET;
  send_sock_in.sin_port = recv_sock_in.sin_port = htons (port);
  send_sock_in.sin_addr.s_addr = inet_addr (group_addr.c_str ());

  recv_sock_in.sin_addr.s_addr = htonl (INADDR_ANY);

  recv_socket = socket (AF_INET, SOCK_DGRAM, 0);
  if (recv_socket < 0) {
    close (send_socket);
    throw "Erro ao criar o socket de recebimento";
  }

  u_int yes = 1;
  if (setsockopt (recv_socket,
                  SOL_SOCKET,
                  SO_REUSEADDR,
                  ( char * ) &yes,
                  sizeof (yes)) < 0) {

    close (recv_socket);
    close (send_socket);
    throw "Eero ao espeicficar multiplas instancias na mesma porta";
  }

  if (bind (recv_socket,
            ( struct sockaddr * ) &recv_sock_in,
            sizeof (recv_sock_in)) < 0) {

    close (recv_socket);
    close (send_socket);

    throw "Erro ao executar o bind da porta especificada";
  }
}
MulticastSocket::~MulticastSocket () { leave (); }

void MulticastSocket::join () {

  group.imr_multiaddr.s_addr = inet_addr (group_addr.c_str ());
  group.imr_interface.s_addr = htonl (INADDR_ANY);

  if (setsockopt (recv_socket,
                  IPPROTO_IP,
                  IP_ADD_MEMBERSHIP,
                  ( char * ) &group,
                  sizeof (group)) < 0) {

    close (send_socket);
    close (recv_socket);

    throw "Erro ao se juntar ao gropo (IP_ADD_MEMBERSHIP)";
  }
}

void MulticastSocket::leave () {
  close (send_socket);
  close (recv_socket);
}

void MulticastSocket::sendMessage (const char * message) {

  int size = sizeof (message);

  if (sendto (send_socket,
              message,
              size + 1,
              0,
              ( struct sockaddr * ) &send_sock_in,
              sizeof (send_sock_in)) < 0) {

    throw "Erro ao enviar mensagem so grupo";
  }
}

char * MulticastSocket::receiveMessage (const int size) {

  char * buffer = ( char * ) calloc (size, sizeof (char));
  memset (buffer, 0, size);

  unsigned int recv_sock_size = sizeof (recv_sock_in);

  if (recvfrom (recv_socket,
                buffer,
                size,
                0,
                ( struct sockaddr * ) &recv_sock_in,
                &recv_sock_size) < 0) {

    throw "Erro no recebimento da mensagem";
  }

  return buffer;
}
