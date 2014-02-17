#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<vector>
#include"Spritesheet.h"

class Player{
    
    public:
        Player(SDL_Renderer*);
        ~Player();
        void setSpeedX();
        void setSpeedY();
        void render();
        void update(long);

            
    private:
        SDL_Rect dstRect;
        SDL_Renderer* gameRenderer;
        SDL_Rect* getCurrentRectangle();
        Spritesheet* spritesheet;
        float speedX;
        float speedY;
        float posX;
        float posY;

        bool running;
        bool inJump;
    };

#endif
