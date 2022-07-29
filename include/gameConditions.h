#ifndef GAMECONDITIONS_H
#define GAMECONDITIONS_H

#include "raylib.h"
#include "player.h"
#include "ai.h"
#include "gameboard.h"
#include <string>


class GameConditions {
private:
    Ghosts& redGhost, &blueGhost, &pinkGhost, &orangeGhost;

    Player& pacman;
    Balls& balls;
    Walls& walls;
    Texture2D* list;


    Music pacRemix;
    Sound chompSound, sirenB, sirenC, deathSound, ghostEaten; 


    int score, lives, round;
    float timer, deathTimer;
    bool gameStart;
    bool IsPlayerWinner, IsPaused, fullRestart;

    bool CheckMouseCollisionRec(const Rectangle&);
    void CheckIfPacmanAteBigBall();
    void CheckGameOverOrWon();
public:
    GameConditions(Ghosts&, Ghosts&, Ghosts&,
    Ghosts&, Player&, Balls&, Walls&, Texture2D list[]);
    ~GameConditions();
    void RestartMap();
    void PacmanAteBall(Rectangle);
    bool IsPlayerAlive, exit;
    bool PauseGame();
    void DrawPauseMenu();
    void DrawGUI(Texture2D);
    void DeathMenu();

    void CheckAllConditions();
    void MoveAllGhosts();
    void DrawAllEntities();

    void StartGame();

    void PlayAllSound();
};

#endif