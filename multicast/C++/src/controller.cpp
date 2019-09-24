/**
 *  Controlador
 *  Otavio Goes
 */

#include "controller.h"

Controller::Controller (Properties props) {
  _mSocket =
      new MulticastSocket (props.multicastIP.c_str (), props.multicastPort);
  _dSocket = new DatagramSocket ();

  this->props = &props;

  Target * group = ( Target * ) malloc (sizeof (Target));

  group->nickname = std::string ("Todos");
  group->addr     = props.multicastIP;
  group->port     = props.multicastPort;

  onlineUsers.push_back (group);
  joinMulticastGroup ();
}

Controller::~Controller () {
  delete _dSocket;
  delete _mSocket;

  delete interface;
}

void Controller::joinMulticastGroup () {
  _mSocket->join ();

  int join_msg_type = 1;

  Message * join_msg = new Message (join_msg_type,
                                    ( const char * ) props->nickname.c_str (),
                                    this->_dSocket->getAddress ().c_str ());
  sendMessage ("Todos", join_msg);
}

void Controller::leaveMulticastGroup () {

  int leave_msg_type  = 5;
  Message * leave_msg = new Message (
      leave_msg_type, ( const char * ) props->nickname.c_str (), "");

  sendMessage ("Todos", leave_msg);
  _mSocket->leave ();
}

void Controller::sendMessage (const char * target_nickname, Message * msg) {

  int target_index = in_online_users_vector (std::string (target_nickname));

  if (strcmp (target_nickname, "Todos") == 0) {
    Message * snd = new Message (
        3, props->nickname.c_str (), ( const char * ) msg->message ());

    sendGroupMessage (snd);
  } else if (target_index >= 0) {
    Message * snd = new Message (
        4, props->nickname.c_str (), ( const char * ) msg->message ());

    Target * target = onlineUsers.at (target_index);

    sendMessage (snd, target);
  }
}
char * Controller::receiveGroupMessage (const int size = 300) {
  return _mSocket->receiveMessage (size);
}
char * Controller::receiveMessage (const int size = 300) { return ""; }

int Controller::sendMessage (Message * msg, Target * target) {
  _dSocket->sendMessage (
      target->addr, target->port, ( const char * ) msg->toBytes ());
  return 0;
}
int Controller::sendGroupMessage (Message * msg) {
  _mSocket->sendMessage (( const char * ) msg->toBytes ());
  return 0;
}
int Controller::in_online_users_vector (std::string nickname) {

  int index = 0;
  for (auto it = onlineUsers.begin (); it != onlineUsers.end ();
       ++it, ++index) {
    if ((*it)->nickname == nickname) { return index; }
  }

  return -1;
}

void Controller::setInterface (Interface * ui) { interface = ui; }

void Controller::senderRoutine () {

  std::string recved;

  while ((recved = interface->readMessageFromUI ()) != "EXIT") {
    // this->interface->showReceivedMessage (recved);
    int i = this->interface->getSelectedUserIndex ();
    sendMessage (onlineUsers.at (i)->nickname.c_str (),
                 new Message (1, "", recved.c_str ()));
  }
}

void Controller::recvRoutine () {
  std::thread udp ([this]() {
    MessageInformation a = this->_dSocket->receiveMessage (400);
    Message * msg        = new Message (a.message_bytes);
    if (msg->type () == 2) {
      Target * novo  = ( Target * ) malloc (sizeof (Target));
      novo->nickname = msg->nickname ();
      novo->addr     = a.sender_address;
      novo->port     = a.sender_port;

      onlineUsers.push_back (novo);

      std::vector< std::string > nas;

      for (auto i = onlineUsers.begin (); i != onlineUsers.end (); ++i) {
	nas.push_back ((*i)->nickname);
      }
      interface->assign (nas);
    }
  });

  std::thread multi ([this]() {
    Message * msg = new Message (this->_mSocket->receiveMessage (400));
    if (msg->type () == 1) {
      Message * sen = new Message (2, props->nickname.c_str (), "");

      Target * novo  = ( Target * ) malloc (sizeof (Target));
      novo->nickname = msg->nickname ();
      novo->addr     = msg->message ();
      novo->port     = 6799;

      onlineUsers.push_back (novo);

      sendMessage (novo->nickname.c_str (), sen);
    } else if (msg->type () == 3) {
      this->interface->showReceivedMessage (msg->message ());
    } else if (msg->type () == 5) {
      std::vector< Target * > novo;

      for (auto a = onlineUsers.begin (); a != onlineUsers.end (); ++a) {
	if ((*a)->nickname != msg->nickname ()) novo.push_back (*a);
      }

      onlineUsers = novo;
    }
  });

  udp.join ();
  multi.join ();
}
