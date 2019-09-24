#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

class MulticastSocket {

public:
  MulticastSocket (const char * /*address*/, int /*port*/);
  ~MulticastSocket ();

  void join ();
  void leave ();

  void sendMessage (const char * /*msg*/);
  char * receiveMessage (const int /*size*/);

private: // attributes
  int port;

  std::string group_addr;
  std::string local_addr;

  int send_socket;
  int recv_socket;

  struct sockaddr_in send_sock_in;
  struct sockaddr_in recv_sock_in;

  struct ip_mreq group;
};
