/**
 *  Mensagem
 *  Otavio Goes
 */

#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class Message {

public:
  Message (int /*type*/, const char * /*nickname*/, const char * /*msg*/);
  Message (char * /*msg_bytes*/);
  ~Message ();

  char * toBytes ();

  int type ();
  char * nickname ();
  char * message ();

  std::string toString () const;

private:
  int tipo;
  std::string apelido;
  std::string mensagem;
};
