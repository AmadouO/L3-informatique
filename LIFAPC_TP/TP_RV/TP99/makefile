all: main

main: main.o image.o
	g++ main.o image.o -o main

main.o: main.cpp image.h
	g++ -Wall -std=c++11 -c main.cpp

image.o: image.cpp image.h
	g++ -Wall -std=c++11 -c image.cpp

clean:
	rm -f main.o image.o main