#include"Player.h"


Player::Player(SDL_Renderer *renderer, Level &l, vec2di &c, int x, int y):
    super(x*SCALEDBLOCK, y*SCALEDBLOCK, renderer, c, true),
    spritesheet("sprites/wiz_staff_down.png", 1, 3, 3, renderer),
    level(l),
    height(spritesheet.singleHeight*SCALE),
    width(spritesheet.singleWidth*SCALE),
    direction(DIRECTIONRIGHT),
    running(false),
    inJump(true),
    dstRect({0, 0, width, height}),
        bullet_counter(0)
{}

Player::~Player()
{
}

void Player::update()
{
    super::update();
    stayInLevel();
    updateBounding();
    handleCollision();
    handleCollision();
    if (bullet_counter != 0) bullet_counter--;
}

void Player::stayInLevel()
{
    if ( pos.y + height > (level.height * SCALEDBLOCK) )
    {
        pos.y = (level.height * SCALEDBLOCK) - height - SMALLOFFSET;
        vel.y = 0;
        inJump = false;
    }
    if ( pos.x + width > (level.width * SCALEDBLOCK) )
    {
        pos.x = (level.width * SCALEDBLOCK) - width - SMALLOFFSET;
        vel.x = 0;
    }
    if ( pos.y < 0 )
    {
        pos.y = SMALLOFFSET;
        vel.y = 0;
    }
    if ( pos.x < 0 )
    {
        pos.x = SMALLOFFSET;
        vel.x = 0;
    }
}

void Player::setCamera()
{
    if (interppos.x < SCREEN_WIDTH / 2)
        camera.x = 0;
    else if (interppos.x > (level.pixelWidth) - (SCREEN_WIDTH / 2))
        camera.x = (level.pixelWidth) - SCREEN_WIDTH;
    else
        camera.x = interppos.x - SCREEN_WIDTH / 2;
    if (interppos.y < SCREEN_HEIGHT / 2)
        camera.y = 0;
    else if (interppos.y > (level.pixelHeight) - (SCREEN_HEIGHT / 2))
        camera.y = (level.pixelHeight) - SCREEN_HEIGHT;
    else
        camera.y = interppos.y - SCREEN_HEIGHT / 2;
}

void Player::updateBounding()
{
    bounding.x0 = pos.x +         ((direction == DIRECTIONRIGHT) ? PXOFFSETL : PXOFFSETR);
    bounding.x1 = pos.x + width - ((direction == DIRECTIONRIGHT) ? PXOFFSETR : PXOFFSETL);
    bounding.y0 = pos.y;
    bounding.y1 = pos.y + height;
}
/**
 * Uses a minimum translation vector approach,
 * simplified to axis-aligned rectangles to deal woth collision
 * http://elancev.name/oliver/2D%20polygon.htm
 */

void Player::handleCollision()
{
    interpXcnt = (interpXcnt > 0) ? interpXcnt - 1 : interpXcnt;
    int mini = bounding.y0 / SCALEDBLOCK;
    int maxi = bounding.y1 / SCALEDBLOCK;
    int minj = bounding.x0 / SCALEDBLOCK;
    int maxj = bounding.x1 / SCALEDBLOCK;
    rectangle tile;
    int x, y;
    for (int i = mini; i <= maxi; i++)
    {
        for (int j = minj; j <= maxj; j++)
        {
            if (level.isSolid(i, j))
            {
                tile.x0 = j * SCALEDBLOCK;
                tile.x1 = (j + 1) * SCALEDBLOCK;
                tile.y0 = i * SCALEDBLOCK;
                tile.y1 = (i + 1) * SCALEDBLOCK;
                Geometry::getMTV(bounding, tile, &x, &y);
                pos.x = pos.x + x;
                if (x != 0)
                {
                    interpXcnt = 1;
                    vel.x = 0;
                }
                updateBounding();
            }
        }
    }
    for (int i = mini; i <= maxi; i++)
    {
        for (int j = minj; j <= maxj; j++)
        {
            if (level.isSolid(i, j))
            {
                tile.x0 = j * SCALEDBLOCK;
                tile.x1 = (j + 1) * SCALEDBLOCK;
                tile.y0 = i * SCALEDBLOCK;
                tile.y1 = (i + 1) * SCALEDBLOCK;
                Geometry::getMTV(bounding, tile, &x, &y);
                pos.y = pos.y + y;
                if (x != 0)
                {
                    interpXcnt = 1;
                    vel.x = 0;
                }
                updateBounding();
            }
        }
    }
    if (solidAbove())
    {
        if (vel.y < 0) vel.y = 0;
    }
    if (solidBelow())
    {
        vel.y = 0;
        inJump = false;
    }
}

