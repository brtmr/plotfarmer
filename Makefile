CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb -std=c++11
LFlags = -lSDL2 -lSDL2_image 
OBJS = Player.o Tilemanager.o Spritesheet.o Game.o Level.o

plotfarmer: $(OBJS)
	$(CC) $(LFlags) $(OBJS) -o plotfarmer

Game.o: src/Game.cpp src/Game.h src/Player.h src/Tilemanager.h
	$(CC) -c $(CFlags) $(LFlags) src/Game.cpp -o Game.o

Player.o: src/Player.h src/Player.cpp src/Spritesheet.h
	$(CC) -c $(CFlags) $(LFlags) src/Player.cpp -o Player.o

Tilemanager.o: src/Tilemanager.cpp src/Tilemanager.h src/Spritesheet.h
	$(CC) -c $(CFlags) $(LFlags) src/Tilemanager.cpp -o Tilemanager.o

Spritesheet.o: src/Spritesheet.cpp src/Spritesheet.h
	$(CC) -c $(CFlags) $(LFlags) src/Spritesheet.cpp -o Spritesheet.o

Level.o: src/Level.cpp src/Level.h
	$(CC) -c $(CFlags) $(LFlags) src/Level.cpp -o Level.o

clean:
	clear
	\rm -f *.o plotfarmer
