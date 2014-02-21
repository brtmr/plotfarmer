#ifndef CONSTANTS_H
#define CONSTANTS_H

/* sizes & scales */
const int SCALE = 4;
const int BLOCKSIZE = 16;
const int SMALLOFFSET = 0;
const int SCALEDBLOCK = BLOCKSIZE * SCALE;
const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT = 480;

/* speeds and accelerations */
const float GRAVITY   = 0.0006 * SCALE;
const float SPEED     = 0.1 * SCALE;
const float JUMPSPEED = 0.2 * SCALE;
const int FALLCOUNTER = 4;

/* flags */
const int DIRECTIONLEFT  = 0;
const int DIRECTIONRIGHT = 1;

/* player bounding box */
const int PXOFFSETL = 9 * SCALE;
const int PXOFFSETR = 6 * SCALE;

/* for splitting the level into chunks for buffering */
const int CHUNKBORDER = 5;
const int REDRAWLIMIT = 1; 

/* display the grid + some info for debugging */ 
const bool DEBUG = false;
#endif