bool Player::solidAbove()
{
    int i  = ((bounding.y0 - 1) / SCALEDBLOCK);
    int j0 = ((bounding.x0 + 1) / SCALEDBLOCK);
    int j1 = ((bounding.x1 - 1) / SCALEDBLOCK);

    if ( level.isSolid(i, j0) ||  level.isSolid(i, j1) )
    {
        return true;
    }
    return false;
}

bool Player::solidBelow()
{
    int i  = ((bounding.y1 + 1) / SCALEDBLOCK);
    int j0 = ((bounding.x0 + 1) / SCALEDBLOCK);
    int j1 = ((bounding.x1 - 1) / SCALEDBLOCK);

    if ( level.isSolid(i, j0) ||  level.isSolid(i, j1) )
    {
        return true;
    }
    return false;
}

void Player::setDirection(int d)
{
    running = true;
    if (d == DIRECTIONLEFT)
    {
        direction = DIRECTIONLEFT;
        vel.x = -SPEED;
    }
    if (d == DIRECTIONRIGHT)
    {
        direction = DIRECTIONRIGHT;
        vel.x = SPEED;
    }
}

void Player::stop()
{
    vel.x = 0;
    running = false;
}

void Player::jump()
{
    if (inJump || vel.y < 0) return;
    vel.y = -JUMPSPEED;
    inJump = true;
}

vec2di Player::getTile()
{
    vec2di result;
    result.x = pos.y / SCALEDBLOCK;
    result.y = pos.x / SCALEDBLOCK;
    return result;
}

void Player::render()
{
    vec2di renderpos;
    renderpos.x = (interppos.x) + roundf(interpremainder.x);
    renderpos.y = (interppos.y) + roundf(interpremainder.y);
    dstRect.x = renderpos.x - camera.x;
    dstRect.y = renderpos.y - camera.y;
    if (direction == DIRECTIONRIGHT)
        SDL_RenderCopy(
            gameRenderer,
            spritesheet.sprites,
            getCurrentRectangle(),
            &dstRect
        );
    if (direction == DIRECTIONLEFT)
        SDL_RenderCopyEx(
            gameRenderer,
            spritesheet.sprites,
            getCurrentRectangle(),
            &dstRect,
            0,
            NULL,
            SDL_FLIP_HORIZONTAL
        );
}

SDL_Rect* Player::getCurrentRectangle()
{
    if (inJump)
        return &(spritesheet.clipRectangles.at(2));
    if (!running)
        return &(spritesheet.clipRectangles.at(0));
    int i;
    int spriteDuration = 80;
    long which = SDL_GetTicks() / spriteDuration;
    if (which % 4 == 0) i = 0;
    if (which % 4 == 1) i = 1;
    if (which % 4 == 2) i = 2;
    if (which % 4 == 3) i = 1;
    return &(spritesheet.clipRectangles.at(i));
}

/* just updates the interpolated values. does _not_ change game state */
void Player::update_interp(int interpolation)
{
    super::update_interp(interpolation);
    setCamera();
}

vec2di Player::getStaffPosition()
{
    if (direction == DIRECTIONRIGHT)
        return {pos.x + 12 * SCALE, pos.y + 17 * SCALE};
    else
        return {pos.x + 3 * SCALE, pos.y + 17 * SCALE};
}

short Player::getDirection()
{
    return direction;
}

bool Player::readyToFire()
{
    return (bullet_counter == 0);
}

void Player::hightenBulletCounter()
{
    bullet_counter = FRAMES_PER_BULLET;
}
