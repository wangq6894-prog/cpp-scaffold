CFLAGS = -I../../source/ -std=c++17
log_test: log_test.cc ../../source/mylog.cc
	g++ -o log_test log_test.cc ../../source/mylog.cc $(CFLAGS) -lspdlog -lfmt -lgflags -lpthread
clean:
	rm -f log_test