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
#include"MovingObject.h"
#include"MagicBullet.h"

class Player : MovingObject{
    
    public:
        Player(SDL_Renderer*, Level &l, vec2di &c, int x, int y);
        ~Player();
        void render();
        void update();
        void setDirection(int d);
        void stop();
        void jump();
        vec2di getStaffPosition();
        short getDirection();
        void update_interp(int);
        vec2di getTile();
        
        typedef MovingObject super; //for calling the super class

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
        /* references to game objects & structs */
        Spritesheet spritesheet;
        Level &level;
        /* velocity & position informatien */
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
