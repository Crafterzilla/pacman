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
    Ghosts ghosts[4] = {redGhost, blueGhost, 
    pinkGhost, orangeGhost};

    Player& pacman;
    Balls& balls;
    Walls& walls;
    Texture2D* list;


    Music pacRemix;
    Sound chompSound, sirenB, sirenC, deathSound, ghostEaten; 


    int score, lives, round;
    float timer;
    bool gameStart;
    bool IsPlayerAlive, IsPlayerWinner, IsPaused;
    bool CheckMouseCollisionRec(const Rectangle&);
    void CheckIfPacmanAteBigBall();
    void CheckGameOverOrWon();
    void RestartMap(bool);
public:
    GameConditions(Ghosts&, Ghosts&, Ghosts&,
    Ghosts&, Player&, Balls&, Walls&, Texture2D list[]);
    ~GameConditions();

    void PacmanAteBall(Rectangle);

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