#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {

public:
  static bool open (const char * /*filename*/);

private:
  Database ();
  ~Database ();

private:
  // singleton
  inline static Database * instance = nullptr;

  sqlite3 * db = NULL;
  bool opened;
};
