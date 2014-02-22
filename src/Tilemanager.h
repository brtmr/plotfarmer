#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include"Geometry.h"
#include"Spritesheet.h"
#include"Level.h"
#include"Constants.h"
#include"Player.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>

class Tilemanager{
    
    public:
        
        Tilemanager(SDL_Renderer* r, Level &l, vec2di &c);
        ~Tilemanager();
        void render();
        void drawSky();
        
    private:
        //functions
        void getClipRectangle(int n);
        //fields
        bool redraw;
        SDL_Renderer* gameRenderer;
        SDL_Texture* skyTexture;
        Spritesheet spritesheet;
        Level  &level;
        vec2di &camera;
        /* for splitting the level into chunks to be drawn*/

    };
    
#endif
