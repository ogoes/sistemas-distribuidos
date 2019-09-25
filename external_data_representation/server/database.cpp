#include <iostream>
#include <string>

#include <sqlite3.h>

#include "database.h"

#include "entities/aluno.h"
#include "entities/curso.h"
#include "entities/disciplina.h"
#include "entities/matricula.h"

static int callback (void * data, int argc, char ** argv, char ** azColName) {
  int i;
  fprintf (stderr, "%s: ", ( const char * ) data);

  for (i = 0; i < argc; i++) {
    printf ("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf ("\n");
  return 0;
}

bool Database::open (const char * db_name) {
  if (instance == nullptr) instance = new Database ();
  if (instance->opened) return instance->opened;

  if (sqlite3_open (db_name, &(instance->db))) {
    delete instance;
    instance = nullptr;
    throw "Erro ao abrir o banco de dados especificado";
  }

  char * zErrMsg    = 0;
  const char * data = "Callback function called";

  std::string sql = Curso::tableCreationSql ();
  if (sqlite3_exec (
          instance->db, sql.c_str (), callback, ( void * ) data, &zErrMsg) !=
      SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Curso";
  }

  sql = Aluno::tableCreationSql ();
  if (sqlite3_exec (
          instance->db, sql.c_str (), callback, ( void * ) data, &zErrMsg) !=
      SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Aluno";
  }

  sql = Disciplina::tableCreationSql ();
  if (sqlite3_exec (
          instance->db, sql.c_str (), callback, ( void * ) data, &zErrMsg) !=
      SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Disciplina";
  }

  sql = Matricula::tableCreationSql ();
  if (sqlite3_exec (
          instance->db, sql.c_str (), callback, ( void * ) data, &zErrMsg) !=
      SQLITE_OK) {
    delete instance;
    throw "Erro ao criar tabela de Matricula";
  }

  return true;
}

Database::Database () {}
Database::~Database () {}

int main () {
  Database::open ("./teste.db");

  return 0;
}
