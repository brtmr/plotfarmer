#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<vector>
#include<iostream>
#include"Constants.h"


class Spritesheet
{
    public:
        Spritesheet(std::string path, int m, int n, int p, SDL_Renderer* gameRenderer);
        ~Spritesheet();
        int drawSpriteAt(SDL_Renderer *renderer, int x, int y, int n, bool flip);

    private:
        SDL_Rect createClipRectangle(SDL_Surface*,int,int,int);
        SDL_Texture* sprites;
        std::vector<SDL_Rect> clipRectangles;
        int singleWidth;
        int singleHeight;
};

#endif
