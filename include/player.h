#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <iostream>
#include <cmath>
#include <string>

class Entity {
protected:
    Texture2D spriteSheet;
    float x, y, timer;
    int currentDirection, nextDirection, frame;
    enum Direction {right, left, down, up, nodir};
    void RoundtoNearest25(float&);
public:
    Rectangle hitbox;
    void DrawEntity();
};

class Player : public Entity {
public:
    Player(Texture2D);
    void MovePlayer(bool collision);
};

#endif