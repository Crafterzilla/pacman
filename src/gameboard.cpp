#include "../include/gameboard.h"

#define logStuff(x) std::cout << x << "\n";

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
    Rectangle tmp = {0, 50, 25, 25};

    
    int doorCounter = 0;
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0 ; j < mazeWidth; j++) {
            if (mazeSketch[i][j] == '#') {
                walls.push_back(tmp);
            } else if (mazeSketch[i][j] == '-') {
                doors[doorCounter] = tmp;
                doorCounter++;
            }
            tmp.x += 25;
        }
        tmp.x = 0;
        tmp.y += 25;
    }
}

bool Walls::WallCollsion(Rectangle pacman) const{
    for (std::list<Rectangle>::const_iterator it = walls.begin();
    it != walls.end(); ++it) {
        if (CheckCollisionRecs(pacman, *it)) {
            return true;
        }
    }
    return false;
}

bool Walls::DoorCollision(Rectangle rec) const{
    for (int i = 0; i < doors.size(); i++) {
        if (CheckCollisionRecs(rec, doors[i]))
            return true;
    }
    return false;
}

Balls::Balls(Walls& walls) {
    //find big balls and make big balls
    Rectangle tmp = {0, 50, 12.5f, 12.5f};
    float x = 0, y = 50;

    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0 ; j < mazeWidth; j++) {
            if (mazeSketch[i][j] == 'o') {
                tmp = {x + 9.0f, y + 9.0f, 10, 10};
                bigBalls.push_back(tmp);
            }
            x += 25;
        }
        x = 0;
        y += 25;
    }

    //make smalls anywhere else 
    ball.reserve(31 * 28);
    Rectangle middleBox = {250, 350, 25 * 8, 25 * 5};
    x = 0, y = 50;

    for (unsigned int i = 0; i < 31 * 28; i++) {
        Rectangle tmp = {x, y, 5, 5};
        if (!walls.WallCollsion(tmp) && !CheckCollisionRecs(tmp, middleBox) &&
        !BigBallCollision(tmp)) {
            tmp = {x + 12.5f, y + 12.5f, 5, 5};
            ball.push_back(tmp);
        }
        if (x > 675) {
            y += 25;
            x = 0;
        } else {
            x += 25;
        }
    }
    ball.shrink_to_fit();
}

void Balls::DrawBalls() {
    for (unsigned int i = 0; i < ball.size(); i++) {
        DrawRectangleRec(ball[i], YELLOW);
    }
    for (unsigned int i = 0; i < bigBalls.size(); i++) {
        DrawRectangleRec(bigBalls[i], YELLOW);
    }
}

void Balls::BallCollision(Rectangle pacman) {
    for (unsigned int i = 0; i < ball.size(); i++) {
        if (CheckCollisionRecs(pacman, ball[i])) {
            ball.erase(ball.begin() + i);
        }
    }
}

bool Balls::BigBallCollision(const Rectangle& rec) const{
    for (unsigned int i = 0; i < bigBalls.size(); i++) {
        if (CheckCollisionRecs(bigBalls[i], rec)) {
            return true;
        }
    }
    return false;
}

void Balls::RemoveBigBall(Rectangle rec) {
    for (unsigned int i = 0; i < bigBalls.size(); i++) {
        if (CheckCollisionRecs(bigBalls[i], rec)) {
            bigBalls.erase(bigBalls.begin() + i);
        }
    }
}