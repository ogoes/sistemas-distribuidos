#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

typedef struct {
  char * message_bytes;
  int sender_port;
  std::string sender_address;

} MessageInformation;

class DatagramSocket {
public:
  DatagramSocket ();
  ~DatagramSocket ();

  void sendMessage (std::string /*addr*/, int /*port*/, const char * /*msg*/);
  MessageInformation receiveMessage (const int /*size*/);

  std::string getAddress ();

private:
  int port;
  int send_socket;
  int recv_socket;
  struct sockaddr_in sock_in;
};
