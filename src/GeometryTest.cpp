#include<iostream>
#include"Geometry.h"


void printRectangle(rectangle r, std::string name);

int main(int argc, char** argv)
{
    float x,y;
    rectangle tile;
    rectangle player;
    
    std::cout << "MTV test" << std::endl;
    std::cout << "Test 1: Rectangles do not intersect." << std::endl;
    player.x0 = 1;
    player.x1 = 2;
    player.y0 = 1;
    player.y1 = 2;
    tile.x0 = 5;
    tile.x1 = 10;
    tile.y0 = 5;
    tile.y1 = 10;
    printRectangle(tile, "Tile");
    printRectangle(player, "Player");
    getMTV(player, tile, &x, &y);
    std::cout<< "MTV x: " << x << std::endl;
    std::cout<< "MTV y: " << y << std::endl;
    
    std::cout << "Test 2: Rectangles _do_ intersect, narrower penetration on x-Axis" << std::endl;
    player.x0 = 1;
    player.x1 = 6;
    player.y0 = 1;
    player.y1 = 8;
    tile.x0 = 5;
    tile.x1 = 10;
    tile.y0 = 5;
    tile.y1 = 10;
    printRectangle(tile, "Tile");
    printRectangle(player, "Player");
    getMTV(player, tile, &x, &y);
    std::cout<< "MTV x: " << x << std::endl;
    std::cout<< "MTV y: " << y << std::endl;
    
    std::cout << "Test 3: Rectangles _do_ intersect, narrower penetration on x-Axis" << std::endl;
    player.x0 = 6;
    player.x1 = 11;
    player.y0 = 8;
    player.y1 = 12;
    tile.x0 = 5;
    tile.x1 = 10;
    tile.y0 = 5;
    tile.y1 = 10;
    printRectangle(tile, "Tile");
    printRectangle(player, "Player");
    getMTV(player, tile, &x, &y);
    std::cout<< "MTV x: " << x << std::endl;
    std::cout<< "MTV y: " << y << std::endl;
}

void printRectangle(rectangle r, std::string name)
{
    std::cout << "###" << name << "###" << std::endl;
    std::cout << "x0: " << r.x0 << std::endl;
    std::cout << "x1: " << r.x1 << std::endl;
    std::cout << "y0: " << r.y0 << std::endl;
    std::cout << "y1: " << r.y1 << std::endl;
}
