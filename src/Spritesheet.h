#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<vector>
#include<iostream>


class Spritesheet
{
    public:
        Spritesheet(std::string path, int m, int n, int p, SDL_Renderer* gameRenderer);
        ~Spritesheet();
        SDL_Rect createClipRectangle(SDL_Surface*,int,int,int);
        SDL_Texture* sprites;
        std::vector<SDL_Rect> clipRectangles;
        int singleWidth;
        int singleHeight;
};

#endif
