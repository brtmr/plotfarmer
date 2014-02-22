#ifndef CONSTANTS_H
#define CONSTANTS_H

/* sizes & scales */
const int SCALE = 3;
const int BLOCKSIZE = 16;
const int SMALLOFFSET = 0;
const int SCALEDBLOCK = BLOCKSIZE * SCALE;
const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT = 768;

/* speeds and accelerations */
const float GRAVITY   = 0.6 * SCALE;
const float SPEED     = 4 * SCALE;
const float JUMPSPEED = 7 * SCALE;
const int FALLCOUNTER = 4;
const float SPEEDLIMIT = SCALEDBLOCK / 2.1; 

const int BULLETSPEED = SPEEDLIMIT;

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
const bool DEBUG = 0;

/* DeWitters Game Loop */ 
const int TICKS_PER_SECOND = 40;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

const int BULLET_LIFETIME = 20;
#endif
