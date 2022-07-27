#include "../include/gameConditions.h"

GameConditions::GameConditions(Ghosts& redGhost, Ghosts& blueGhost,
Ghosts& pinkGhost, Ghosts& orangeGhost, 
Player& pacman, Balls& balls, Walls& walls) :
    redGhost(redGhost), 
    blueGhost(blueGhost), 
    pinkGhost(pinkGhost),
    orangeGhost(orangeGhost), 
    pacman(pacman), 
    balls(balls), 
    walls(walls) {}

void GameConditions::CheckIfPacmanAteBigBall() {
    redGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    pinkGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    orangeGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    blueGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
}

void GameConditions::MoveAllGhosts() {
    redGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    pinkGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    orangeGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    blueGhost.MoveGhost(pacman, redGhost.hitbox, walls);
}

void GameConditions::DrawAllGhost() {
    pacman.DrawEntity();
    redGhost.DrawEntity();
    pinkGhost.DrawEntity();
    orangeGhost.DrawEntity();
    blueGhost.DrawEntity();
}