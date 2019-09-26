#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {

public:
  static bool open (const char * /*filename*/);
  static bool exec (const char * sql);
  static std::vector< std::vector< std::string > > query (const char * sql);

private:
  Database ();
  ~Database ();

private:
  // singleton
  inline static Database * instance = nullptr;

  sqlite3 * db = NULL;
  bool opened;
};
