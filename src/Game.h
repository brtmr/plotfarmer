#ifndef GAME_H
#define GAME_H

#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Player.h"

class Game{
    
    public:
        Game(SDL_Window*, SDL_Renderer*);
        ~Game();
        void gameMainLoop();
        void render();

    private:
        void update();
        bool init_SDL;
        SDL_Window*   gameWindow;       
        SDL_Renderer* gameRenderer;       
        Player *player;
        std::vector<SDL_Rect*> clipRectangle;
    };


#endif
