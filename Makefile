CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb -std=c++11
LFlags = -lSDL2 -lSDL2_image 
OBJS = Player.o Tilemanager.o

Game: src/Game.cpp src/Game.h $(OBJS)
	$(CC) $(CFlags) $(LFlags) src/Game.cpp $(OBJS) -o plotfarmer

Player.o: src/Player.h src/Player.cpp
	$(CC) -c $(CFlags) $(LFlags) src/Player.cpp -o Player.o

Tilemanager.o: src/Tilemanager.o src/Tilemanager.h
	$(CC) -c $(CFlags) $(LFlags) src/Tilemanager.cpp -o Tilemanager.o

clean:
	\rm -f *.o plotfarmer
