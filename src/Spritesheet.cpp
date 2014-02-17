#include"Spritesheet.h"

/*
 * path is the filename of the spritesheet
 * m is the number of rows
 * n is the number of columns
 * p ist the total number of sprites in the sheet
 */

Spritesheet::Spritesheet(std::string path, int m, int n, int p, SDL_Renderer* gameRenderer)
{
    SDL_Surface* spritesSurface = IMG_Load(path.c_str());
    sprites = SDL_CreateTextureFromSurface(
        gameRenderer,
        spritesSurface
    );
    for(int i=0; i<p; i++){
        clipRectangles.push_back(createClipRectangle(spritesSurface, m, n, i));
        }
    singleWidth  = (spritesSurface->w)/n;
    singleHeight = (spritesSurface->h)/m;
    SDL_FreeSurface(spritesSurface);
}

Spritesheet::~Spritesheet()
{
    SDL_DestroyTexture(sprites);
}


/* 
 * This functionn returns the clipRectangle for a for the
 * ith sprite (zero-based) in a mxn spritesheet
 * where m is the number of rows
 * where n is the number of columns
 * */
SDL_Rect Spritesheet::createClipRectangle(SDL_Surface* spritesheet, int m, int n, int i)
{
    int w = (spritesheet->w)/n;
    int h = (spritesheet->h)/m;
    SDL_Rect result;
    result.w = w;
    result.h = h;
    result.x = (i%n)*w;
    result.y = (i/n)*h;
    return result;
}
