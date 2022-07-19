#include "raylib.h"
#include "./include/player.h"
#include "./include/gameboard.h"

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

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(boardMaze, 0, 50, RAYWHITE);
            DrawGrid(widthRes, lengthRes, tileScaleFactor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

