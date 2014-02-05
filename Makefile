CC = g++
CFlags = -Wall -Werror -pedantic-errors
LFlags = -lSDL2

Game: src/Game.cpp src/Game.h
	$(CC) $(CFlags) $(LFlags) src/Game.cpp -o plotfarmer
	
