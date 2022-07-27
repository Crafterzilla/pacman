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
    int nextDirection, frame, moveX = 0, moveY = 0;
    enum Direction {right, left, down, up, nodir};
    void RoundtoNearest25(float&);
    Vector2 Rotate180DegreesFromOrigin(Vector2, Vector2);
public:
    void DrawEntity();
    Rectangle hitbox;
    int currentDirection;
};

class Player : public Entity {
public:
    Player(Texture2D);
    void MovePlayer(bool collision, bool doorCollision);
    // void DrawPlayer();
};

#endif