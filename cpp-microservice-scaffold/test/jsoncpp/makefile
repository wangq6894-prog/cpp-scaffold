json_test: json_test.cc ../../source/util.h ../../source/util.cc ../../source/mylog.h ../../source/mylog.cc
	g++ -o json_test json_test.cc ../../source/util.cc ../../source/mylog.cc -ljsoncpp -std=c++17 -lfmt -lspdlog -lpthread
clean:
	rm -f json_test
