#include "handler.h"

using namespace pro_buffer;

enum Request { CRUD = 1, NOTAS, ALUNOS, DISCIPLINAS };

char * middleware (int type, char * requestData) {

  switch (type) {
  case CRUD: return crudRequest (requestData);

  case NOTAS: return notasRequest (requestData);

  case ALUNOS: return alunosRequest (requestData);

  case DISCIPLINAS: return disciplinasRequest (requestData);
  }
}

char * crudRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
}
char * notasRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
}
char * alunosRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
}
char * disciplinasRequest (char * requestData) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  google::protobuf::ShutdownProtobufLibrary ();
}
