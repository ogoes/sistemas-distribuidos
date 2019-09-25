COMPILER=g++
FLAGS=-std=c++17 -lprotobuf -lpthread -lsqlite3

PBFILES=./protocol_buffer/*.c*
# JSONFILES=./json/*.c*
# XMLFILES=./xml/*.c*
JSONFILES=
XMLFILES=


server: server.cpp
	$(COMPILER) $(FLAGS) server.cpp database.cpp $(PBFILES) $(JSONFILES) $(XMLFILES) -o server 
