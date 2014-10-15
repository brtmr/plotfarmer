#ifndef GAME_H
#define GAME_H


#include"Level.h"
#include"Game.h"
#include"Player.h"
#include"MagicBullet.h"
#include"Level.h"
#include"Tilemanager.h"
#include"Constants.h"
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

class Game{

    public:
        Game(SDL_Window*, SDL_Renderer*);
        ~Game();
        void gameMainLoop();
        void render(float);

    private:
        //methods
        void update();
        bool gameOver;
        void handleKeys();
        //fields
        SDL_Window*   gameWindow;
        SDL_Renderer* gameRenderer;
        Level       level;
        Player      player;
        Tilemanager tilemanager;
        vec2di      camera;
        std::vector<std::shared_ptr<MovingObject>> gameObjects;
    };


#endif
