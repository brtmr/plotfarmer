#include"Player.h"
#include"Spritesheet.h"
#include<iostream>

#define SCALE 4

Player::Player(SDL_Renderer* renderer)
{

    gameRenderer = renderer;
    /* load the spritesheet */
    spritesheet = new Spritesheet("sprites/wiz.png",1,3,3,renderer);
    
    /* set initial position*/
    posX = 5;
    posY = 20;
    speedX = 0.02;
        
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = SCALE*(spritesheet->singleWidth);
    dstRect.h = SCALE*(spritesheet->singleHeight);

}

Player::~Player()
{
    delete spritesheet;
}

void Player::update(long dt)
{
   posX = posX + speedX*dt;
   posY = posY + speedY*dt;
    
   dstRect.x = SCALE*posX;
   dstRect.y = SCALE*posY;
}

void Player::render()
{
    SDL_RenderCopy(
        gameRenderer,
        spritesheet->sprites,
        getCurrentRectangle(),
        &dstRect   
    ); 
}

SDL_Rect* Player::getCurrentRectangle()
{
    int i;
    int spriteDuration = 80; 
    long which = SDL_GetTicks()/spriteDuration;
    if (which % 4 == 0) i = 0;
    if (which % 4 == 1) i = 1;
    if (which % 4 == 2) i = 2;
    if (which % 4 == 3) i = 1;

    return &(spritesheet->clipRectangles.at(i));
}
