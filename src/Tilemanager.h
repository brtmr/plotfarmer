#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include<SDL2/SDL.h>
#include<vector>

class Tilemanager{
    
    public:
        
        Tilemanager(SDL_Renderer* r);
        ~Tilemanager();
        void render();
        
    private:
        
        bool redraw;
        int level[5][5];
        SDL_Renderer* gameRenderer;
        SDL_Texture* spritesheet;
        SDL_Texture* levelTexture;
        std::vector<SDL_Rect> clipRectangles;
    
    };
    
#endif
