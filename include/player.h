#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    Texture2D pacmanSprite;
    float x, y;
    Rectangle pacman;
public:
    Player(Texture2D);
    void MovePlayer();
    void DrawPlayer();
};

#endif