#include <iostream>
#include "socket.h"



int main () {
  io_context io_context;
  ServerSocket * server = new ServerSocket(9999, io_context, tcp::v4());

  // server->acceptConnetion();

  return 0;
}
