all: sync_server async_server sync_client async_client http_server http_client
sync_server: sync_server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
async_server: async_server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
sync_client: sync_client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
async_client: async_client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
http_server: http_server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
http_client: http_client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
clean:
	rm -f server sync_server async_server sync_client async_client http_server http_client
