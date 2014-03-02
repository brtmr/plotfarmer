#include"Tile.h"

bool Tile::isSolid()
{
    return solid;
}

void Tile::render(SDL_Renderer *gameRenderer, SDL_Rect *dstRec)
{
    SDL_RenderCopy(
        gameRenderer,
        spritesheet.sprites,
        clipRectangle,
        dstRec
    );
}


void Tile::damage(int damage)
{
    health = health-damage;
    if (health <= 0)
        {
        health = 0;
        solid  = false;
        }
}
