#include "src/multicast_socket.h"
#include <exception>
#include <iostream>

int main () {

  try {

    MulticastSocket * mul = new MulticastSocket ("226.56.56.1", 5678);
    mul->join ();

    mul->sendMessage ("Ola todos");
    std::cout << mul->receiveMessage (1024) << std::endl;
    std::cout << mul->receiveMessage (1024) << std::endl;
    std::cout << mul->receiveMessage (1024) << std::endl;

  } catch (std::exception & e) {
    std::cout << e.what () << std::endl;
  } catch (const char * e) { std::cout << e << std::endl; }

  return 0;
}
