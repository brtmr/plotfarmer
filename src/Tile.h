#ifndef TILE_H
#define TILE_H

#include"Constants.h"
#include"Spritesheet.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Tile
{
    public: 
        Tile();
        ~Tile();
        int getHealth();
        void damage(int damage);
        void repair();
        void render(SDL_Renderer *gameRenderer, SDL_Rect *dstRec);
        bool isSolid();
        
    private:
        /* rendering info */
        Spritesheet &spritesheet;
        SDL_Rect *clipRectangle;
        
        /* physical info */
        bool solid;
        int health;
        
        //Item contains;
        
                
};

#endif
