#include "Geometry.h"
#include <cmath>

using namespace std;

/*
 * Provides various Geometry related functions,
 * mainly used for collision detection and handling
 */

/* returns the minimum translation vector for the player to leave the
 * tile */
void Geometry::getMTV(rectangle player, rectangle tile, int *x, int *y)
{
    *x = 0;
    *y = 0;
    //rectangles do _not_ intersect.
    if ( ((tile.x1 <= player.x0) || (tile.x0 >= player.x1))
            ||  ((tile.y1 <= player.y0) || (tile.y0 >= player.y1)) )
    {
        return;
    }
    //x values _do_ intersect.
    if ( !((tile.x1 <= player.x0) || (tile.x0 >= player.x1)) )
    {
        float right = tile.x1 - player.x0;
        float left  = tile.x0 - player.x1;
        *x = (abs(right) < abs(left)) ? right : left;
    }
    //y values _do_ intersect.
    if ( !((tile.y1 <= player.y0) || (tile.y0 >= player.y1)) )
    {
        float up    = tile.y1 - player.y0;
        float down  = tile.y0 - player.y1;
        *y = (abs(up) < abs(down)) ? up : down;
    }
    //we want the smallest push, so check wether atleast one coordinate
    //is zero, if not, eliminate the bigger one.
    if (*y != 0 && *x != 0)
    {
        if (abs(*y) <= abs(*x))
            *x = 0;
        else
            *y = 0;
    }
}
