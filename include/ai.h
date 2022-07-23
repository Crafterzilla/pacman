#ifndef AI_H
#define AI_H

#include "raylib.h"
#include <iostream>
#include "player.h"

class Ghosts : public Entity {
private:
    float possibleDirections[4];
    enum {red, blue, pink, orange};
    int whichGhost;
    void RedAI(Rectangle& pacman);
    void BlueAI(Rectangle& pacman);
    void PinkAI(Rectangle& pacman);
    void OrangeAI(Rectangle& pacman);
public:
    Ghosts(Texture2D, int whichGhost);
    void MoveGhost(Rectangle& pacman);
    void DrawGhost();
};



#endif