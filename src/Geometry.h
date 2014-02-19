#ifndef GEOMETRY_H
#define GEOMETRY_H

struct rectangle
{
    float x0;
    float x1;
    float y0;
    float y1;
};

struct Point
{
    float x;
    float y;
};

struct Line
{
    Point from;
    Point to;
};

class Geometry
{
    public:
    static void getMTV(rectangle player, rectangle tile, float *x, float *y);
};

#endif
