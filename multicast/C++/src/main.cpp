#include "controller.h"
#include "interface.h"

#include <iostream>
#include <thread>

int main () {
  TUI * ui = new TUI ();

  ui->showUsers ();
  ui->showMessages ();

  Controller * ctrl = new (ui->getProps ());
  ctrl->setInterface (ui);

  // std::thread sender ([](Controller * ctrl) { ctrl->senderRoutine (); },
  // ctrl); std::thread receiver ([](Controller * ctrl) { ctrl->recvRoutine ();
  // }, ctrl);

  // sender.join ();
  // sender.join ();
  // delete ctrl;
  //
  delete ui;
}
