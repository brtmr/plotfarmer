#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include"Spritesheet.h"
#include"Level.h"
#include"Constants.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>

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
