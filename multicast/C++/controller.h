#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <time.h>

#include "message.h"
#include "multicast_socket.h"

typedef struct {
  std::string multicastIP;
  int multicastPort;
  int udpPort;
  std::string addr;
  std::string nickname;
} Properties;

typedef struct {
  std::string nickname;
  std::string addr;
  int port;
} Target;

class DatagramSocket {
public:
  DatagramSocket (const int /*port*/);
  ~DatagramSocket ();

  void sendMessage (Target /*target*/, const char * /*msg*/);
  char * receiveMessage (const int /*size*/);

private:
  int port;
  int socket;
};

class Controller {

public:
  Controller (Properties & /*props*/);
  ~Controller ();

  int getSocket () const;
  int getPort () const;
  std::string getAddr () const;

  void joinMulticastGroup ();
  void leaveMulticastGroup ();

  void sendMessage (const char * /*target_nickname*/, const char * /* msg */);
  char * receiveGroupMessage (const int /* size */);
  char * receiveMessage (const int /* size */);

private: // attributes
  DatagramSocket * _dSocket;
  MulticastSocket * _mSocket;

  std::vector< Target > onlineUsers;

private: // methods
  int sendMessage (Message * /*msg*/, Target /*target*/);
  int sendGroupMessage (Message * /*msg*/);
};
