
comp = g++
libs = -lpthread

server: clean_server
	$(comp) main_server.cpp server.cpp $(libs) -o server

client: clean_client
	$(comp) main_client.cpp client.cpp $(libs) -o client


clean_server:
	[[ -f server ]] && rm server || echo -n
	
clean_client: 
	[[ -f client ]] && rm client || echo -n
