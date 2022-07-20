#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "raylib.h"
#include <iostream>

class Walls {
private:
    Rectangle topWall, bottomWall, leftWall,
    rightWall;
public:
    Walls(Texture2D);
    bool WallCollsion(Rectangle);
};

class GameCondtions {
public:
    bool IsPlayerAlive, playerAndWallCollsion;
    GameCondtions();
};

void DrawGrid(int widthRes, int lengthRes, int scaleFactor);
void DisplayMouseCords();
//void BuildWalls(Texture2D);
#endif