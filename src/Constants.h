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
const float GRAVITY   = 0.0006 * SCALE;
const float SPEED     = 0.1 * SCALE;
const float JUMPSPEED = 0.2 * SCALE;

/* flags */
const int DIRECTIONLEFT  = 0;
const int DIRECTIONRIGHT = 1;

/* player bounding box */
const int PXOFFSETL = 9 * SCALE;
const int PXOFFSETR = 6 * SCALE;
const int ONEPIXEL = 1;

const bool DEBUG = 1;
#endif
