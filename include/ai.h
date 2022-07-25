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
    enum ghostType {red, blue, pink, orange};
    enum Mode{chase, scatter, random, retreat};
    int whichGhost, mode;

    void PathFind(Rectangle&, Walls&);


    void RedAI(Rectangle& pacman, Walls&, int mode);
    void RedAIRandom();
    void RedAiRetreat();

    void BlueAI(Rectangle& pacman, Walls&);
    void PinkAI(Rectangle& pacman, Walls&);
    void OrangeAI(Rectangle& pacman, Walls&);
public:
    Ghosts(Texture2D, int whichGhost);
    void MoveGhost(Rectangle& pacman, Walls& walls);
    void DrawGhost();
};



#endif