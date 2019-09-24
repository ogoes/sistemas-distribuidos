#include "controller.h"

#include <iostream>
#include <thread>

int main () {
  TUI * ui = new TUI ();

  ui->showUsers ();
  ui->showMessages ();

  Controller * ctrl = new Controller (ui->getProps ());
  ctrl->setInterface (ui);

  std::thread sender ([](Controller * ctrl) { ctrl->senderRoutine (); }, ctrl);
  std::thread receiver ([](Controller * ctrl) { ctrl->recvRoutine (); }, ctrl);

  sender.join ();
  receiver.join ();
  delete ctrl;
}
