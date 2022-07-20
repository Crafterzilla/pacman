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
    const int scaleFactor = 25;
    this->topWall = {0, 50, static_cast<float>(maze.width), 25};
    this->bottomWall = {0, 800, static_cast<float>(maze.width), 25};
    this->leftWall = {0, 50, 25, static_cast<float>(maze.height)};
    this->rightWall = {675, 50, 25, static_cast<float>(maze.height)};
    this->bigLeftBoxTop = {0, 275, scaleFactor * 6, scaleFactor * 5};
    this->bigLeftBoxBottom = {0, 425, scaleFactor * 6, scaleFactor * 5};
    this->bigRightBoxTop = {550, 275, scaleFactor * 6, scaleFactor * 5};
    this->bigRightBoxBottom  = {550, 425, scaleFactor * 6, scaleFactor * 5};
    this->middleBox = {250, 350, scaleFactor * 8, scaleFactor * 5};
    this->smallLeftBox = {0, 650, scaleFactor * 3, scaleFactor * 2};
    this->smallRightBox = {625, 650, scaleFactor * 3, scaleFactor * 2};
    this->left1 = {50, 100, scaleFactor * 4, scaleFactor * 3};
    this->left2 = {175, 100, scaleFactor * 5, scaleFactor * 3};
    this->left3 = {50, 200, scaleFactor * 4, scaleFactor * 2};
    this->right1 = {550, 100, scaleFactor  * 4, scaleFactor * 3};
    this->right2 = {400, 100, scaleFactor * 5, scaleFactor * 3};
    this->right3 = {550, 200, scaleFactor * 4, scaleFactor * 2};
    this->t1top = {175, 200, scaleFactor * 2, scaleFactor * 8};
    this->t1bottom = {225, 275, scaleFactor * 3, scaleFactor * 2};
    this->t2top = {250, 200, scaleFactor * 8, scaleFactor * 2};
    this->t2bottom = {325, 250, scaleFactor * 2, scaleFactor * 3};
    this->t3top = {475, 200, scaleFactor * 2, scaleFactor * 8};
    this->t3bottom = {400, 275, scaleFactor * 3, scaleFactor * 2};
    this->left4 = {175, 425, scaleFactor * 2, scaleFactor * 5};
    this->left5 = {175, 575, scaleFactor * 5, scaleFactor * 2};
    this->right4 = {475, 425, scaleFactor * 2, scaleFactor * 5};
    this->right5 = {400, 575, scaleFactor * 5, scaleFactor * 2};
    this->l1top = {50, 575, scaleFactor * 4, scaleFactor * 2};
    this->l1bottom = {100, 625, scaleFactor * 2, scaleFactor * 3};
    this->l2top = {550, 575, scaleFactor * 4, scaleFactor * 2};
    this->l2bottom = {550, 625, scaleFactor * 2, scaleFactor * 3};
    this->t4top = {250, 500, scaleFactor * 8, scaleFactor * 2};
    this->t4bottom = {325, 550, scaleFactor * 2, scaleFactor * 3};
    this->t5top = {250, 650, scaleFactor * 8, scaleFactor * 2};
    this->t5bottom = {325, 700, scaleFactor * 2, scaleFactor * 3};
    this->t6top = {50, 725, scaleFactor * 10, scaleFactor * 2};
    this->t6bottom = {175, 650, scaleFactor * 2, scaleFactor * 5};
    this->t7top = {400, 725, scaleFactor * 10, scaleFactor * 2};
    this->t7bottom = {475, 650, scaleFactor * 2, scaleFactor * 5};
}

bool Walls::WallCollsion(Rectangle pacman) {
    if (CheckCollisionRecs(pacman, topWall)
    || CheckCollisionRecs(pacman, bottomWall) ||
    CheckCollisionRecs(pacman, leftWall) ||
    CheckCollisionRecs(pacman, rightWall) ||
    CheckCollisionRecs(pacman, bigLeftBoxTop) ||
    CheckCollisionRecs(pacman, bigLeftBoxBottom) ||
    CheckCollisionRecs(pacman, bigRightBoxTop) ||
    CheckCollisionRecs(pacman, bigRightBoxBottom) ||
    CheckCollisionRecs(pacman, smallLeftBox) ||
    CheckCollisionRecs(pacman, smallRightBox) ||
    CheckCollisionRecs(pacman, middleBox) ||
    CheckCollisionRecs(pacman, left1) ||
    CheckCollisionRecs(pacman, left2) ||
    CheckCollisionRecs(pacman, left3) ||
    CheckCollisionRecs(pacman, right1) ||
    CheckCollisionRecs(pacman, right2) ||
    CheckCollisionRecs(pacman, right3) ||
    CheckCollisionRecs(pacman, t1top) ||
    CheckCollisionRecs(pacman, t2top) ||
    CheckCollisionRecs(pacman, t3top) ||
    CheckCollisionRecs(pacman, t1bottom) ||
    CheckCollisionRecs(pacman, t2bottom) ||
    CheckCollisionRecs(pacman, t3bottom) ||
    CheckCollisionRecs(pacman, left4) ||
    CheckCollisionRecs(pacman, left5) ||
    CheckCollisionRecs(pacman, right4) ||
    CheckCollisionRecs(pacman, right5) ||
    CheckCollisionRecs(pacman, l1top) ||
    CheckCollisionRecs(pacman, l1bottom) ||
    CheckCollisionRecs(pacman, l2top) ||
    CheckCollisionRecs(pacman, l2bottom) ||
    CheckCollisionRecs(pacman, t4top) ||
    CheckCollisionRecs(pacman, t4bottom) ||
    CheckCollisionRecs(pacman, t5top) ||
    CheckCollisionRecs(pacman, t5bottom) ||
    CheckCollisionRecs(pacman, t6top) ||
    CheckCollisionRecs(pacman, t6bottom) ||
    CheckCollisionRecs(pacman, t7top) ||
    CheckCollisionRecs(pacman, t7bottom)
    )
        return true;
        
    return false;
}