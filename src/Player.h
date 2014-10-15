#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<iterator>
#include<vector>
#include"Constants.h"
#include"Geometry.h"
#include"Level.h"
#include"MagicBullet.h"
#include"MovingObject.h"
#include"Spritesheet.h"
#include"MyMath.h"

class Player : MovingObject{

    public:
        Player(SDL_Renderer*, Level &l, vec2di &c, int x, int y);
        ~Player();
        void render();
        void update();
        void setDirection(int d);
        void stop();
        void jump();
        void hightenBulletCounter();
        bool readyToFire();
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
        int acc_counter;
        rectangle bounding;
        SDL_Rect dstRect;
        int bullet_counter;
};

#endif
