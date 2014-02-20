#ifndef GEOMETRY_H
#define GEOMETRY_H

struct rectangle
{
    int x0;
    int x1;
    int y0;
    int y1;
};

struct vec2di
{
    int x;
    int y;
};

struct vec2df
{
    float x;
    float y;
};

class Geometry
{
    public:
    static void getMTV(rectangle player, rectangle tile, int *x, int *y);
};

#endif
