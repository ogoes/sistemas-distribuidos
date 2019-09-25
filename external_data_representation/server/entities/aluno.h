#include <iostream>
#include <string>

class Aluno {

public:
  static std::string tableCreationSql () {
    return std::string ("PRAGMA foreign_keys = ON;"
                        "CREATE TABLE IF NOT EXISTS [Aluno] ("
                        "[RA] INTEGER PRIMARY KEY,"
                        "[nome] NVARCHAR(100) NOT NULL,"
                        "[periodo] INTEGER NOT NULL,"
                        "[codigo_curso] INTEGER NOT NULL,"
                        "FOREIGN KEY (codigo_curso) REFERENCES Curso (codigo)"
                        " ON DELETE CASCADE ON UPDATE CASCADE"
                        ");");
  }
  static std::string retrieveSql (std::string where) {
    std::string sql ("SELECT * FROM Disciplina "
                     "WHERE ");

    sql += where + std::string (";");

    return sql.c_str ();
  }
  std::string creationSql () {
    std::string sql ("INSERT INTO Aluno "
                     "(RA,nome,periodo,codigo_curso) "
                     "VALUES (");

    sql += std::to_string (this->RA) + std::string (",");
    sql += this->nome + std::string (",");
    sql += std::to_string (this->periodo) + std::string (",");
    sql += std::to_string (this->codigo_curso) + std::string (");");

    return sql;
  }
  std::string updateSql () {
    std::string sql ("UPDATE Aluno "
                     "SET ");

    sql += std::string ("nome = ") + this->nome + std::string (", ");
    sql += std::string ("periodo = ") + std::to_string (this->periodo) +
           std::string (", ");
    sql +=
        std::string ("codigo_curso = ") + std::to_string (this->codigo_curso);

    sql += std::string (" WHERE ");
    sql +=
        std::string ("RA = ") + std::to_string (this->RA) + std::string (";");

    return sql.c_str ();
  }
  std::string deleteSql () {
    std::string sql ("DELETE FROM Aluno "
                     "WHERE RA = ");

    sql += std::to_string (this->RA) + std::string (";");
    return sql.c_str ();
  }

  Aluno (int RA, std::string nome, int periodo, int codigo_curso) {
    this->RA           = RA;
    this->nome         = nome;
    this->periodo      = periodo;
    this->codigo_curso = codigo_curso;
  }
  ~Aluno () {}

private:
  int RA;
  std::string nome;
  int periodo;
  int codigo_curso;
};
