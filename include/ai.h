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
    Texture2D scaredGhost, floatEyes, regGhost;

    enum ghostType {red, blue, pink, orange};
    enum Mode{chase, scatter, scared, retreat, gameStart};
    int whichGhost, mode;
    float speed;
    float modeTimer;

    bool canGoThroughDoor;

    //Variables for method pathfind
    void PathFind(Rectangle&, Walls&);
    int nextDir[10], goToNextDir = 4,
    sizeNextDir = sizeof(nextDir) / sizeof(*nextDir);

    void RedAI(Player& pacman, Walls&);
    void BlueAI(Player& pacman, Rectangle&, Walls&);
    void PinkAI(Player& pacman, Walls&);
    void OrangeAI(Player& pacman, Walls&);

    void ModeChanger();

    void RetreatMode(Walls&);
    void ScaredMode(Walls&);
    void GameStartMode(Walls&);

public:
    Ghosts(Texture2D, Texture2D, Texture2D, int whichGhost);
    void MoveGhost(Player& pacman, Rectangle& redGhost,
    Walls& walls);
    void DrawGhost();
};



#endif