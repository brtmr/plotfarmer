#include"Player.h"
#include<cstdio>

Player::Player(SDL_Renderer* renderer, Level* l, vec2di *c)
{
    level        = l;
    gameRenderer = renderer;
    camera       = c;
    spritesheet = new Spritesheet("sprites/wiz_staff_down.png",1,3,3,renderer);
    height = spritesheet->singleHeight*SCALE;
    width  = spritesheet->singleWidth*SCALE ;
    pos.x = 5;
    pos.y = 40;
    remainder.x = 0;
    remainder.y = 0;
    vel.y = -0.08;
    vel.x = 0;
    direction = DIRECTIONRIGHT;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = SCALE*(spritesheet->singleWidth);
    dstRect.h = SCALE*(spritesheet->singleHeight);
    running = false;
    inJump  = true;
    
}

Player::~Player()
{
    delete spritesheet;
}

void Player::update()
{
    float diffx,diffy;
    diffx = vel.x + remainder.x;
    pos.x = pos.x + roundf(diffx);
    remainder.x = diffx - roundf(diffx);
    diffy = vel.y + remainder.y;
    pos.y = pos.y + roundf(diffy);
    remainder.y = diffy - roundf(diffy); 
    float prevvely = vel.y;
    vel.y = vel.y + GRAVITY;
    
    stayInLevel();
    updateBounding();
    handleCollision();
    handleCollision();
    checkIfFalling(prevvely);
    setCamera();
}

void Player::stayInLevel()
{
    if ( pos.y+height > (level->height*SCALEDBLOCK) )
    {
        pos.y = (level->width*SCALEDBLOCK) - height - SMALLOFFSET;
        vel.y = 0;
        inJump=false;
    }
    if ( pos.x+width > (level->width*SCALEDBLOCK) )
    {
        pos.x = (level->width*SCALEDBLOCK) - width - SMALLOFFSET;
        vel.x = 0;
    }
    if ( pos.y < 0 )
    {
        pos.y = SMALLOFFSET;
        vel.y = 0;
    }
    if ( pos.x < 0 )
    {
        pos.x = SMALLOFFSET;
        vel.x = 0;
    }
}

void Player::checkIfFalling(float prevvely)
{
    if (vel.y > prevvely) ++acc_counter;
    else acc_counter = 0;
    if (acc_counter>=FALLCOUNTER) inJump = true;
}

void Player::setCamera()
{
    if (pos.x<SCREEN_WIDTH/2) 
        camera->x = 0;
    else if(pos.x > (level->pixelWidth)-(SCREEN_WIDTH/2)) 
        camera->x = (level->pixelWidth)-SCREEN_WIDTH;
    else 
        camera->x = pos.x-SCREEN_WIDTH/2;
    if (pos.y<SCREEN_HEIGHT/2) 
        camera->y = 0;
    else if(pos.y > (level->pixelHeight)-(SCREEN_HEIGHT/2)) 
        camera->y = (level->pixelHeight)-SCREEN_HEIGHT;
    else 
        camera->y = pos.y-SCREEN_HEIGHT/2;
}

void Player::updateBounding()
{
    bounding.x0 = pos.x +         ((direction==DIRECTIONRIGHT)?PXOFFSETL:PXOFFSETR);
    bounding.x1 = pos.x + width - ((direction==DIRECTIONRIGHT)?PXOFFSETR:PXOFFSETL);
    bounding.y0 = pos.y;
    bounding.y1 = pos.y + height;
}
    /**
     * Uses a minimum translation vector approach,
     * simplified to axis-aligned rectangles to deal woth collision
     * http://elancev.name/oliver/2D%20polygon.htm
     */
     
void Player::handleCollision()
{
    bool iMightHaveHitMyHead = false;
    int mini = bounding.y0/SCALEDBLOCK;
    int maxi = bounding.y1/SCALEDBLOCK;
    int minj = bounding.x0/SCALEDBLOCK;
    int maxj = bounding.x1/SCALEDBLOCK;
    rectangle tile;
    int x,y;
    for (int i=mini; i<=maxi; i++)
    {
        for (int j=minj; j<=maxj; j++)
        {
            if (level->isSolid(i,j))
            {
                tile.x0 = j*SCALEDBLOCK;
                tile.x1 = (j+1)*SCALEDBLOCK;
                tile.y0 = i*SCALEDBLOCK;
                tile.y1 = (i+1)*SCALEDBLOCK;
                Geometry::getMTV(bounding, tile, &x, &y);
                pos.x = pos.x + x;
                pos.y = pos.y + y;
                updateBounding();
                if (y<0 && vel.y>0) inJump = false;
                if (y<0) vel.y = 0;
                if (y>0) iMightHaveHitMyHead = true;
            }
        }
    }
    if (iMightHaveHitMyHead && didIHitMyHead())
    {
        vel.y = 0;
    }
}

bool Player::didIHitMyHead()
{
    int i  = (bounding.y0 / SCALEDBLOCK)-1;
    int j0 = ((bounding.x0) / SCALEDBLOCK);
    int j1 = ((bounding.x1) / SCALEDBLOCK);
    return (level->isSolid(i,j0) || level->isSolid(i,j1));
}

void Player::setDirection(int d)
{
    running = true;
    if (d == DIRECTIONLEFT)
        {
        direction = DIRECTIONLEFT;
        vel.x = -SPEED;
        }
    if (d == DIRECTIONRIGHT)
        {
        direction = DIRECTIONRIGHT;
        vel.x = SPEED;
        }
}

void Player::stop()
{
    vel.x = 0;
    running = false;
}
    
void Player::jump()
{
    if (inJump) return;
    vel.y = -JUMPSPEED;
    inJump = true;
}

vec2di Player::getTile()
{
    vec2di result;
    result.x = pos.y / SCALEDBLOCK;
    result.y = pos.x / SCALEDBLOCK;
    return result;
}

void Player::render()
{
    vec2di renderpos;
    renderpos.x = (pos.x)+roundf(remainder.x);
    renderpos.y = (pos.y)+roundf(remainder.y);
    dstRect.x = renderpos.x-camera->x;
    dstRect.y = renderpos.y-camera->y;
    if (direction == DIRECTIONRIGHT)
    SDL_RenderCopy(
        gameRenderer,
        spritesheet->sprites,
        getCurrentRectangle(),
        &dstRect   
    ); 
    if (direction == DIRECTIONLEFT)
    SDL_RenderCopyEx(
        gameRenderer,
        spritesheet->sprites,
        getCurrentRectangle(),
        &dstRect,
        0,
        NULL,
        SDL_FLIP_HORIZONTAL
    ); 
}

SDL_Rect* Player::getCurrentRectangle()
{   if (inJump)
    return &(spritesheet->clipRectangles.at(2));
    if (!running)
    return &(spritesheet->clipRectangles.at(0));
    int i;
    int spriteDuration = 80; 
    long which = SDL_GetTicks()/spriteDuration;
    if (which % 4 == 0) i = 0;
    if (which % 4 == 1) i = 1;
    if (which % 4 == 2) i = 2;
    if (which % 4 == 3) i = 1;    
    return &(spritesheet->clipRectangles.at(i));
}
