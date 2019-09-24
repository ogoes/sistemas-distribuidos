#include "./src/message.h"
#include <iostream>

int main () {
  Message * a =
      new Message (1,
                   "gord",
                   "olaola, todosola, todosola, todosola, todosola, todos, "
                   "todosola, todosola, todosola, todosola, todosola, "
                   "todosola, todosola, todosola, todosola, todos");

  Message * b = new Message (a->toBytes ());

  delete a;
}
