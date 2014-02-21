#include"Tilemanager.h"


Tilemanager::Tilemanager(SDL_Renderer* r, Level* l, vec2di *c)
{
    gameRenderer = r;
    level        = l;
    camera       = c;
    spritesheet = new Spritesheet("sprites/16blox.png",1,5,5,gameRenderer);
    redraw = true;
    
    skyTexture = SDL_CreateTexture(
        gameRenderer,
        SDL_PIXELFORMAT_RGBA8888,  
        SDL_TEXTUREACCESS_TARGET, 
        SCREEN_WIDTH / SCALE,
        SCREEN_HEIGHT / SCALE
        );
    drawSky();
}

Tilemanager::~Tilemanager()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyTexture(skyTexture);
    delete spritesheet;
}


void Tilemanager::render()
{
    SDL_RenderCopy(
        gameRenderer,
        skyTexture,
        NULL,
        NULL
        );
    
    SDL_Rect dstRec;
    dstRec.w = SCALEDBLOCK;
    dstRec.h = SCALEDBLOCK;
    
    int tileOffsetX = camera->x / SCALEDBLOCK;
    int tileOffsetY = camera->y / SCALEDBLOCK;
    int pixelOffsetX = tileOffsetX * SCALEDBLOCK - camera->x;
    int pixelOffsetY = tileOffsetY * SCALEDBLOCK - camera->y;
    for (int i=0 ; i<(SCREEN_HEIGHT / SCALEDBLOCK) + 2  ; i++)
    {
        for (int j=0 ; j<(SCREEN_WIDTH / SCALEDBLOCK) + 2 ; j++)
        {
            int iTile = i + tileOffsetY;
            int jTile = j + tileOffsetX;
            
            if (level->isSolid(iTile,jTile))
            {
                dstRec.x = j * SCALEDBLOCK + pixelOffsetX;
                dstRec.y = i * SCALEDBLOCK + pixelOffsetY;
                SDL_RenderCopy(
                    gameRenderer,
                    spritesheet->sprites,
                    &((spritesheet->clipRectangles).at(level->tiles[iTile][jTile])),
                    &(dstRec)
                    );
            }
            
            if (DEBUG)
            {
                if ( iTile < level->height && jTile < level->width )
                {
                    SDL_SetRenderDrawColor(gameRenderer,0,0,0,0);
                    dstRec.x = j * SCALEDBLOCK + pixelOffsetX;
                    dstRec.y = i * SCALEDBLOCK + pixelOffsetY;
                    SDL_RenderDrawRect(
                        gameRenderer,
                        &(dstRec)
                    );
                }
            }
        }
    }
}

void Tilemanager::drawSky()
{
    SDL_Surface* skySurface = IMG_Load("sprites/sky.png");
    skyTexture = SDL_CreateTextureFromSurface
        (gameRenderer, skySurface);
}
