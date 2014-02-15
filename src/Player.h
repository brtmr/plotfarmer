#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<vector>

class Player{
    
    public:
        Player(SDL_Renderer*);
        ~Player();
        void setSpeedX();
        void setSpeedY();
        void render();
        void update(long);

            
    private:
        SDL_Rect dstRect;
        SDL_Texture* spritesheet;
        SDL_Renderer* gameRenderer;
        std::vector<SDL_Rect> clipRectangles;
        SDL_Rect* getCurrentRectangle();
        float speedX;
        float speedY;
        float posX;
        float posY;

        bool running;
        bool inJump;
    };

#endif
