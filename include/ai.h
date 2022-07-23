#ifndef AI_H
#define AI_H

#include "raylib.h"
#include <iostream>
#include "player.h"

class Ghosts : public Entity {
private:
    int possibleDirections[4];
    enum {red, blue, pink, orange};
    int whichGhost;
    void RedAI();
    void BlueAI();
    void PinkAI();
    void OrangeAI();
public:
    Ghosts(Texture2D, int whichGhost);
    void MoveGhost();
    void DrawGhost();
};



#endif