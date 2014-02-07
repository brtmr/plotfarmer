#include"Player.h"
#include<iostream>

#define SCALE 4

Player::Player(SDL_Renderer* renderer)
{

    /* load the spritesheet */
    SDL_Surface* playSurf = IMG_Load("sprites/wiz.png");    
    spritesheet = SDL_CreateTextureFromSurface( renderer, playSurf );
    
    
    /* create Rectangles for clipping */
    int w = playSurf->w/3;
    int h = playSurf->  h;
    
    SDL_Rect rect1;
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = w;
    rect1.h = h;

    clipRectangles.push_back(rect1);

    SDL_Rect rect2;
    rect2.x = w;
    rect2.y = 0;
    rect2.w = w;
    rect2.h = h;

    clipRectangles.push_back(rect2);

    SDL_Rect rect3;
    rect3.x = 2*w;
    rect3.y = 0;
    rect3.w = w;
    rect3.h = h;

    clipRectangles.push_back(rect3);

    gameRenderer = renderer;

    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = SCALE*w;
    dstRect.h = SCALE*h;

    posX = 20;
    posY = 20;
    speedX = 0.02;
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
        spritesheet,
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

    return &(clipRectangles.at(i));
}
