all: sync_server async_server sync_client async_client
sync_server: sync_server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
async_server: async_server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
sync_client: sync_client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
async_client: async_client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
clean:
	rm -f server sync_server async_server sync_client async_client 
