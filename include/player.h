#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <iostream>
#include <cmath>
#include <string>

class Player {
private:
    Texture2D pacmanSprites;
    float x, y, timer;
    enum Direction {right, left, down, up, nodir};
    int currentDirection, nextDirection, frame;
    void RoundtoNearestFive(float&);
public:
    Rectangle hitbox;
    Player(Texture2D);
    void MovePlayer(bool collision);
    void DrawPlayer();
};

#endif