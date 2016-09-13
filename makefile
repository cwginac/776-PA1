all: main

main: main.o eval.o
	g++ -o main.out main.o eval.o
    
main.o: main.cpp
	g++ -c main.cpp
    
