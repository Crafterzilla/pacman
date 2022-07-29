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


    float modeTimer, scaredTimer;

    bool canGoThroughDoor;

    //Variables for method pathfind
    void PathFind(const Rectangle&, const Walls&);
    int nextDir[10], goToNextDir = 4,
    sizeNextDir = sizeof(nextDir) / sizeof(*nextDir);

    void RedAI(const Player& pacman, const Walls&);
    void BlueAI(const Player& pacman, const Rectangle&, const Walls&);
    void PinkAI(const Player& pacman, const Walls&);
    void OrangeAI(const Player& pacman, const Walls&);

    void ModeChanger();

    void RetreatMode(const Walls&);
    void ScaredMode(const Player& pacman, const Walls&);
    void GameStartMode(const Walls&);

public:
    Ghosts(Texture2D, Texture2D, Texture2D, int whichGhost, float ghostSpeed);
    int GetGhostMode() {return this->mode;}
    void SetGhostModeTimer(float modeTimer) {this->modeTimer = modeTimer;}
    float GetGhostModeTimer() {return this->modeTimer;}
    void MoveGhost(const Player& pacman, const Rectangle& redGhost,
    const Walls& walls);
    void DrawGhost();
    void CheckConditions(bool);
};



#endif