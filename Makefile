CC = g++
CFlags = -Wall -Werror -pedantic-errors
LFlags = -lSDL2 -lSDL2_image 
#OBJS = 

Game: src/Game.cpp src/Game.h 
	$(CC) $(CFlags) $(LFlags) src/Game.cpp -o plotfarmer

clean:
	\rm -f *.o plotfarmer
