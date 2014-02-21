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
        Player(SDL_Renderer*, Level* l, vec2di *c);
        ~Player();
        void render();
        void update();
        void setDirection(int d);
        void stop();
        void jump();
        void update_interp(int);
        vec2di getTile();
        

    private:
        //functions:
        void handleCollision();
        void updateBounding();
        bool didIHitMyHead();
        void setCamera();
        void stayInLevel();
        void checkIfFalling(float);
        SDL_Rect* getCurrentRectangle();
        //fields
        SDL_Rect dstRect;
        SDL_Renderer* gameRenderer;
        Level* level;
        Spritesheet* spritesheet;
        vec2df vel;        
        vec2di pos;
        vec2di interppos;
        vec2df remainder;
        vec2df interpremainder;
        vec2di *camera;
        int height;
        int width;
        short direction;
        rectangle bounding;
        bool running;
        bool inJump;
        bool interpX;
        int acc_counter;
    };

#endif
