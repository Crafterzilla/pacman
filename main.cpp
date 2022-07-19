#include "raylib.h"
#include "./include/test.h"
#include "./include/gameboard.h"

int main(int argc, char ** argv)
{
    const int tileScaleFactor = 25;
    const int widthRes = 28 * tileScaleFactor, lengthRes = 36 * tileScaleFactor;
    const int mazeWidth = 28 * tileScaleFactor, mazelength = 31 * tileScaleFactor;

    InitWindow(widthRes, lengthRes, "Pac-Mans");

    Texture2D boardMaze = LoadTexture("./img/board.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawText("Sample text", 190, 200, 20, RAYWHITE);
            DrawTexture(boardMaze, 0, 50, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


