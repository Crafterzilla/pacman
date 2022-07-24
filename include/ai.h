#ifndef AI_H
#define AI_H

#include "raylib.h"
#include <iostream>
#include "player.h"
#include "gameboard.h"
#include <list>
#include <vector>

class Ghosts : public Entity {
private:
    enum {red, blue, pink, orange};
    int whichGhost;
    void RedAI(Rectangle& pacman, Walls&);
    void BlueAI(Rectangle& pacman, Walls&);
    void PinkAI(Rectangle& pacman, Walls&);
    void OrangeAI(Rectangle& pacman, Walls&);
public:
    Ghosts(Texture2D, int whichGhost);
    void MoveGhost(Rectangle& pacman, Walls& walls);
    void DrawGhost();
};



#endif