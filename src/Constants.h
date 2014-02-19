#ifndef CONSTANTS_H
#define CONSTANTS_H

/* sizes & scales */
const int BLOCKSIZE = 16;
const int SCALE = 4;
const int SMALLOFFSET = 0;
const int SCALEDBLOCK = BLOCKSIZE * SCALE;
const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT = 640;


/* speeds and accelerations */
const float GRAVITY   = 0.0004;
const float SPEED     = 0.05;
const float JUMPSPEED = 0.16;

/* flags */
const int DIRECTIONLEFT  = 0;
const int DIRECTIONRIGHT = 1;

/* player bounding box */
const int PXOFFSETL = 9;
const int PXOFFSETR = 6;

const bool DEBUG = 0;
#endif
