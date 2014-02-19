#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<vector>
#include<iterator>
#include<iostream>
#include"Spritesheet.h"
#include"Level.h"
#include"Geometry.h"
#include"Constants.h"




class Player{
    
    public:
        Player(SDL_Renderer*, Level* l);
        ~Player();
        void render();
        void update(long);
        void setDirection(int d);
        void stop();
        void jump();
            
    private:
        //functions:
        bool isColliding();
        void handleCollision();
        void handleSingleCollision(float px, float py);
        void updateBounding();
        //fields
        SDL_Rect dstRect;
        SDL_Renderer* gameRenderer;
        SDL_Rect* getCurrentRectangle();
        Level* level;
        Spritesheet* spritesheet;
        float speedY;
        float speedX;
        Point pos;
        Point prevpos;
        int height;
        int width;
        short direction;
        rectangle bounding;
        bool running;
        bool inJump;
    };

#endif
