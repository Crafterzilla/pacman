#include "../include/player.h"

Player::Player(Texture2D sprite) {
    this->pacmanSprites = sprite;
    this->x = 325;
    this->y = 625;
    this->pacman = {x, y, 25, 25};
    this->currentDirection = nodir;
    this->timer = 0.0f;
    this->frame = 0;
};

void Player::DrawPlayer() {
    Vector2 position = {x, y};
    const int scaleFactor = 25;
    static float rotation = 1.0f;

    const float frameWidth = static_cast<float>(pacmanSprites.width / 4),
    frameHeight = static_cast<float>(pacmanSprites.height / 4);

    static Rectangle pacFrame = {static_cast<float>(frame), 25, frameWidth, frameHeight};

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

    timer += GetFrameTime();
    if (timer >= 0.05) {
        timer = 0.0f;
        frame += 1;
    }

    frame %= 4;

    pacFrame = {static_cast<float>(frame) * scaleFactor, rotation, frameWidth, 
    frameHeight};

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