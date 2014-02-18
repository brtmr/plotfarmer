#ifndef GAME_H
#define GAME_H


#include"Level.h"
#include"Game.h"
#include"Player.h"
#include"Level.h"
#include"Tilemanager.h"
#include"Constants.h"
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<iostream>
#include<vector>

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
        bool gameOver;
        void handleKey(SDL_Event);
        //fields        
        SDL_Window*   gameWindow;       
        SDL_Renderer* gameRenderer;       
        Player *player;
        Tilemanager *tilemanager;
        Level level;
    };


#endif
