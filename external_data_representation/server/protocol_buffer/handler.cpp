#include "handler.h"

namespace pro_buffer {

enum Request { CRUD = 1, NOTAS, ALUNOS, DISCIPLINAS };

char * middleware (int type, char * requestData) {

  switch (type) {
  case CRUD: return crudRequest (requestData);

  case NOTAS: return matriculasRequest (requestData);

  case ALUNOS: return alunosRequest (requestData);

  case DISCIPLINAS: return disciplinasRequest (requestData);
  }
}

char * crudRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  sd::NotaRequest request;

  if (!request.ParseFromString (std::string (requestData))) {
    // Vai RETORNAR UM ERRO
    // NAO SEI AINDA
  }

  sd::Matricula matricula   = request.matricula ();
  sd::Aluno aluno           = matricula.aluno ();
  sd::Disciplina disciplina = matricula.disciplina ();

  switch (request.type ()) {
  case sd::NotaRequest::CREATE: break;
  case sd::NotaRequest::RETRIEVE: break;
  case sd::NotaRequest::UPDATE: break;
  case sd::NotaRequest::DELETE: break;
  }

  google::protobuf::ShutdownProtobufLibrary ();

  return "asd";
}
char * matriculasRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
  return "asd";
}
char * alunosRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
  return "asd";
}
char * disciplinasRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
  return "asd";
}
}; // namespace pro_buffer
