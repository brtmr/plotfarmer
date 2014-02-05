#include"Game.h"
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_TIMER ) !=0)
     {
         cout << "SDL Initialization error. " << SDL_GetError() << endl;
         exit(-1); 
     }

    SDL_Window* gameWindow = SDL_CreateWindow(
        "plotfarmer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0);
    if (gameWindow==NULL)
    {
         cout << "SDL Window Initialization error. " << SDL_GetError() << endl;
         exit(-1); 
    }

    SDL_Renderer* gameRenderer = SDL_CreateRenderer(
        gameWindow,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (gameRenderer==NULL)
    {
         cout << "SDL Renderer Initialization error. " << SDL_GetError() << endl;
         exit(-1); 
    }

    Game* plotfarmerGame = new Game(
        gameWindow,
        gameRenderer
    );
        
    plotfarmerGame->gameMainLoop();
    
    SDL_Quit();
}


Game::Game(SDL_Window* w, SDL_Renderer* r)
{
    gameWindow  =  w;
    gameRenderer = r;     
}

void Game::gameMainLoop()
{
    
    bool gameOver = false;
    SDL_Event e;
    while (!gameOver)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type == SDL_QUIT)
            {
            gameOver = true;
            }
        }
        update();
        render();
    }
            
}

void Game::update(){}

void Game::render(){}
