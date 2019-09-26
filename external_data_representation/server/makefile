COMPILER=g++
FLAGS=-std=c++17 -lprotobuf -lpthread -lsqlite3

PBFILES=./protocol_buffer/*.c*
DBFILES=./entities/*.h
# JSONFILES=./json/*.c*
# XMLFILES=./xml/*.c*
JSONFILES=
XMLFILES=


server: clean
	$(COMPILER) server.cpp database.cpp $(DBFILES) $(PBFILES) $(JSONFILES) $(XMLFILES) -o server $(FLAGS)

clean:
	[[ -f server ]] && rm server || echo -n
