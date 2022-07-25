#include "raylib.h"
#include "./include/player.h"
#include "./include/gameboard.h"
#include "./include/ai.h"


#define log(x) std::cout << x << std::endl;


int main(int argc, char ** argv)
{
    const int tileScaleFactor = 25;
    const int widthRes = 28 * tileScaleFactor, lengthRes = 36 * tileScaleFactor;
    const int mazeWidth = 28 * tileScaleFactor, mazelength = 31 * tileScaleFactor;

    InitWindow(widthRes, lengthRes, "Pac-Mans");

    //Set FPS
    const int screenRefreshRate = GetMonitorRefreshRate(0);
    SetTargetFPS(screenRefreshRate);

    Texture2D boardMaze = LoadTexture("./img/board.png");
    Texture2D pacmanSprite = LoadTexture("./img/pacmanSprites.png");

    //Ghosts textures
    Texture2D redGhostTex = LoadTexture("./img/redGhost.png");
    Texture2D pinkGhostTex = LoadTexture("./img/pinkGhost.png");
    Texture2D orangeGhostTex = LoadTexture("./img.orangeGhost.png");
    Texture2D blueGhostTex = LoadTexture("./img/blueGhost.png");

    Player pacman(pacmanSprite);
    Walls walls(boardMaze);
    GameCondtions game;
    Balls balls(walls);

    //Summon ghosts
    enum {red, blue, pink, orange};
    Ghosts redGhost(redGhostTex, red);
    Ghosts blueGhost(blueGhostTex, blue);
    Ghosts pinkGhost(pinkGhostTex, pink);
    Ghosts orangeGhost(orangeGhostTex, orange);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            //DisplayMouseCords();
            game.playerAndWallCollsion = walls.WallCollsion(pacman.hitbox);
            //log(game.playerAndWallCollsion);
            pacman.MovePlayer(game.playerAndWallCollsion);
            balls.BallCollision(pacman.hitbox);
            redGhost.MoveGhost(pacman.hitbox, walls);
            blueGhost.MoveGhost(pacman.hitbox, walls);

            pacman.DrawEntity();
            redGhost.DrawEntity();
            blueGhost.DrawEntity();
            DrawTexture(boardMaze, 0, 50, RAYWHITE);
            balls.DrawBalls();
            DrawGrid(widthRes, lengthRes, tileScaleFactor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

