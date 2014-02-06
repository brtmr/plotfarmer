CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb
LFlags = -lSDL2 -lSDL2_image 
OBJS = Player.o

Game: src/Game.cpp src/Game.h $(OBJS)
	clear
	$(CC) $(CFlags) $(LFlags) src/Game.cpp $(OBJS) -o plotfarmer

Player.o: src/Player.h src/Player.cpp
	clear
	$(CC) -c $(CFlags) $(LFlags) src/Player.cpp -o Player.o

clean:
	\rm -f *.o plotfarmer
