#include "../include/player.h"

Player::Player(Texture2D sprite) {
    this->pacmanSprites = sprite;
    this->x = 325;
    this->y = 625;
    this->pacman = {x, y, 25, 25};
    this->currentDirection = nodir;
};

void Player::DrawPlayer() {
    Vector2 position = {x, y};
    const int scaleFactor = 25;
    static float rotation = 1;
    static Rectangle pacFrame = {0, 25, static_cast<float>(pacmanSprites.width / 4), 
    static_cast<float>(pacmanSprites.height / 4)};

    if (currentDirection == up) {
        rotation = scaleFactor * up;
    }
    else if (currentDirection == down) {
        rotation = scaleFactor * down;
    } 
    else if (currentDirection == left) {
        rotation = scaleFactor * left;
    } 
    else if (currentDirection == right) {
        rotation = scaleFactor * right;
    }
    pacFrame = {0, rotation, static_cast<float>(pacmanSprites.width / 4), 
    static_cast<float>(pacmanSprites.height / 4)};

    pacman = {x, y, 25, 25};
    DrawTextureRec(pacmanSprites, pacFrame, position, RAYWHITE);
}

void Player::MovePlayer() {
    static int moveX = 0, moveY = 0;
    float speed = 200.0f;

    if (IsKeyPressed(KEY_W)) {
        moveY = -1;
        moveX = 0;
        currentDirection = up;
    }
    if (IsKeyPressed(KEY_S)) {
        moveY = 1;
        moveX = 0;
        currentDirection = down;
    }
    if (IsKeyPressed(KEY_D)) {
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    }
    if (IsKeyPressed(KEY_A)) {
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }

    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime(); 
}