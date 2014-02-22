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
        Player(SDL_Renderer*, Level &l, vec2di &c);
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
        /* SDL stuff */ 
        SDL_Renderer *gameRenderer;
        /* references to game objects & structs */
        Spritesheet spritesheet;
        Level &level;
        vec2di &camera;
        /* velocity & position informatien */
        vec2df vel;        
        vec2di pos;
        vec2di interppos;
        vec2df remainder;
        vec2df interpremainder;
        int height;
        int width;
        short direction;
        bool running;
        bool inJump;
        bool interpX;
        int acc_counter;
        rectangle bounding;
        SDL_Rect dstRect;
    };

#endif
