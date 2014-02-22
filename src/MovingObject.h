#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include"Geometry.h"
#include"Constants.h"
#include<cmath>
#include<SDL2/SDL.h>

class MovingObject
{
    public:
        MovingObject(int x, int y, SDL_Renderer* renderer, vec2di &c, bool hW);
        virtual void update();
        virtual void render();
        virtual bool isDead();
        virtual void update_interp(int interpolation);
        
        /* velocity & position information */
        vec2df vel;        
        vec2di pos;
        vec2di interppos;
        vec2df remainder;
        vec2df interpremainder;
        //determines wether the object is influenced by gravity
        bool hasWeight;
        SDL_Renderer *gameRenderer;
        vec2di &camera;
        bool interpX;
};

#endif

