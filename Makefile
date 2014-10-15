CC = g++
CFlags = -Wall -Werror -pedantic-errors -g -ggdb -std=c++11 -O3
LFlags = -lSDL2 -lSDL2_image -flto
OBJDIR = build

all: plotfarmer

OBJS = $(OBJDIR)/Player.o $(OBJDIR)/Tilemanager.o $(OBJDIR)/Spritesheet.o \
	$(OBJDIR)/Game.o $(OBJDIR)/Level.o $(OBJDIR)/Geometry.o \
	$(OBJDIR)/MovingObject.o $(OBJDIR)/MagicBullet.o

$(OBJS): $(OBJDIR)/%.o : src/%.cpp
	$(CC) -c $(CFlags) $(LFlags) $< -o $@

plotfarmer: $(OBJS)
	$(CC) $(LFlags) $(OBJS) -o plotfarmer

clean:
	\rm -f build/*.o plotfarmer
