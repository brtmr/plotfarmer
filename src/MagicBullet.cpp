#include"MagicBullet.h"

MagicBullet::MagicBullet(int x, int y, SDL_Renderer *r, vec2di &c, int direction):
super(x,y,r,c,false),
spritesheet("sprites/ball.png",1,1,1,r)
{
    if (direction == DIRECTIONRIGHT)
    vel.x = BULLETSPEED;
    else vel.x = -BULLETSPEED;
}

void MagicBullet::render()
{
    vec2di renderpos;
    renderpos.x = (interppos.x)+roundf(interpremainder.x);
    renderpos.y = (interppos.y)+roundf(interpremainder.y);

    SDL_Rect dstRec = {
        renderpos.x-camera.x,
        renderpos.y-camera.y,
        spritesheet.singleWidth*SCALE,
        spritesheet.singleHeight*SCALE
        };
    SDL_RenderCopy(gameRenderer,
        spritesheet.sprites,
        NULL,
        &(dstRec));
}




