#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    Texture2D pacmanSprites;
    float x, y, timer;
    enum Direction {right, left, down, up, nodir};
    int currentDirection, frame;
public:
    Rectangle hitbox;
    Player(Texture2D);
    void MovePlayer();
    void DrawPlayer();
};

#endif