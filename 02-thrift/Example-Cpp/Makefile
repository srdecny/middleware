all: server

# Generate source files from Thrift IDL
gen-cpp/Example.cpp: Task.thrift
	thrift --gen cpp Task.thrift

# Compile server from main source and generated sources
server: server.cpp
	g++ -Igen-cpp -o server server.cpp gen-cpp/Login.cpp gen-cpp/Search.cpp gen-cpp/Reports.cpp gen-cpp/Task_types.cpp -lthrift

clean:
	rm -f server
	rm -rf gen-cpp


.PHONY: all clean