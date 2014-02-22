#include"Game.h"

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
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        //SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
        0
        );
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
         cout << "SDL Renderer Initialization error. " << SDL_GetError() 
                << endl;
         exit(-1); 
    }
   
    if (IMG_INIT_PNG != IMG_Init(IMG_INIT_PNG))
    {
         cout << "SDL Renderer Initialization error. " << SDL_GetError() 
                << endl;
         exit(-1); 
    }
   
    if (IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG)
    {
         cout << "SDL Image Initialization Error. "  << endl;
         exit(-1); 
    }

    Game* plotfarmerGame = new Game(
        gameWindow,
        gameRenderer
    );
        
    plotfarmerGame->gameMainLoop();
    
    delete plotfarmerGame;
    
    SDL_Quit();
}


Game::Game(SDL_Window* w, SDL_Renderer* r) : 
    gameOver(false),
    gameWindow(w),
    gameRenderer(r),
    level(),
    player(r, level, camera),
    tilemanager(r, level, camera),
    camera({0,0})
{
}

Game::~Game(){
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    }

void Game::gameMainLoop()
{
    long next_game_tick = SDL_GetTicks();
    int loops;
    float interpolation;
    while( !gameOver ) {
        loops = 0;
        while( SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }

    interpolation = float( SDL_GetTicks() + SKIP_TICKS - next_game_tick )
                            / float( SKIP_TICKS );
        
    render(interpolation);
    }
}

void Game::handleKey(SDL_Event e)
{
    if(e.type ==SDL_KEYDOWN)
    {
        if ( e.key.keysym.sym == SDLK_LEFT)
        {
            player.setDirection(DIRECTIONLEFT);
        }
        if ( e.key.keysym.sym == SDLK_RIGHT)
        {
            player.setDirection(DIRECTIONRIGHT);
        }
        if ( e.key.keysym.sym == SDLK_UP)
        {
            player.jump();
        }
    }
    if(e.type ==SDL_KEYUP)
    {
        if ( e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
            player.stop();
    }
}

void Game::update()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)!=0)
    {
        if(e.type == SDL_QUIT)
        {
            gameOver = true;
        }
            if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
        {
            handleKey(e);
        }
    }
    player.update();
}

void Game::render(float interpolation){
    player.update_interp(interpolation);
    
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameRenderer);
    tilemanager.render();
    player.render();
    SDL_RenderPresent(gameRenderer);
    }
