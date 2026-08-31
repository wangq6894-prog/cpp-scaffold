all: server client
server: server.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
client: client.cc cal.pb.cc
	g++ -o $@ $^ -std=c++17 -lbrpc -lleveldb -lprotobuf -lpthread -ldl -lssl -lcrypto -lgflags
clean:
	rm -f server client
