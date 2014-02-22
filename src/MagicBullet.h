#ifndef MAGIC_BULLET_H
#define MAGIC_BULLET_H

#include"Geometry.h"
#include"MovingObject.h"
#include"Spritesheet.h"
#include<SDL2/SDL.h>
#include<iostream>

class MagicBullet : public MovingObject{
    
    public:
        MagicBullet(int x, int y, SDL_Renderer *r, vec2di &c, int direction);
        ~MagicBullet();
        void render();
        void update();
        bool isDead();
        typedef MovingObject super; //for calling the super class

    
    private:
        Spritesheet spritesheet;
        int timer;
};

#endif
