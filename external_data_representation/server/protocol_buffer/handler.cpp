#include "handler.h"

enum Request { CRUD = 1, NOTAS, ALUNOS, DISCIPLINAS };

const char* PBHandler::middleware(int type, char* requestData) {
  switch (type) {
    case CRUD:
      return PBHandler::crudRequest(requestData);

    case NOTAS:
      // return matriculasRequest(requestData);

    case ALUNOS:
      // return alunosRequest(requestData);

    case DISCIPLINAS:
      break;
      // return disciplinasRequest(requestData);
  }

  return std::string("asd").c_str();
}

sd::NotaResponse PBHandler::CreateMatricula(const sd::Matricula& matricula) {
  sd::NotaResponse response;
  sd::ResponseStatus* status = response.mutable_status();

  const sd::Aluno& aluno = matricula.aluno();
  const sd::Disciplina& disciplina = matricula.disciplina();

  std::string codigo = disciplina.codigo();
  std::string RA = std::to_string(aluno.ra());

  std::cout << codigo << std::endl;
  std::cout << RA << std::endl;

  std::string selectAluno = std::string("SELECT * FROM Aluno WHERE RA = ");
  selectAluno += RA + std::string(";");

  std::string selectDisciplina =
      std::string("SELECT * FROM Disciplina WHERE codigo = \'");
  selectDisciplina += codigo + std::string("\';");

  std::string selectMatricula =
      std::string("SELECT * FROM Matricula WHERE codigo = \'");
  selectMatricula += codigo + std::string("\' AND RA = ") + RA;

  std::vector<std::vector<std::string>> queryAluno, queryDisciplina,
      queryMatricula;

  queryAluno = Database::query(selectAluno.c_str());
  if (queryAluno.empty()) {
    status->set_statuscode(404);
    status->set_message("Aluno não encontrado.");
    return response;
  }

  queryDisciplina = Database::query(selectDisciplina.c_str());
  if (queryDisciplina.empty()) {
    status->set_statuscode(404);
    status->set_message("Disciplina não encontrada.");
    return response;
  }

  queryMatricula = Database::query(selectMatricula.c_str());
  if (!queryMatricula.empty()) {
    status->set_statuscode(409);
    status->set_message("A matricula já foi criada.");
    return response;
  }

  Matricula* novaMatricula =
      new Matricula(aluno.ra(), codigo, matricula.ano(), matricula.semestre(),
                    matricula.nota(), matricula.faltas());

  if (!Database::exec(novaMatricula->creationSql().c_str())) {
    status->set_statuscode(500);
    status->set_message("Erro ao criar matricula do Aluno");

    std::cout << "erro" << std::endl;
    return response;
  }

  status->set_statuscode(201);
  status->set_message("Matricula criada com sucesso");

  return response;
}

// sd::NotaResponse RetrieveMatricula(const sd::Matricula& matricula) {}
// sd::NotaResponse UpdateMatricula(const sd::Matricula& matricula) {}
// sd::NotaResponse DeleteMatricula(const sd::Matricula& matricula) {}

const char* PBHandler::crudRequest(char* requestData) {
  sd::NotaRequest request;

  if (!request.ParseFromString(std::string(requestData))) {
    return nullptr;
  }

  sd::NotaResponse response;

  switch (request.type()) {
    case sd::NotaRequest::CREATE:
      response = CreateMatricula(request.matricula());
      break;
    case sd::NotaRequest::RETRIEVE:
      // response = RetrieveMatricula(request.matricula());
      break;
    case sd::NotaRequest::UPDATE:
      // response = UpdateMatricula(request.matricula());
      break;
    case sd::NotaRequest::DELETE:
      // response = DeleteMatricula(request.matricula());
      break;
  }

  std::string serializedResponse;
  response.SerializeToString(&serializedResponse);

  unsigned int size = strlen(serializedResponse.c_str());

  char* res = (char*)calloc(4 + size, sizeof(char));

  int init = 0;
  res[init++] = (char)((size & 0xff000000));
  res[init++] = (char)((size & 0x00ff0000));
  res[init++] = (char)((size & 0x0000ff00));
  res[init++] = (char)((size & 0x000000ff));

  memcpy(res + init, serializedResponse.c_str(), 4 + size);

  return (const char*)res;
}
// const char* PBHandler::matriculasRequest(char* requestData) {
//   char a[] = "asd";
//   return a;
// }
// const char* PBHandler::alunosRequest(char* requestData) {
//   char a[] = "asd";
//   return a;
// }
// const char* PBHandler::disciplinasRequest(char* requestData) {
//   char a[] = "asd";
//   return a;
// }
