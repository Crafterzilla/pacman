#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "raylib.h"
#include <iostream>
#include <vector>
#include <list>

class Walls {
private:
    std::list<Rectangle> walls;

public:
    Walls(Texture2D);
    bool WallCollsion(Rectangle);
};

class GameCondtions {
public:
    bool IsPlayerAlive, playerAndWallCollsion;
    GameCondtions();
    void PacmanAteBall(Rectangle);
};

class Balls {
private:
    std::vector<Rectangle> ball;

public:
    Balls(Walls&);
    void DrawBalls();
    void BallCollision(Rectangle);
};


void DrawGrid(int widthRes, int lengthRes, int scaleFactor);
void DisplayMouseCords();
//void BuildWalls(Texture2D);
#endif