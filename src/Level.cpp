#include"Level.h"

std::vector<std::vector<int>> dummyTiles();

Level::Level()
{
    
    tiles = dummyTiles();
    width  = 20;
    height = 10;
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
    const int width = 20;
    const int height = 10;
    std::vector<std::vector<int>> rows;
    for (int i=0; i<height; i++)
    {
        std::vector<int> row;
        for (int j=0; j<width; j++)
            {
                if ( i<6)  row.push_back(-1);
                if (i==6) row.push_back(0);
                if ( i>6 && i<=8)  row.push_back(2);
                if ( i>8)  row.push_back(4);
            }
        rows.push_back(row);
    }
    
    
    rows[6][4]=2;
    rows[6][5]=2;
    rows[6][6]=2;
    rows[6][7]=2;
    rows[5][4]=0;
    rows[5][5]=1;
    rows[5][6]=1;
    rows[5][7]=0;
    rows[5][14]=1;
    rows[4][9]=0;
    rows[4][10]=1;
    rows[4][11]=1;
    rows[4][12]=0;
    rows[2][0]=3;
    rows[2][1]=2;
    rows[2][0]=3;
    rows[3][2]=2;
    rows[0][0]=3;
    rows[1][0]=3;
    rows[2][0]=3;
    rows[3][0]=3;
    rows[4][0]=3;
    rows[5][0]=3;
    
    return rows;
}
