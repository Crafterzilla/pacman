#ifndef AI_H
#define AI_H

#include "raylib.h"
#include <iostream>
#include "player.h"
#include "gameboard.h"
#include <list>
#include <vector>
#include <ctime>

class Ghosts : public Entity {
private:
    enum ghostType {red, blue, pink, orange};
    enum Mode{chase, scatter, scared, retreat, gameStart};
    int whichGhost, mode;
    
    bool canGoThroughDoor;

    //Variables for method pathfind
    void PathFind(Rectangle&, Walls&);
    int nextDir[10], goToNextDir = 4,
    sizeNextDir = sizeof(nextDir) / sizeof(*nextDir);

    void RedAI(Player& pacman, Walls&);
    void BlueAI(Player& pacman, Walls&);
    void PinkAI(Player& pacman, Walls&);
    void OrangeAI(Player& pacman, Walls&);
public:
    Ghosts(Texture2D, int whichGhost);
    void MoveGhost(Player& pacman, Walls& walls);
    void DrawGhost();
};



#endif