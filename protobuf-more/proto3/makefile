ALL:write read
read:read.cc contacts.pb.cc
	g++ -o read read.cc contacts.pb.cc -std=c++17 -lprotobuf
write:write.cc contacts.pb.cc
	g++ -o write write.cc contacts.pb.cc -std=c++17 -lprotobuf
.PHONY:clean
clean:
	rm -f write read
