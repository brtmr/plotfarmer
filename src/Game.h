#ifndef GAME_H
#define GAME_H

#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Player.h"
#include"Tilemanager.h"

class Game{
    
    public:
        Game(SDL_Window*, SDL_Renderer*);
        ~Game();
        void gameMainLoop();
        void render();

    private:
        void update(long);
        bool init_SDL;
        SDL_Window*   gameWindow;       
        SDL_Renderer* gameRenderer;       
        Player *player;
        Tilemanager *tilemanager;
        std::vector<SDL_Rect*> clipRectangle;
    };


#endif
