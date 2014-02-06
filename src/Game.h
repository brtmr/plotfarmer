#ifndef GAME_H
#define GAME_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Player.h"

class Game{
    
    public:
        Game(SDL_Window*, SDL_Renderer*);
        ~Game();

        void gameMainLoop();

    private:
        void update();
        void render();
        bool init_SDL;
        SDL_Window*   gameWindow;       
        SDL_Renderer* gameRenderer;       
        Player *player;
    };


#endif
