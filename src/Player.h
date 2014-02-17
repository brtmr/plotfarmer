#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<vector>
#include"Spritesheet.h"
#include"Level.h"


class Player{
    
    public:
        Player(SDL_Renderer*, Level* l);
        ~Player();
        void render();
        void update(long);
        void setDirection(int d);
            
    private:
        //functions:
        bool isColliding();
        void handleCollision();
        //fields
        SDL_Rect dstRect;
        SDL_Renderer* gameRenderer;
        SDL_Rect* getCurrentRectangle();
        Level* level;
        Spritesheet* spritesheet;
        float speedY;
        float speedX;
        float posX;
        float posY;
        int height;
        int width;
        short direction;
        bool running;
        bool inJump;
    };

#endif
