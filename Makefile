output: main.o
	g++ -o output main.o 

main.o: main.cpp linearlist.h linearlist-implementation.h queue.h
	g++ -c  -std=c++17 main.cpp