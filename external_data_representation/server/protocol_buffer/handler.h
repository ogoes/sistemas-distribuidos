#include <iostream>
#include <string>
#include <vector>

#include "../database.h"
#include "../entities/aluno.h"
#include "../entities/curso.h"
#include "../entities/disciplina.h"
#include "../entities/matricula.h"

#include "red.pb.h"

class PBHandler {
 public:
  static const char *middleware(int, char *);

 private:
  static const char *crudRequest(char *);
  static const char *matriculasRequest(char *);
  static const char *alunosRequest(char *);
  static const char *disciplinasRequest(char *);

  static sd::NotaResponse CreateMatricula(const sd::Matricula &);
};
