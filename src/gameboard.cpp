#include "../include/gameboard.h"

void DrawGrid(int widthRes, int lengthRes, int scaleFactor) {
    for (int i = 0; i < widthRes; i += scaleFactor) {
        DrawRectangle(i, 0, 1, lengthRes, RAYWHITE);
    }
    for (int i = 0; i < lengthRes; i += scaleFactor) {
        DrawRectangle(0, i, widthRes, 1, RAYWHITE);
    }
}

void DisplayMouseCords() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    std::cout << "MouseX: " << mouseX << "\n"
    << "MouseY: " << mouseY << "\n";
}
GameCondtions::GameCondtions() {
    this->IsPlayerAlive = false;
    this->playerAndWallCollsion = false;
}

Walls::Walls(Texture2D maze) {
    this->topWall = {0, 50, static_cast<float>(maze.width), 50};
    this->bottomWall = {0, 800, static_cast<float>(maze.width), 50};
    this->leftWall = {0, 50, 50, static_cast<float>(maze.height)};
    this->rightWall = {675, 50, 50, static_cast<float>(maze.height)};
}

bool Walls::WallCollsion(Rectangle pacman) {
    if (CheckCollisionRecs(pacman, topWall)
    || CheckCollisionRecs(pacman, bottomWall) ||
    CheckCollisionRecs(pacman, leftWall) ||
    CheckCollisionRecs(pacman, rightWall)
    )
        return true;
        
    return false;
}