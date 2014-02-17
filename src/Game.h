#ifndef GAME_H
#define GAME_H

#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Player.h"
#include"Tilemanager.h"
#include"Level.h"


class Game{
    
    public:
        Game(SDL_Window*, SDL_Renderer*);
        ~Game();
        void gameMainLoop();
        void render();

    private:
        //methods
        void update(long);
        bool init_SDL;
        void handleKey(SDL_Event);
        //fields        
        SDL_Window*   gameWindow;       
        SDL_Renderer* gameRenderer;       
        Player *player;
        Tilemanager *tilemanager;
        Level level;
    };


#endif
