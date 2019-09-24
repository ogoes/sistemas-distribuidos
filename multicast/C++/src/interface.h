#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

typedef struct {
  std::string multicastIP;
  int multicastPort;
  std::string nickname;
} Properties;

class Interface {
public: // métodos que irão se comunicar com o controller
  Interface () {}
  ~Interface () {}
  virtual void assign (std::vector< std::string > /*user_nick*/) {}
  virtual void appendUser (std::string /*user_nick*/) {}
  virtual void showReceivedMessage (std::string /*msg*/) {}
  virtual std::string readMessageFromUI () { return std::string (""); }
  virtual int getSelectedUserIndex () { return -1; }

protected:
  std::vector< std::string > users;
  std::vector< std::string > messages;
};

class TUI : public Interface {

public:
  TUI ();
  ~TUI ();

  void assign (std::vector< std::string > /*user_nick*/);
  void appendUser (std::string /*user_nick*/);
  void showReceivedMessage (std::string /*msg*/);
  std::string readMessageFromUI ();
  int getSelectedUserIndex ();

  void showUsers ();
  void showMessages ();

  Properties getProps ();

private:
  Properties props;
  bool logged;

  int selected_user;

  WINDOW * users_tab;
  WINDOW * messages_tab;
  WINDOW * reader_tab;

  std::vector< std::string > users;
  std::vector< std::string > messages;

private: // methods
  void getInitialInformations ();
};
