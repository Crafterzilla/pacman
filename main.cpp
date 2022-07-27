#include "raylib.h"
#include "./include/player.h"
#include "./include/gameboard.h"
#include "./include/ai.h"
#include "./include/gameConditions.h"

#define log(x) std::cout << x << std::endl;


int main(int argc, char ** argv)
{
    const int tileScaleFactor = 25;
    const int widthRes = 28 * tileScaleFactor, lengthRes = 36 * tileScaleFactor;

    InitWindow(widthRes, lengthRes, "Pac-Mans");

    //Set FPS
    const int screenRefreshRate = GetMonitorRefreshRate(0);
    SetTargetFPS(200);

    Texture2D boardMaze = LoadTexture("./img/board.png");
    Texture2D pacmanSprite = LoadTexture("./img/pacmanSprites.png");

    SetRandomSeed(time(0));

    //Ghosts textures
    Texture2D redGhostTex = LoadTexture("./img/redGhost.png");
    Texture2D pinkGhostTex = LoadTexture("./img/pinkGhost.png");
    Texture2D orangeGhostTex = LoadTexture("./img/orangeGhost.png");
    Texture2D blueGhostTex = LoadTexture("./img/blueGhost.png");

    Texture2D floatingEyes = LoadTexture("./img/floatingGhost.png");
    Texture2D scaredGhost = LoadTexture("./img/scareGhost.png");

    Player pacman(pacmanSprite);
    Walls walls(boardMaze);
    Balls balls(walls);

    //Summon ghosts
    enum {red, blue, pink, orange};
    Ghosts redGhost(redGhostTex, floatingEyes, scaredGhost, red);
    Ghosts blueGhost(blueGhostTex, floatingEyes, scaredGhost,blue);
    Ghosts pinkGhost(pinkGhostTex, floatingEyes, scaredGhost, pink);
    Ghosts orangeGhost(orangeGhostTex, floatingEyes, scaredGhost, orange);

    GameConditions game(redGhost, blueGhost, pinkGhost, orangeGhost, pacman, 
    balls, walls);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DisplayMouseCords();

            pacman.MovePlayer(walls.WallCollsion(pacman.hitbox), 
            walls.DoorCollision(pacman.hitbox));

            game.CheckIfPacmanAteBigBall();

            balls.BallCollision(pacman.hitbox);
            balls.RemoveBigBall(pacman.hitbox);

            game.MoveAllGhosts();
            
            game.DrawAllGhost();
            balls.DrawBalls();

            DrawTexture(boardMaze, 0, 50, RAYWHITE);

            DrawGrid(widthRes, lengthRes, tileScaleFactor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

