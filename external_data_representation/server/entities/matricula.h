#include <iostream>
#include <string>

class Matricula {

public:
  static std::string tableCreationSql () {
    return std::string ("PRAGMA foreign_keys = ON;"
                        "CREATE TABLE IF NOT EXISTS [Matricula] ("
                        "[RA] INTEGER NOT NULL,"
                        "[codigo_disciplina] NVARCHAR(15) NOT NULL,"
                        "[ano] INTEGER NOT NULL,"
                        "[semestre] INTEGER NOT NULL,"
                        "[nota] REAL NOT NULL,"
                        "[faltas] INTEGER NOT NULL,"
                        "PRIMARY KEY (codigo_disciplina, RA)"
                        ");");
  }
  static std::string retrieveSql (std::string where) {
    std::string sql ("SELECT * FROM Matricula "
                     "WHERE ");

    sql += where + std::string (";");

    return sql.c_str ();
  }
  std::string creationSql () {
    std::string sql ("INSERT INTO Matricula "
                     "(RA,codigo_disciplina,ano,semestre,nota,faltas) "
                     "VALUES (");

    sql += std::to_string (this->RA) + std::string (",");
    sql += this->codigo_disciplina + std::string (",");
    sql += std::to_string (this->ano) + std::string (",");
    sql += std::to_string (this->semestre) + std::string (",");
    sql += std::to_string (this->nota) + std::string (",");
    sql += std::to_string (this->faltas) + std::string (");");

    return sql.c_str ();
  }
  std::string updateSql () {
    std::string sql ("UPDATE Matricula "
                     "SET ");

    sql += std::string ("ano = ") + std::to_string (this->ano) +
           std::string (", ");
    sql += std::string ("semestre = ") + std::to_string (this->semestre) +
           std::string (", ");
    sql += std::string ("nota = ") + std::to_string (this->nota) +
           std::string (", ");
    sql += std::string ("faltas = ") + std::to_string (this->faltas);

    sql += std::string (" WHERE ");
    sql += std::string ("RA = ") + std::to_string (this->RA);
    sql += std::string (" AND codigo_disciplina = ") + this->codigo_disciplina +
           std::string (";");

    return sql.c_str ();
  }
  std::string deleteSql () {
    std::string sql ("DELETE FROM Matricula "
                     "WHERE RA = ");

    sql +=
        std::to_string (this->RA) + std::string (" AND codigo_disciplina = ");
    sql += this->codigo_disciplina + std::string (";");
    return sql.c_str ();
  }

  Matricula (int RA,
             std::string cod_disciplina,
             int ano,
             int semestre,
             float nota,
             int faltas) {
    this->RA                = RA;
    this->codigo_disciplina = cod_disciplina;
    this->ano               = ano;
    this->semestre          = semestre;
    this->nota              = nota;
    this->faltas            = faltas;
  }
  ~Matricula () {}

private:
  int RA;
  std::string codigo_disciplina;
  int ano;
  int semestre;
  float nota;
  int faltas;
};
