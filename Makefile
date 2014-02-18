CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb -std=c++11 -O3
LFlags = -lSDL2 -lSDL2_image 
OBJS = Player.o Tilemanager.o Spritesheet.o Game.o Level.o

plotfarmer: $(OBJS)
	$(CC) $(LFlags) $(OBJS) -o plotfarmer

Game.o: src/Game.cpp src/Game.h src/Player.h src/Tilemanager.h src/Constants.h
	$(CC) -c $(CFlags) $(LFlags) src/Game.cpp -o Game.o

Player.o: src/Player.h src/Player.cpp src/Spritesheet.h src/Constants.h
	$(CC) -c $(CFlags) $(LFlags) src/Player.cpp -o Player.o

Tilemanager.o: src/Tilemanager.cpp src/Tilemanager.h src/Spritesheet.h src/Constants.h
	$(CC) -c $(CFlags) $(LFlags) src/Tilemanager.cpp -o Tilemanager.o

Spritesheet.o: src/Spritesheet.cpp src/Spritesheet.h
	$(CC) -c $(CFlags) $(LFlags) src/Spritesheet.cpp -o Spritesheet.o

Level.o: src/Level.cpp src/Level.h src/Constants.h
	$(CC) -c $(CFlags) $(LFlags) src/Level.cpp -o Level.o

Geometry.o: src/Geometry.cpp src/Geometry.h src/Constants.h
	$(CC) -c $(CFlags) $(LFlags) src/Geometry.cpp -o Geometry.o

clean:
	clear
	\rm -f *.o plotfarmer
