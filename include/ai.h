#ifndef AI_H
#define AI_H

#include "raylib.h"
#include <iostream>

class Ghosts {
private:
    Texture2D ghostSkin;
    float x, y;
    Rectangle hitbox;
    enum {left, right, up, down, nodir};
    int currentDirection, nextDirection;
    int possibleDirections[4];
    enum {red, blue, pink, orange};
    int whichGhost;
    void RedAI();
    void BlueAI();
    void PinkAI();
    void OrangeAI();
public:
    Ghosts(Texture2D, int whichGhost);
    void DrawGhost();
    void MoveGhost();
};



#endif