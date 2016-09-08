all: main

main: main.o eval.o
	g++ -std=c++11 -o main.out main.o eval.o -lpthread
    
main.o: main.cpp
	g++ -std=c++11 -c main.cpp -lpthread
    
