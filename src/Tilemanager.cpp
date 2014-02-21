#include"Tilemanager.h"


Tilemanager::Tilemanager(SDL_Renderer* r, Level* l, vec2di *c)
{
    gameRenderer = r;
    level        = l;
    camera       = c;
    spritesheet = new Spritesheet("sprites/16blox.png",1,5,5,gameRenderer);
    redraw = true;
    
    chunkOrigin.x = 0;
    chunkOrigin.y = 0;
    chunkWidth  = (SCREEN_WIDTH  / SCALEDBLOCK) + 2 * CHUNKBORDER;
    chunkHeight = (SCREEN_HEIGHT / SCALEDBLOCK) + 2 * CHUNKBORDER;
    if (chunkWidth >level->width )chunkWidth  = level-> width;
    if (chunkHeight>level->height)chunkHeight = level->height;
    levelTexture = SDL_CreateTexture(
        gameRenderer,
        SDL_PIXELFORMAT_RGBA8888,  
        SDL_TEXTUREACCESS_TARGET, 
        chunkWidth  * SCALEDBLOCK,   
        chunkHeight * SCALEDBLOCK
        );
        
    skyTexture = SDL_CreateTexture(
        gameRenderer,
        SDL_PIXELFORMAT_RGBA8888,  
        SDL_TEXTUREACCESS_TARGET, 
        SCREEN_WIDTH / SCALE,
        SCREEN_HEIGHT / SCALE
        );
    drawSky();
    drawNewChunk();
}

Tilemanager::~Tilemanager()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyTexture(levelTexture);
    delete spritesheet;
}

vec2di Tilemanager::calculateNewOrigin()
{
    vec2di newChunkOrigin;
    newChunkOrigin.x = chunkOrigin.x;
    newChunkOrigin.y = chunkOrigin.y;
    //screen positions in tile space
    int screenLeftTile  = ( camera->x ) / SCALEDBLOCK ;
    int screenRightTile = ( camera->x + SCREEN_WIDTH ) / SCALEDBLOCK ;
    int screenTopTile   = ( camera->y ) / SCALEDBLOCK ;
    int screenDownTile  = ( camera->y + SCREEN_HEIGHT ) / SCALEDBLOCK ;
    int leftLimit       = (chunkOrigin.x + REDRAWLIMIT);
    int rightLimit      = (chunkOrigin.x + chunkWidth - REDRAWLIMIT);
    int topLimit        = (chunkOrigin.y + REDRAWLIMIT);
    int bottomLimit     = (chunkOrigin.y + chunkHeight - REDRAWLIMIT);
    int centerOnX       = ( camera->x ) / SCALEDBLOCK - CHUNKBORDER;
    int centerOnY       = ( camera->y ) / SCALEDBLOCK - CHUNKBORDER;
    //if positions exceed limits, set new chunk.
    if (screenLeftTile < leftLimit || screenRightTile > rightLimit)
        newChunkOrigin.x = centerOnX;
    if (screenTopTile < topLimit || screenDownTile > bottomLimit);
        newChunkOrigin.y = centerOnY;
    //the chunk mustnt overlap with the level edges
    if (newChunkOrigin.x > (level->width ) - chunkWidth ) 
        newChunkOrigin.x = (level->width ) - chunkWidth;
    if (newChunkOrigin.y > (level->height) - chunkHeight) 
        newChunkOrigin.y = (level->height) - chunkWidth;
    if (newChunkOrigin.y<0) newChunkOrigin.y = 0;
    if (newChunkOrigin.x<0) newChunkOrigin.x = 0;
    return newChunkOrigin;
}

void Tilemanager::drawNewChunk()
{
    SDL_Rect dstRec;
    //std::cout << "Drawing new Chunk at " << chunkOrigin.x << " | " << chunkOrigin.y << std::endl;
    dstRec.w = SCALEDBLOCK;
    dstRec.h = SCALEDBLOCK;
    SDL_SetRenderTarget(gameRenderer, levelTexture);
    //SDL_SetRenderDrawColor(gameRenderer,0xAA,0x0,0x0,0x00);
    SDL_RenderClear(gameRenderer);
    
    for (int i=0; i<chunkHeight; i++)
    {
        for (int j=0; j<chunkWidth; j++)
        {
            if (level->isSolid((i + chunkOrigin.y),(j + chunkOrigin.x)))
            {
                dstRec.x = j * SCALEDBLOCK;
                dstRec.y = i * SCALEDBLOCK;
                SDL_RenderCopy(
                    gameRenderer,
                    spritesheet->sprites,
                    &( spritesheet->clipRectangles.at((level->tiles)[i + chunkOrigin.y][j + chunkOrigin.x]) ),
                    &(dstRec)
                );
            }
            if (DEBUG)
            {
                if (j < CHUNKBORDER || j > chunkWidth-CHUNKBORDER || i < CHUNKBORDER || i > chunkHeight-CHUNKBORDER)
                     SDL_SetRenderDrawColor(gameRenderer,0xFF,0xFF,0xFF,0xFF);
                else SDL_SetRenderDrawColor(gameRenderer,0xAA,0x0,0x0,0xFF);
                dstRec.x = j * SCALEDBLOCK;
                dstRec.y = i * SCALEDBLOCK;
                
                SDL_RenderDrawRect(gameRenderer,&dstRec);
            }
       }
    }
    //SDL_RenderPresent(gameRenderer);
    SDL_SetRenderTarget(gameRenderer, NULL);
}

void Tilemanager::render()
{
    /* if necessary, redraw the current chunk of the level onto the buffer */
    vec2di newChunkOrigin = calculateNewOrigin();
    if ( newChunkOrigin.x != chunkOrigin.x || newChunkOrigin.y != chunkOrigin.y )
        {
        chunkOrigin.x = newChunkOrigin.x;
        chunkOrigin.y = newChunkOrigin.y;
        drawNewChunk();
        }
    /* copy th sky buffer onto the screen */
    SDL_SetTextureBlendMode(levelTexture,
                            SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(skyTexture,
                           SDL_BLENDMODE_NONE);
    SDL_Rect srcRec;
    SDL_Rect dstRec;
    SDL_RenderCopy(
        gameRenderer,
        skyTexture,
        NULL,
        NULL
        );
    /* copy the buffer onto the screen. */
    
    srcRec.x = camera->x - (chunkOrigin.x * SCALEDBLOCK);
    srcRec.y = camera->y - (chunkOrigin.y * SCALEDBLOCK);
    srcRec.w = SCREEN_WIDTH;
    srcRec.h = SCREEN_HEIGHT;
    dstRec.x = 0;
    dstRec.y = 0;
    dstRec.w = SCREEN_WIDTH;
    dstRec.h = SCREEN_HEIGHT;
    SDL_RenderCopy(
        gameRenderer,
        levelTexture,
        &(srcRec),
        &(dstRec)
        );
    
}

void Tilemanager::drawSky()
{
    SDL_Surface* skySurface = IMG_Load("sprites/sky.png");
    skyTexture = SDL_CreateTextureFromSurface
        (gameRenderer, skySurface);
}
