

#include "message.h"

Message::Message (int type, const char * nickname, const char * msg)
    : tipo (type), apelido (nickname), mensagem (msg) {}

Message::Message (char * msg) {

  unsigned char * msg_bytes = ( unsigned char * ) msg;

  unsigned int nick_size, msg_size;

  unsigned int begin = 0;
  tipo               = ( unsigned int ) msg_bytes[begin++];

  nick_size = ( unsigned int ) msg_bytes[begin++];
  std::stringstream nick_ss;
  for (unsigned int i = 0; i < nick_size; ++i) {
    nick_ss << msg_bytes[begin++];
  }
  apelido = nick_ss.str ();

  msg_size = ( unsigned int ) msg_bytes[begin++];

  std::stringstream msg_ss;
  for (unsigned int i = 0; i < msg_size; ++i) {
    msg_ss << msg_bytes[begin++];
  }
  mensagem = msg_ss.str ();
}
Message::~Message () {}

char * Message::toBytes () {
  unsigned int nick_size = apelido.length ();
  unsigned int msg_size  = mensagem.length ();

  unsigned int byte_size = 1 + 1 + nick_size + 1 + msg_size;

  char * bytes = ( char * ) calloc (byte_size, sizeof (char));

  unsigned int begin = 0;

  bytes[begin++] = ( char ) tipo;

  bytes[begin++] = ( char ) nick_size;
  for (unsigned int i = 0; i < nick_size; ++i) {
    bytes[begin++] = apelido.at (i);
  }

  bytes[begin++] = (msg_size);
  for (unsigned int i = 0; i < msg_size; ++i) {
    bytes[begin++] = mensagem.at (i);
  }

  return bytes;
}

int Message::type () { return tipo; }
char * Message::nickname () { return ( char * ) apelido.c_str (); }
char * Message::message () { return ( char * ) mensagem.c_str (); }

std::string Message::toString () const {
  std::string r;
  r = std::string ("[") + std::to_string (tipo) + std::string (", ") + apelido +
      std::string (", ") + mensagem + std::string ("]");
  return ( char * ) r.c_str ();
}

std::ostream & operator<< (std::ostream & outs, const Message * msg) {
  return outs << msg->toString ();
}
