#include"Level.h"

std::vector<std::vector<int>> dummyTiles();
std::vector<std::vector<int>> putplatform(std::vector<std::vector<int>>, int i, int j);

#define DUMMYW 70
#define DUMMYH 20

Level::Level()
{
    tiles = dummyTiles();
    width  = DUMMYW;
    height = DUMMYH;
    unscaledHeight = height*BLOCKSIZE;
    unscaledWidth = width*BLOCKSIZE;
    pixelHeight = height*SCALEDBLOCK;
    pixelWidth  = width*SCALEDBLOCK;
}

Level::~Level()
{
}


bool Level::isSolid(int i, int j)
{
    if (i>height-1 || j>width-1 || i<0 || j<0) return false;
    return tiles[i][j]!=-1;
}

std::vector<std::vector<int>> dummyTiles()
{
    const int width = DUMMYW;
    const int height = DUMMYH;
    std::vector<std::vector<int>> rows;
    for (int i=0; i<height; i++)
    {
        std::vector<int> row;
        for (int j=0; j<width; j++)
            {
                if ( i<12)  row.push_back(-1);
                if (i==12) row.push_back(j%2==0?0:1);
                if ( i>12 && i<=16)  row.push_back(2);
                if ( i>16)  row.push_back(4);
            }
        rows.push_back(row);
    }
    
    rows = putplatform(rows,4,0);
    rows = putplatform(rows,6,3);
    rows = putplatform(rows,8,6);
    rows = putplatform(rows,10,9);

    rows = putplatform(rows,8,12);
    rows = putplatform(rows,6,15);
    rows = putplatform(rows,4,18);
    
    rows = putplatform(rows,5,25);
    rows = putplatform(rows,6,30);
    rows = putplatform(rows,7,35);
    rows = putplatform(rows,8,40);
    rows = putplatform(rows,9,45);
    rows = putplatform(rows,10,50);
    rows = putplatform(rows,11,55);
    
    for (int i=0; i<height; ++i)
    rows[i][0] = -1;
    
    return rows;
}

std::vector<std::vector<int>> putplatform(std::vector<std::vector<int>> tiles, int i, int j)
{
    tiles[i][j++]=0;
    tiles[i][j++]=1;
    tiles[i][j++]=1;
    tiles[i][j++]=0;
    
    return tiles;
}
