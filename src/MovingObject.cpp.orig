#include"MovingObject.h"

MovingObject::MovingObject(int x, int y, SDL_Renderer *r, vec2di &c, bool hW):
    vel({0,0}),
    pos({x,y}),
    interppos({x,y}),
    remainder({0,0}),
    interpremainder({0,0}),
    hasWeight(hW),
    gameRenderer(r),
    camera(c),
    interpXcnt(0)
{}

void MovingObject::update()
{
    //update velocity
    if (hasWeight) vel.y = vel.y + GRAVITY;
    if ( vel.y < -SPEEDLIMIT ) vel.y = -SPEEDLIMIT;
    if ( vel.y >  SPEEDLIMIT ) vel.y =  SPEEDLIMIT;
    //update positions
    float diffx,diffy;
    diffx = vel.x + remainder.x;
    pos.x = pos.x + roundf(diffx);
    remainder.x = diffx - roundf(diffx);
    diffy = vel.y + remainder.y;
    pos.y = pos.y + roundf(diffy);
    remainder.y = diffy - roundf(diffy); 
}

void MovingObject::update_interp(int interpolation)
{
    if (interpXcnt==0)
    {
        float diffX = vel.x * interpolation + remainder.x;
        interppos.x = pos.x + roundf(diffX);
        interpremainder.x = diffX - roundf(diffX);
    }
    else
    {
        interppos.x = pos.x;
        interpremainder.x = remainder.x;
    }
    float diffY = vel.y * interpolation + remainder.y;
    interppos.y = pos.y + roundf(diffY);
    interpremainder.y = diffY - roundf(diffY);
    //setCamera();
}

void MovingObject::render(){}

bool MovingObject::isDead(){return false;}
