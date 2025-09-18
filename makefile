all: main

main: main.cpp components/Board.hpp components/GameLogic.hpp
	g++ -o main main.cpp -lncurses