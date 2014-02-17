#include"Tilemanager.h"
#include"Spritesheet.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#define SCALE 4
#define BLOCKSIZE 16

Tilemanager::Tilemanager(SDL_Renderer* r, Level* l)
{
    gameRenderer = r;
    level        = l;

    
    /* load the spritesheet */
    spritesheet = new Spritesheet("sprites/16blox.png",1,5,5,gameRenderer);
    
    
    redraw = true;
    
    levelTexture = SDL_CreateTexture(
        gameRenderer,
        SDL_PIXELFORMAT_RGBA8888,  
        SDL_TEXTUREACCESS_TARGET, 
        10 * SCALE * BLOCKSIZE,   //Warning! 10 is set as a magic number
        10 * SCALE * BLOCKSIZE);  //needs to be replaced by some int member
                                 //defining the current level size.
}

Tilemanager::~Tilemanager()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyTexture(levelTexture);
    delete spritesheet;
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
        
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<10; j++)
            {
                if (level->isSolid(i,j))
                {
                    dstRec.x = SCALE * j * BLOCKSIZE;
                    dstRec.y = SCALE * i * BLOCKSIZE;
                    SDL_RenderCopy(
                        gameRenderer,
                        spritesheet->sprites,
                        &(spritesheet->clipRectangles.at((level->tiles)[i][j])),
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
    dstRec.w = SCALE * 10 * BLOCKSIZE;
    dstRec.h = SCALE * 10 * BLOCKSIZE;
    SDL_RenderCopy(
        gameRenderer,
        levelTexture,
        &(dstRec),
        &(dstRec)
        );
}
