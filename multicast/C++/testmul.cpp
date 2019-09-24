#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

struct in_addr localInterface;
struct sockaddr_in groupSock;
int send_sd;
int recv_sd;
int datalen;
char databuf[1024];

struct sockaddr_in localSock;
struct ip_mreq group;

int main (int argc, char * argv[]) {

  /*--------------------------------------------------------------------------------*/

  /*
   * Enable SO_REUSEADDR to allow multiple instances of this
   * application to receive copies of the multicast datagrams.
   */
  {
    int reuse = 1;

    if (setsockopt (recv_sd,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    ( char * ) &reuse,
                    sizeof (reuse)) < 0) {
      perror ("setting SO_REUSEADDR");
      close (sd);
      exit (1);
    }
  }

  /*--------------------------------------------------------------------------------*/

  /*
   * Bind to the proper port number with the IP address
   * specified as INADDR_ANY.
   */
  memset (( char * ) &localSock, 0, sizeof (localSock));
  localSock.sin_family      = AF_INET;
  localSock.sin_port        = htons (5555);
  localSock.sin_addr.s_addr = INADDR_ANY;

  if (bind (sd, ( struct sockaddr * ) &localSock, sizeof (localSock))) {
    perror ("binding datagram socket");
    close (sd);
    exit (1);
  }

  /*--------------------------------------------------------------------------------*/

  /*
   * Join the multicast group 225.1.1.1 on the local 9.5.1.1
   * interface.  Note that this IP_ADD_MEMBERSHIP option must be
   * called for each local interface over which the multicast
   * datagrams are to be received.
   */
  group.imr_multiaddr.s_addr = inet_addr ("225.1.1.1");
  group.imr_interface.s_addr = inet_addr ("9.5.1.1");
  if (setsockopt (recv_sd,
                  IPPROTO_IP,
                  IP_ADD_MEMBERSHIP,
                  ( char * ) &group,
                  sizeof (group)) < 0) {
    perror ("adding multicast group");
    close (recv_sd);
    exit (1);
  }

  /*--------------------------------------------------------------------------------*/

  /*
   * Send a message to the multicast group specified by the
   * groupSock sockaddr structure.
   */
  datalen = 10;
  if (sendto (send_sd,
              databuf,
              datalen,
              0,
              ( struct sockaddr * ) &groupSock,
              sizeof (groupSock)) < 0) {
    perror ("sending datagram message");
  }

  /*
   * Read from the socket.
   */
  datalen = sizeof (databuf);
  if (read (recv_sd, databuf, datalen) < 0) {
    perror ("reading datagram message");
    close (recv_sd);
    exit (1);
  }
}
