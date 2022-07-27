#ifndef GAMECONDITIONS_H
#define GAMECONDITIONS_H

#include "raylib.h"
#include "player.h"
#include "ai.h"
#include "gameboard.h"

class GameConditions {
private:
    Ghosts& redGhost, blueGhost, pinkGhost, orangeGhost;
    Player& pacman;
    Balls& balls;
    Walls& walls;
    bool IsPlayerAlive, playerAndWallCollsion,
    ghostsFrightened;
public:
    GameConditions(Ghosts&, Ghosts&, Ghosts&,
    Ghosts&, Player&, Balls&, Walls&);

    void PacmanAteBall(Rectangle);

    void CheckIfPacmanAteBigBall();
    void MoveAllGhosts();
    void DrawAllGhost();
};

#endif