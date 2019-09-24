/**
 *
 *  Otavio Goes
 */

#include "datagram_socket.h"
#include "interface.h"
#include "message.h"
#include "multicast_socket.h"

#include <arpa/inet.h> // PF_INET, inet_ntoa
#include <ifaddrs.h>   // ifreq
#include <net/if.h>    // IF_NAMESIZE
#include <netdb.h>
#include <netinet/in.h>

#include <sys/ioctl.h>
#include <sys/socket.h> // socket
#include <sys/types.h>

#include <cerrno>
#include <cstring> // memset
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <time.h>
#include <unistd.h> // close

typedef struct {
  std::string nickname;
  std::string addr;
  int port;
} Target;

class Controller {

public:
  Controller (Properties /*props*/);
  ~Controller ();

  void senderRoutine ();
  void recvRoutine ();
  void setInterface (Interface * /*ui*/);

private: // attributes
  DatagramSocket * _dSocket;
  MulticastSocket * _mSocket;

  std::vector< Target * > onlineUsers;

  Properties * props;
  Interface * interface;

private: // methods
  int getSocket () const;
  int getPort () const;
  std::string getAddr () const;

  void leaveMulticastGroup ();

  void sendMessage (const char * /*target_nickname*/, Message * /* msg */);
  char * receiveGroupMessage (const int /* size */);
  char * receiveMessage (const int /* size */);
  int sendMessage (Message * /*msg*/, Target * /*target*/);
  int sendGroupMessage (Message * /*msg*/);
  int in_online_users_vector (std::string /*nickname*/);
  void joinMulticastGroup ();
  void messageHandler (Message *);
};
