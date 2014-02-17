#include"Player.h"
#include"Spritesheet.h"
#include"Constants.h"
#include<iostream>


Player::Player(SDL_Renderer* renderer, Level* l)
{
    level        = l;
    gameRenderer = renderer;
    /* load the spritesheet */
    spritesheet = new Spritesheet("sprites/wiz.png",1,3,3,renderer);
    
    height = spritesheet->singleHeight;
    width  = spritesheet->singleWidth;
    
    /* set initial position*/
    posX = 5;
    posY = 40;
    speedY = -0.08;
    speedX = 0.04;
    
    direction = DIRECTIONRIGHT;
    
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = SCALE*(spritesheet->singleWidth);
    dstRect.h = SCALE*(spritesheet->singleHeight);

    running = true;
    inJump  = true;

}

Player::~Player()
{
    delete spritesheet;
}

void Player::update(long dt)
{
    posX = posX + speedX*dt;
    posY = posY + speedY*dt;
    speedY = speedY + GRAVITY*dt;
    
    /*
     * Dont let the player leave the level.
     */
    if ( posY+height > (level->unscaledHeight) )
    {
        posY = (level->unscaledHeight) - height - SMALLOFFSET;
        speedY = 0;
    }
    if ( posX+width > (level->unscaledWidth) )
    {
        posX = (level->unscaledWidth) - width - SMALLOFFSET;
        speedX = 0;
    }
    if ( posY < 0 )
    {
        posY = SMALLOFFSET;
        speedY = 0;
    }
    if ( posX < 0 )
    {
        posX = SMALLOFFSET;
        speedX = 0;
    }
    
    /*
    * check for collisions with the level
    * and handle them
    */
    
    if (isColliding())
    {
        handleCollision();
    }
    
}

void Player::handleCollision()
{
    //int topY    = posY / BLOCKSIZE;
    int bottomY = (posY+height) / BLOCKSIZE;
    int leftX   = posX / BLOCKSIZE;
    int rightX  = (posX+width) / BLOCKSIZE;
    /*falling*/
    if (speedY>0)
    {
        /* check wether the above block is free. move the player there */
        if( !level->isSolid(bottomY-1, leftX ) &&
            !level->isSolid(bottomY-1, rightX) &&
            !level->isSolid(bottomY-2, leftX ) &&
            !level->isSolid(bottomY-2, rightX)
            )
        {
            posY = (bottomY)*BLOCKSIZE-height;
            speedY = 0;
            inJump = false;
        }
    }
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
    bool topleft     = level->isSolid (posY/BLOCKSIZE, posX/BLOCKSIZE);
    bool topright    = level->isSolid (posY/BLOCKSIZE, (posX+width)/BLOCKSIZE);
    bool bottomleft  = level->isSolid ((posY+height)/BLOCKSIZE, posX/BLOCKSIZE);
    bool bottomright = level->isSolid ((posY+height)/BLOCKSIZE, (posX+width)/BLOCKSIZE);
    
    if (topleft || topright || bottomleft || bottomright) return true;  
    return false; 
}

void Player::render()
{
    dstRect.x = SCALE*posX;
    dstRect.y = SCALE*posY;
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
