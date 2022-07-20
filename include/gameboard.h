#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "raylib.h"
#include <iostream>

class Walls {
private:
    //The four hitboxes for the main four walls of the game
    Rectangle topWall, bottomWall, leftWall,
    rightWall;
    //All the hitboxes on the sides
    Rectangle bigLeftBoxTop, bigLeftBoxBottom, 
    bigRightBoxTop, bigRightBoxBottom, middleBox, smallLeftBox, smallRightBox;
    //All the top hitboxes
    Rectangle left1, left2, left3, right1, right2, right3;
    //Those weird t-shaped things in the top hitboxes
    Rectangle t1top, t1bottom, t2top, t2bottom, t3top, t3bottom;
    //The Rectangles on the bottom half
    Rectangle left4, left5, right4, right5;
    //Those l-shaped things on the bottom hitboxes
    Rectangle l1top, l1bottom, l2top, l2bottom;
    //The rest of the t-shaped things on the bottom hitboxes
    Rectangle t4top, t4bottom, t5top, t5bottom, t6top, t6bottom,
    t7top, t7bottom;
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