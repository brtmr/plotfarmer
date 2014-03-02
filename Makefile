CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb -std=c++11 -O3
LFlags = -lSDL2 -lSDL2_image -flto
OBJS = Player.o Tilemanager.o Spritesheet.o Game.o Level.o Geometry.o MovingObject.o MagicBullet.o

plotfarmer: $(OBJS)
	$(CC) $(LFlags) $(OBJS) -o plotfarmer

Game.o: src/Game.cpp src/Game.h src/Player.h src/Tilemanager.h src/Constants.h
	$(CC) -c $(CFlags) src/Game.cpp -o Game.o

Player.o: src/Player.h src/Player.cpp src/Spritesheet.h src/Constants.h src/MovingObject.h
	$(CC) -c $(CFlags) src/Player.cpp -o Player.o

Tilemanager.o: src/Tilemanager.cpp src/Tilemanager.h src/Spritesheet.h src/Constants.h
	$(CC) -c $(CFlags) src/Tilemanager.cpp -o Tilemanager.o

Tile.o :src/Tile.h src/Tile.cpp src/Spritesheet.h src/Constants.h
	$(CC) -c $(CFlags) src/Tile.cpp -o Tile.o

Spritesheet.o: src/Spritesheet.cpp src/Spritesheet.h
	$(CC) -c $(CFlags) src/Spritesheet.cpp -o Spritesheet.o

Level.o: src/Level.cpp src/Level.h src/Constants.h
	$(CC) -c $(CFlags) src/Level.cpp -o Level.o

Geometry.o: src/Geometry.cpp src/Geometry.h src/Constants.h
	$(CC) -c $(CFlags) src/Geometry.cpp -o Geometry.o

MovingObject.o: src/MovingObject.cpp src/MovingObject.h src/Constants.h
	$(CC) $(CFlags) -c src/MovingObject.cpp -o MovingObject.o

MagicBullet.o: src/MagicBullet.cpp src/MagicBullet.h src/Constants.h
	$(CC) $(CFlags) -c src/MagicBullet.cpp -o MagicBullet.o

GeometryTest: src/Geometry.cpp src/Geometry.h src/GeometryTest.cpp Geometry.o
	$(CC) $(CFlags) src/GeometryTest.cpp Geometry.o -o GeometryTest

clean:
	clear
	\rm -f *.o plotfarmer GeometryTest
