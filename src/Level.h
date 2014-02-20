#ifndef LEVEL_H
#define LEVEL_H

#include"Constants.h"
#include<iostream>
#include<vector>

class Level
{
    public:
        Level();
        ~Level();
        bool isSolid(int,int);
        int height;
        int width;
        int pixelHeight;
        int pixelWidth;
        int unscaledWidth;
        int unscaledHeight;
        std::vector<std::vector<int>> tiles;
    private:
        
};

#endif
