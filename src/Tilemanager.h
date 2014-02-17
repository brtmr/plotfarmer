#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include<SDL2/SDL.h>
#include<vector>
#include"Spritesheet.h"
#include"Level.h"

class Tilemanager{
    
    public:
        
        Tilemanager(SDL_Renderer* r, Level* l);
        ~Tilemanager();
        void render();
        
    private:
        
        bool redraw;
        SDL_Renderer* gameRenderer;
        Spritesheet* spritesheet;
        SDL_Texture* levelTexture;
        void getClipRectangle(int n);
        Level* level;
    
    };
    
#endif
