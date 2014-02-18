#include"Player.h"
#include"Spritesheet.h"
#include"Constants.h"
#include<iostream>


Player::Player(SDL_Renderer* renderer, Level* l)
{
    level        = l;
    gameRenderer = renderer;
    /* load the spritesheet */
    spritesheet = new Spritesheet("sprites/wiz_staff_down.png",1,3,3,renderer);
    
    height = spritesheet->singleHeight;
    width  = spritesheet->singleWidth;
    
    /* set initial position*/
    pos.x = 5;
    pos.y = 40;
    prevpos.x = 5;
    prevpos.y = 40;
    speedY = -0.08;
    speedX = 0;
    
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

void Player::update(long dt)
{
    prevpos.x = pos.x;
    prevpos.y = pos.y;
    
    pos.x = pos.x + speedX*dt;
    pos.y = pos.y + speedY*dt;
    speedY = speedY + GRAVITY*dt;
    
    /*
     * Dont let the player leave the level.
     */
    if ( pos.y+height > (level->unscaledHeight) )
    {
        pos.y = (level->unscaledHeight) - height - SMALLOFFSET;
        speedY = 0;
        inJump=false;
    }
    if ( pos.x+width > (level->unscaledWidth) )
    {
        pos.x = (level->unscaledWidth) - width - SMALLOFFSET;
        speedX = 0;
    }
    if ( pos.y < 0 )
    {
        pos.y = SMALLOFFSET;
        speedY = 0;
    }
    if ( pos.x < 0 )
    {
        pos.x = SMALLOFFSET;
        speedX = 0;
    }
    
    updateBounding();
    
    handleCollision();
    handleCollision();
}

void Player::updateBounding()
{
    bounding.x0 = pos.x +         ((direction==DIRECTIONRIGHT)?PXOFFSETL:PXOFFSETR);
    bounding.x1 = pos.x + width - ((direction==DIRECTIONRIGHT)?PXOFFSETR:PXOFFSETL);
    bounding.y0 = pos.y;
    bounding.y1 = pos.y + height;
    bounding.ym = pos.y + (height/2);

}

void Player::handleCollision()
{
    std::cout << "########################################" << std::endl;
    std::vector<std::vector<int>> tiles;
    for (int i=bounding.y0/BLOCKSIZE; i<=bounding.y1/BLOCKSIZE; i++)
    {
        for (int j=bounding.x0/BLOCKSIZE; j<=bounding.x1/BLOCKSIZE; j++)
        {
            std::vector<int> tile;
            tile.push_back(i);
            tile.push_back(j);
            tiles.push_back(tile);
        }
    }
    //iterate over all the tiles!
    for (std::vector<std::vector<int>>::iterator it = tiles.begin(); it != tiles.end(); ++it)
    {
        //find a point in this thing!
        //top left 
        
    }
}

void Player::handleSingleCollision(float px, float py)
{   

}

void Player::setDirection(int d)
{
    running = true;
    if (d == DIRECTIONLEFT)
        {
        direction = DIRECTIONLEFT;
        speedX = -SPEED;
        }
    if (d == DIRECTIONRIGHT)
        {
        direction = DIRECTIONRIGHT;
        speedX = SPEED;
        }
}

void Player::stop()
{
    speedX = 0;
    running = false;
}
    
void Player::jump()
{
    //cant jump while jumping
    if (inJump) return;
    speedY = -JUMPSPEED;
    inJump = true;
}

bool Player::isColliding()
{
    for (int i=bounding.y0/BLOCKSIZE; i<(bounding.y1/BLOCKSIZE)+1; i++)
    {
        for (int j=bounding.x0/BLOCKSIZE; j<(bounding.x1/BLOCKSIZE)+1; j++)
        {
            if (level->isSolid(i,j)) return true;
        }
    }
    return false;
}

void Player::render()
{
    dstRect.x = SCALE*pos.x;
    dstRect.y = SCALE*pos.y;
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
