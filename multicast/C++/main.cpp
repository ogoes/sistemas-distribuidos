#include <iostream>
#include <ncurses.h>
#include <thread>
#include <unistd.h>
#include <vector>

int y_size, x_size;

std::vector< std::string > msgs;

void user_tab () {
  WINDOW * win = newwin (3 * y_size / 4, x_size / 3, 0, 0);
  refresh ();

  box (win, 0, 0);
  wrefresh (win);

  int w_y_size, w_x_size;
  getmaxyx (win, w_y_size, w_x_size);

  mvwprintw (win, 0, w_x_size / 10, "Usuarios online");

  wrefresh (win);
}

void messages_tab () {

  WINDOW * win = newwin (3 * y_size / 4, (2 * x_size / 3), 0, (x_size / 3));
  refresh ();

  box (win, 0, 0);

  int w_y_size, w_x_size;
  getmaxyx (win, w_y_size, w_x_size);

  char msg[] = "Mensagens";

  mvwprintw (win, 0, (w_x_size / 10), msg);
  wrefresh (win);

  while (true) {
    int i = 0;
    for (auto it = msgs.begin (); it != msgs.end (); ++it, ++i) {
      mvwprintw (win, i + 1, 1, it->c_str ());
    }

    wrefresh (win);
    msgs.push_back (std::string ("asd"));
    sleep (1);
  }
  while (wgetch (win) != '\n') {}
}

void input_tab () {}

int main () {

  msgs.push_back (std::string ("<teste1>: Ola meu caro"));
  msgs.push_back (std::string ("<teste2>: Ola meu bom"));
  msgs.push_back (std::string ("<teste3>: tudo bem?"));
  initscr ();

  getmaxyx (stdscr, y_size, x_size);

  std::thread tab (user_tab);
  tab.join ();

  std::thread messages (messages_tab);
  messages.join ();

  getch ();
  endwin ();
  return 0;
}
