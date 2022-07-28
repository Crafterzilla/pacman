#ifndef GAMECONDITIONS_H
#define GAMECONDITIONS_H

#include "raylib.h"
#include "player.h"
#include "ai.h"
#include "gameboard.h"
#include <string>


class GameConditions {
private:
    Ghosts& redGhost, blueGhost, pinkGhost, orangeGhost;
    Player& pacman;
    Balls& balls;
    Walls& walls;
    Texture2D* list;
    int score, lives, round;
    float timer;
    bool IsPlayerAlive, IsPlayerWinner, IsPaused;
    bool CheckMouseCollisionRec(const Rectangle&);
    void RestartMap();
public:
    GameConditions(Ghosts&, Ghosts&, Ghosts&,
    Ghosts&, Player&, Balls&, Walls&, Texture2D list[]);

    void PacmanAteBall(Rectangle);

    void CheckIfPacmanAteBigBall();
    bool PauseGame();
    void DrawPauseMenu();
    void CheckGameOverOrWon();
    void DrawGUI(Texture2D);

    void CheckAllConditions();
    void MoveAllGhosts();
    void DrawAllEntities();
};

#endif