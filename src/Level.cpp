#include"Level.h"
#include<iostream>
#include<vector>
#include<fstream>

#define BLOCKSIZE 16

std::vector<std::vector<int>> dummyTiles();

Level::Level()
{
    
    tiles = dummyTiles();
    width  = 10;
    height = 10;
    pixelHeight = height*BLOCKSIZE;
    pixelWidth  = width*BLOCKSIZE;
    
}

Level::~Level()
{
    
    tiles = dummyTiles();
    
}


bool Level::isSolid(int i, int j)
{
    return tiles[i][j]!=-1;
}

std::vector<std::vector<int>> dummyTiles()
{
    const int width = 10;
    const int height = 10;
    std::vector<std::vector<int>> rows;
    for (int i=0; i<height; i++)
    {
        std::vector<int> row;
        for (int j=0; j<width; j++)
            {
                if ( i<6)  row.push_back(-1);
                if (i==6) row.push_back(0);
                if ( i>6)  row.push_back(3);
            }
        rows.push_back(row);
    }
    return rows;
}
