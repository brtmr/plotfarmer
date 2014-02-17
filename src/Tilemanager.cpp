#include"Tilemanager.h"


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
        level->pixelWidth,   
        level->pixelHeight);  
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
    
    if (redraw){
        
        dstRec.w = SCALEDBLOCK;
        dstRec.h = SCALEDBLOCK;
        
        SDL_SetRenderTarget(gameRenderer, levelTexture);
        SDL_RenderClear(gameRenderer);
        
        for (int i=0; i<(level->height); i++)
        {
            for (int j=0; j<(level->width); j++)
            {
                if (level->isSolid(i,j))
                {
                    dstRec.x = j * SCALEDBLOCK;
                    dstRec.y = i * SCALEDBLOCK;
                    SDL_RenderCopy(
                        gameRenderer,
                        spritesheet->sprites,
                        &(spritesheet->clipRectangles.at((level->tiles)[i][j])),
                        &(dstRec)
                    );
                }
                /*
                 * draw tile boundaries for debugging
                 * */
                if (DEBUG)
                {
                    dstRec.x = j * SCALEDBLOCK;
                    dstRec.y = i * SCALEDBLOCK;
                    SDL_SetRenderDrawColor(gameRenderer,0x66,0x0,0x0,0xFF);
                    SDL_RenderDrawRect(gameRenderer,&dstRec);
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
    dstRec.w = (level->pixelWidth);
    dstRec.h = (level->pixelHeight);
    SDL_RenderCopy(
        gameRenderer,
        levelTexture,
        NULL,
        &(dstRec)
        );
}
