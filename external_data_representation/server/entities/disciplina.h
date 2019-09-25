#include <iostream>
#include <string>

class Disciplina {

public:
  static std::string tableCreationSql () {
    return std::string (
        "PRAGMA foreign_keys = ON;"
        "CREATE TABLE IF NOT EXISTS [Disciplina] ("
        "[codigo] NVARCHAR(15) PRIMARY KEY,"
        "[nome] NVARCHAR(50) NOT NULL,"
        "[professor] NVARCHAR(100) NOT NULL,"
        "[codigo_curso] INTEGER NOT NULL,"
        "FOREIGN KEY (codigo_curso) REFERENCES Curso (codigo) ON DELETE "
        "CASCADE ON UPDATE CASCADE"
        ");");
  }
  static std::string retrieveSql (std::string where) {
    std::string sql ("SELECT * FROM Disciplina "
                     "WHERE ");

    sql += where + std::string (";");

    return sql.c_str ();
  }
  std::string creationSql () {
    std::string sql ("INSERT INTO Disciplina "
                     "(codigo,nome,professor,codigo_curso) "
                     "VALUES (");

    sql += this->codigo + std::string (",");
    sql += this->nome + std::string (",");
    sql += this->professor + std::string (",");
    sql += std::to_string (this->codigo_curso) + std::string (");");

    return sql.c_str ();
  }
  std::string updateSql () {
    std::string sql ("UPDATE Disciplina "
                     "SET ");

    sql += std::string ("nome = ") + this->nome + std::string (", ");
    sql += std::string ("professor = ") + this->professor + std::string (", ");
    sql +=
        std::string ("codigo_curso = ") + std::to_string (this->codigo_curso);

    sql += std::string (" WHERE ");
    sql += std::string ("codigo = ") + this->codigo + std::string (";");

    return sql.c_str ();
  }
  std::string deleteSql () {
    std::string sql ("DELETE FROM Disciplina "
                     "WHERE codigo = ");

    sql += this->codigo + std::string (";");
    return sql.c_str ();
  }

  Disciplina (std::string codigo,
              std::string nome,
              std::string professor,
              int codigo_curso) {
    this->codigo       = codigo;
    this->nome         = nome;
    this->professor    = professor;
    this->codigo_curso = codigo_curso;
  }
  ~Disciplina () {}

private:
  std::string codigo;
  std::string nome;
  std::string professor;
  int codigo_curso;
};
