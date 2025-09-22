all: main

main: main.cpp components/*
	g++ -o main main.cpp -lncurses