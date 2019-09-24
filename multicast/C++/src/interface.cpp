#include "interface.h"

#include <sstream>

TUI::TUI () : Interface () {
  initscr ();
  // getInitialInformations ();

  selected_user = 0;

  int y_size, x_size;

  getmaxyx (stdscr, y_size, x_size);

  users_tab    = newwin (3 * y_size / 4, x_size / 3, 0, 0);
  messages_tab = newwin (3 * y_size / 4, (2 * x_size / 3), 0, (x_size / 3));
  reader_tab   = newwin ((y_size / 4), x_size - 1, (3 * y_size / 4), 0);

  refresh ();
}

TUI::~TUI () {
  endwin ();
  delwin (users_tab);
  delwin (messages_tab);
  delwin (reader_tab);
}

void TUI::getInitialInformations () {

  int x_size, y_size;
  getmaxyx (stdscr, y_size, x_size);

  int w_y_size = (y_size / 3);
  int w_x_size = (x_size / 3);

  WINDOW * win = newwin (w_y_size, w_x_size, w_y_size, w_x_size);
  refresh ();

  box (win, 0, 0);

  mvwprintw (win, 0, w_x_size / 10, "informacoes iniciais");

  char multicastGroupAddress[20];
  char nickname[256];
  char port[6];

  int begin = 5;

  mvwprintw (win, begin, 2, "Endereco Multicast: ");
  mvwprintw (win, begin + 2, 2, "Porta: ");
  mvwprintw (win, begin + 4, 2, "Nickname: ");

  mvwprintw (win, begin, 22, "");
  wgetnstr (win, multicastGroupAddress, 16);

  mvwprintw (win, begin + 2, 9, "");
  wgetnstr (win, port, 6);

  mvwprintw (win, begin + 4, 12, "");
  wgetnstr (win, nickname, 256);

  wrefresh (win);

  props.multicastIP   = std::string (multicastGroupAddress);
  props.multicastPort = std::atoi (port);
  props.nickname      = std::string (nickname);

  logged = true;
  delwin (win);
}

Properties TUI::getProps () { return this->props; }

void TUI::showUsers () {
  noecho ();
  box (users_tab, 0, 0);
  wrefresh (users_tab);

  int w_y_size, w_x_size;
  getmaxyx (users_tab, w_y_size, w_x_size);

  mvwprintw (users_tab, 0, w_x_size / 10, "Usuarios online");

  int i = 0;
  for (auto it = users.begin (); it != users.end (); ++it, ++i) {
    if (i == selected_user) { wattron (users_tab, A_REVERSE); }
    mvwprintw (users_tab, i + 1, 2, it->c_str ());
    wattroff (users_tab, A_REVERSE);
  }

  for (int i = 0; i < users.size (); ++i) {}

  wrefresh (users_tab);
  refresh ();
}

void TUI::showMessages () {
  box (messages_tab, 0, 0);

  int w_y_size, w_x_size;
  getmaxyx (messages_tab, w_y_size, w_x_size);

  char msg[] = "Mensagens";

  mvwprintw (messages_tab, 0, (w_x_size / 10), msg);
  wrefresh (messages_tab);
  refresh ();

  auto first = messages.size () > w_y_size - 3 ? messages.end () - w_y_size - 3
                                               : messages.begin ();
  auto last = messages.end ();

  std::vector< std::string > new_one (first, last);

  int i = 0;
  for (auto it = new_one.begin (); it != new_one.end (); ++it, ++i) {
    mvwprintw (messages_tab, i + 1, 2, it->c_str ());
  }
  wrefresh (messages_tab);
}

std::string TUI::readMessageFromUI () {
  box (reader_tab, 0, 0);

  int w_y_size, w_x_size;
  getmaxyx (reader_tab, w_y_size, w_x_size);

  char msg[] = "Escreva uma mensagem";

  mvwprintw (reader_tab, 0, (w_x_size / 10), msg);

  for (int i = 0; i < w_x_size - 1; ++i) {
    mvwprintw (reader_tab, 5, i, " ");
    wrefresh (reader_tab);
  }

  mvwprintw (reader_tab, 5, 1, "Enter para enviar: ");

  int beginning = 21;

  wrefresh (reader_tab);

  cbreak ();
  noecho ();
  keypad (reader_tab, TRUE);

  std::vector< char > mesg;

  std::string mensagem;
  std::stringstream mesg_ss;
  int ch;
  while ((ch = wgetch (reader_tab)) != '\n') {
    switch (ch) {
    case KEY_DOWN:
      selected_user = (selected_user + 1) % users.size ();
      showUsers ();
      break;
    case KEY_F (1): return std::string ("EXIT");
    case KEY_BACKSPACE:
      wmove (reader_tab, 5, beginning + (mesg.size () - 2));
      mesg.pop_back ();
      wprintw (reader_tab, " ");
      wmove (reader_tab, 5, beginning + (mesg.size () - 2));
      break;
    default:
      wprintw (reader_tab, "%c", ch);
      mesg.push_back (( char ) ch);
      break;
    }
  }

  for (auto i = mesg.begin (); i != mesg.end (); ++i) {
    mesg_ss << *i;
  }

  return mesg_ss.str ();
}

void TUI::showReceivedMessage (std::string msg) {
  messages.push_back (msg);
  showMessages ();
}

void TUI::appendUser (std::string user) { users.push_back (user); }

void TUI::assign (std::vector< std::string > users) {

  this->users   = users;
  selected_user = 0;
}

int TUI::getSelectedUserIndex () { return selected_user; }
