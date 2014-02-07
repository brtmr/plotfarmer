#include"Tilemanager.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#define SCALE 4
#define BLOCKSIZE 32

Tilemanager::Tilemanager(SDL_Renderer* r)
{
    gameRenderer = r;
    SDL_Surface* blox = IMG_Load("sprites/blox.png");
    
    spritesheet = SDL_CreateTextureFromSurface(
        gameRenderer,
        blox
    );
    
    /* create Rectangles for clipping */
    int w = blox->w/4;
    int h = blox->  h;
    
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

    SDL_Rect rect4;
    rect4.x = 3*w;
    rect4.y = 0;
    rect4.w = w;
    rect4.h = h;

    clipRectangles.push_back(rect4);

    for (int i=0; i<5; i++)
    {
        for (int j=0; j<5; j++)
        {
            level[i][j]=-1;
        }
    }
    
    level[3][0]=0;
    level[3][1]=1;
    level[3][2]=2;
    level[3][3]=3;
    level[3][4]=3;
    
    redraw = true;
    
    SDL_RendererInfo info;
    SDL_GetRendererInfo(gameRenderer,&info);
    
    levelTexture = SDL_CreateTexture(
        gameRenderer,
        SDL_PIXELFORMAT_RGBA8888,  //Picking the first one may not be the best idea ...
                                  //But how do you manage which one is supported?
        SDL_TEXTUREACCESS_TARGET, 
        5 * SCALE * BLOCKSIZE,   //Warning! 5 is set as a magic number
        5 * SCALE * BLOCKSIZE);  //needs to be replaced by some int member
                                 //defining the current level size.
}

void Tilemanager::render()
{
    /**
     * if redraw set, draw the entire level on the levelTexture.
     * make sure to save the old renderTarget. 
     */
    SDL_Rect dstRec;
    
    if (true){
        
        
        
        dstRec.w = BLOCKSIZE * SCALE;
        dstRec.h = BLOCKSIZE * SCALE;
        
        SDL_SetRenderTarget(gameRenderer, levelTexture);
        SDL_RenderClear(gameRenderer);
        
        for (int i=0; i<5; i++)
        {
            for (int j=0; j<5; j++)
            {
                if (level[i][j]!=-1)
                {
                    dstRec.x = SCALE * j * BLOCKSIZE;
                    dstRec.y = SCALE * i * BLOCKSIZE;
                    SDL_RenderCopy(
                        gameRenderer,
                        spritesheet,
                        &(clipRectangles.at(level[i][j])),
                        &(dstRec)
                    );
                }
            }
        }
        
        redraw = false;
    }
    /**
    * copy the contents of the levelTexture onto the screen
    */
    SDL_SetRenderTarget(gameRenderer, NULL);
    dstRec.x = 0 ;
    dstRec.y = 0 ;
    dstRec.w = SCALE * 5 * BLOCKSIZE;
    dstRec.h = SCALE * 5 * BLOCKSIZE;
    SDL_RenderCopy(
        gameRenderer,
        levelTexture,
        &(dstRec),
        &(dstRec)
        );
}

