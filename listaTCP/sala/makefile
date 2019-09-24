comp = g++
libs = -lpthread -std=c++11

all: server client
	echo -n

server: clean_server
	$(comp) server.cpp ../../socket/server.cpp $(libs) -o server

client: clean_client
	$(comp) client.cpp ../../socket/client.cpp $(libs) -o client

clean: clean_server clean_client
	echo -n

clean_server:
	[[ -f server ]] && rm -f server || echo -n

clean_client:
	[[ -f client ]] && rm -f client || echo -n
