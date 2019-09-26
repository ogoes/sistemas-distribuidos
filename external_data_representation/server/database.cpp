#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

#include "database.h"

#include "entities/aluno.h"
#include "entities/curso.h"
#include "entities/disciplina.h"
#include "entities/matricula.h"

static int callback(void* data, int argc, char** argv, char** azColName) {
  int i;
  fprintf(stderr, "%s: ", (const char*)data);

  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}

bool Database::open(const char* db_name) {
  if (instance == nullptr) instance = new Database();
  if (instance->opened) return instance->opened;

  if (sqlite3_open(db_name, &(instance->db))) {
    delete instance;
    instance = nullptr;
    throw "Erro ao abrir o banco de dados especificado";
  }

  std::string sql = Curso::tableCreationSql();
  if (sqlite3_exec(instance->db, sql.c_str(), 0, 0, 0) != SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Curso";
  }

  sql = Aluno::tableCreationSql();
  if (sqlite3_exec(instance->db, sql.c_str(), 0, 0, 0) != SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Aluno";
  }

  sql = Disciplina::tableCreationSql();
  if (sqlite3_exec(instance->db, sql.c_str(), 0, 0, 0) != SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Disciplina";
  }

  sql = Matricula::tableCreationSql();
  if (sqlite3_exec(instance->db, sql.c_str(), 0, 0, 0) != SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Matricula";
  }

  instance->opened = !instance->opened;

  return true;
}

bool Database::exec(const char* sql) {
  if (!instance) instance = new Database();
  if (!instance->opened) return !instance->opened;

  char* errMsg = 0;

  if (sqlite3_exec(instance->db, sql, callback, 0, &errMsg) != SQLITE_OK) {
    std::cout << errMsg << std::endl;
    return false;
  }
  return true;
}

std::vector<std::vector<std::string> > Database::query(const char* sql) {
  if (!instance) instance = new Database();

  std::vector<std::vector<std::string> > response;
  if (!instance->opened) return response;

  sqlite3_stmt* statement;

  if (sqlite3_prepare_v2(instance->db, sql, -1, &statement, 0) == 0) {
    int colNumber = sqlite3_column_count(statement);
    int retval;
    while ((retval = sqlite3_step(statement)) != SQLITE_DONE) {
      if (retval == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int col = 0; col < colNumber; ++col) {
          row.push_back(
              std::string((const char*)sqlite3_column_text(statement, col)));
        }
        response.push_back(row);
      }
    }
  }

  return response;
}

Database::Database() {}
Database::~Database() {}

void query(std::string (*function)(std::string)) {
  std::vector<std::vector<std::string> > query =
      Database::query(function("1").c_str());

  if (!query.empty()) {
    for (auto it = query.begin(); it != query.end(); ++it) {
      std::cout << "[";
      for (auto row = (*it).begin(); row != (*it).end(); ++row) {
        std::cout << *row;
        if ((row + 1) != (*it).end()) std::cout << ", ";
      }
      std::cout << "]" << std::endl;
    }
  }
}

// int main() {
//   Database::open("./teste.db");

//   Curso* C = new Curso(1, "BCC");
//   // Database::exec(C->creationSql().c_str());
//   std::string (*function)(std::string) = Curso::retrieveSql;
//   query(function);

//   Disciplina* D = new Disciplina("BCC", "ASDASD", "Asdas", 1);
//   // Database::exec(D->creationSql().c_str());
//   function = Disciplina::retrieveSql;
//   query(function);

//   Aluno* A = new Aluno(1921924, "Otavio", 6, 1);
//   // Database::exec(A->creationSql().c_str());
//   function = Aluno::retrieveSql;
//   query(function);

//   Matricula* M = new Matricula(1921924, "BCC", 2019, 1, 8.7, 5);
//   // Database::exec(M->creationSql().c_str());
//   function = Matricula::retrieveSql;
//   query(function);

//   return 0;
// }
