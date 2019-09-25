

class Curso {

public:
  static std::string tableCreationSql () {
    return std::string ("PRAGMA foreign_keys = ON;"
                        "CREATE TABLE IF NOT EXISTS [Curso] ("
                        "[codigo] INTEGER PRIMARY KEY,"
                        "[nome] NVARCHAR(100) NOT NULL"
                        ");");
  }
  static std::string retrieveSql (std::string where) {
    std::string sql ("SELECT * FROM Curso "
                     "WHERE ");

    sql += where + std::string (";");

    return sql.c_str ();
  }
  std::string creationSql () {
    std::string sql ("INSERT INTO Curso "
                     "(codigo,nome) "
                     "VALUES (");

    sql += std::to_string (this->codigo) + std::string (",");
    sql += this->nome + std::string (");");

    return sql.c_str ();
  }
  std::string updateSql () {
    std::string sql ("UPDATE Curso "
                     "SET ");

    sql += std::string ("nome = ") + this->nome;
    sql += std::string (" WHERE ");

    sql += std::string ("codigo = ") + std::to_string (this->codigo) +
           std::string (";");

    return sql.c_str ();
  }
  std::string deleteSql () {
    std::string sql ("DELETE FROM Curso "
                     "WHERE codigo = ");

    sql += std::to_string (this->codigo) + std::string (";");
    return sql.c_str ();
  }

  Curso (int codigo, std::string nome) {
    this->codigo = codigo;
    this->nome   = nome;
  }
  ~Curso () {}

private:
  int codigo;
  std::string nome;
};
