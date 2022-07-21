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
    this->wall[0] = {0, 50, static_cast<float>(maze.width), 25}; //topwall
    this->wall[1] = {0, 800, static_cast<float>(maze.width), 25}; //bottomwall
    this->wall[2] = {0, 50, 25, static_cast<float>(maze.height)}; //leftwall
    this->wall[3] = {675, 50, 25, static_cast<float>(maze.height)}; //rightwall
    this->wall[4] = {0, 275, scaleFactor * 6, scaleFactor * 5}; //big left box top
    this->wall[5] = {0, 425, scaleFactor * 6, scaleFactor * 5}; //big left box bottom
    this->wall[6] = {550, 275, scaleFactor * 6, scaleFactor * 5}; // big right box top
    this->wall[7]  = {550, 425, scaleFactor * 6, scaleFactor * 5}; //big right box bottom
    this->wall[8] = {250, 350, scaleFactor * 8, scaleFactor * 5}; //middle box
    this->wall[9] = {0, 650, scaleFactor * 3, scaleFactor * 2}; //small left box
    this->wall[10] = {625, 650, scaleFactor * 3, scaleFactor * 2}; //small right box
    this->wall[11] = {50, 100, scaleFactor * 4, scaleFactor * 3}; //left top rectangle
    this->wall[12] = {175, 100, scaleFactor * 5, scaleFactor * 3}; //left top rectangle
    this->wall[13] = {50, 200, scaleFactor * 4, scaleFactor * 2}; //left top rectangle
    this->wall[14] = {550, 100, scaleFactor  * 4, scaleFactor * 3}; //right top rectangle
    this->wall[15] = {400, 100, scaleFactor * 5, scaleFactor * 3}; //right top rectangle
    this->wall[16] = {550, 200, scaleFactor * 4, scaleFactor * 2}; //right top rectangle
    this->wall[17] = {175, 200, scaleFactor * 2, scaleFactor * 8}; //t shape top half
    this->wall[18] = {225, 275, scaleFactor * 3, scaleFactor * 2}; //t shape top half
    this->wall[19] = {250, 200, scaleFactor * 8, scaleFactor * 2}; //t shape top half
    this->wall[20] = {325, 250, scaleFactor * 2, scaleFactor * 3}; //t shape top half
    this->wall[21] = {475, 200, scaleFactor * 2, scaleFactor * 8}; //t shape top half
    this->wall[22] = {400, 275, scaleFactor * 3, scaleFactor * 2}; //t shape top half
    this->wall[23] = {175, 425, scaleFactor * 2, scaleFactor * 5}; //left rectangle bottom
    this->wall[24] = {175, 575, scaleFactor * 5, scaleFactor * 2}; //left rectangle bottom
    this->wall[25] = {475, 425, scaleFactor * 2, scaleFactor * 5}; //right rectangle bottom
    this->wall[26] = {400, 575, scaleFactor * 5, scaleFactor * 2}; //right rectangle bottom
    this->wall[27] = {50, 575, scaleFactor * 4, scaleFactor * 2}; //l shape bottom
    this->wall[28] = {100, 625, scaleFactor * 2, scaleFactor * 3}; //l shape bottom
    this->wall[29] = {550, 575, scaleFactor * 4, scaleFactor * 2}; //l shape bottom
    this->wall[30] = {550, 625, scaleFactor * 2, scaleFactor * 3}; //l shape bottom
    this->wall[31] = {250, 500, scaleFactor * 8, scaleFactor * 2}; //t shape bottom
    this->wall[32] = {325, 550, scaleFactor * 2, scaleFactor * 3}; //t shape bottom
    this->wall[33] = {250, 650, scaleFactor * 8, scaleFactor * 2}; //t shape bottom
    this->wall[34] = {325, 700, scaleFactor * 2, scaleFactor * 3}; //t shape bottom
    this->wall[35] = {50, 725, scaleFactor * 10, scaleFactor * 2}; //t shape bottom
    this->wall[36] = {175, 650, scaleFactor * 2, scaleFactor * 5}; //t shape bottom
    this->wall[37] = {400, 725, scaleFactor * 10, scaleFactor * 2}; //t shape bottom
    this->wall[38] = {475, 650, scaleFactor * 2, scaleFactor * 5}; //t shape bottom
    this->wall[39] = {325, 75, scaleFactor * 2, scaleFactor * 4}; //middle wall piece on the top
}

bool Walls::WallCollsion(Rectangle pacman) {

    for (unsigned int i = 0; i < numOfWAlls; i++) {
        if (CheckCollisionRecs(pacman, wall[i])) {
            return true;
        }
    }
        
    return false;
}