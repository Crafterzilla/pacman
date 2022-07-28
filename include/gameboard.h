#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "raylib.h"
#include <iostream>
#include <vector>
#include <list>
#include <array>

const char mazeSketch[31][29] =
{
    "############################",
    "#            ##            #",
    "#o#### ##### ## ##### ####o#",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "#                          #",
    "# #### ## ######## ## #### #",
    "# #### ## ######## ## #### #",
    "#      ##    ##    ##      #",
    "###### ##### ## ##### ######",
    "###### ##### ## ##### ######",
    "###### ##          ## ######",
    "###### ## ###--### ## ######",
    "###### ## ###  ### ## ######",
    "          #      #          ",
    "###### ## ######## ## ######",
    "###### ## ######## ## ######",
    "###### ##          ## ######",
    "###### ## ######## ## ######",
    "###### ## ######## ## ######",
    "#            ##            #",
    "# #### ##### ## ##### #### #",
    "# #### ##### ## ##### #### #",
    "#o  ##                ##  o#",
    "### ## ## ######## ## ## ###",
    "### ## ## ######## ## ## ###",
    "#      ##    ##    ##      #",
    "# ########## ## ########## #",
    "# ########## ## ########## #",
    "#                          #",
    "############################"
};
const int mazeWidth = 29, mazeHeight = 31;

class Walls {
private:
    std::list<Rectangle> walls;
    std::array<Rectangle, 2> doors;
public:
    Walls(Texture2D);
    bool WallCollsion(Rectangle) const;
    bool DoorCollision(Rectangle) const;
};

class Balls {
private:
    std::vector<Rectangle> ball;
    std::vector<Rectangle> bigBalls;
public:
    Balls(Walls&);
    unsigned int GetBallCount() {return ball.size();}
    void DrawBalls();
    void BallCollision(Rectangle);
    bool BigBallCollision(const Rectangle&) const;
    void RemoveBigBall(Rectangle);
};


void DrawGrid(int widthRes, int lengthRes, int scaleFactor);
void DisplayMouseCords();
//void BuildWalls(Texture2D);
#endif