#include "../include/player.h"

#define log(x) std::cout << x << "\n";

Player::Player(Texture2D sprite) {
    this->spriteSheet = sprite;
    this->x = 325;
    this->y = 625;
    this->hitbox = {x, y, 25, 25};
    this->currentDirection = nodir;
    this->timer = 0.0f;
    this->frame = 0;
};

void Player::DrawPlayer() {
    Vector2 position = {x, y};
    const int scaleFactor = 25;
    static float rotation = 1.0f;

    const float frameWidth = static_cast<float>(spriteSheet.width / 4),
    frameHeight = static_cast<float>(spriteSheet.height / 4);

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
 
    hitbox = {x, y, 25, 25};
    DrawTextureRec(spriteSheet, pacFrame, position, RAYWHITE);
}

void Player::MovePlayer(bool collision) {
    static int moveX = 0, moveY = 0;
    float speed = 200.0f;

    //Start of Game Movement
    if (IsKeyPressed(KEY_D) && currentDirection == nodir) {
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    }
    if (IsKeyPressed(KEY_A) && currentDirection == nodir) {
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }

    //Store the next direction into the variable for later use
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) && currentDirection != nodir) {
        nextDirection = up;
    }
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) && currentDirection != nodir) {
        nextDirection = down;
    }
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        nextDirection = left;
    }
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        nextDirection = right;
    }

    //if the current direction is right, save the next direction, 
    //and wait until y is divisable by 25 to go up

    //Wait until divisbale or if opposite direction turn around
    if ((((int)this->y % 25 == 0) || (currentDirection == right)) && nextDirection == left) {
        RoundtoNearest25(this->y);
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }
    if ((((int)this->y % 25 == 0) || (currentDirection == left)) && nextDirection == right) {
        RoundtoNearest25(this->y);
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    }

    if ((((int)this->x % 25 == 0) || (currentDirection == down)) && nextDirection == up) {
        RoundtoNearest25(this->x);
        moveY = -1;
        moveX = 0;
        currentDirection = up;
    }
    if ((((int)this->x % 25 == 0) || (currentDirection == up)) && nextDirection == down) {
        RoundtoNearest25(this->x);
        moveY = 1;
        moveX = 0;
        currentDirection = down;
    }

    if (collision) {
        RoundtoNearest25(this->y);
        RoundtoNearest25(this->x);
        //this->x -= 25;
        moveX = 0;
        moveY = 0;
    }

    log(x);
    log(y);
    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime(); 
}

void Entity::RoundtoNearest25(float& num) {
    num = round(num);
    int lastTwoDigits = (int)num % 100;

    if ((lastTwoDigits > 0 && lastTwoDigits < 12.5) ||
    (lastTwoDigits > 25 && lastTwoDigits < 37.5) ||
    (lastTwoDigits > 50 && lastTwoDigits < 62.5) ||
    (lastTwoDigits > 75 && lastTwoDigits < 87.5)) {
        while ((int)num % 25 != 0) {
            num--;
        }
    }

    if ((lastTwoDigits > 12.5 && lastTwoDigits < 25) ||
    (lastTwoDigits > 37.5 && lastTwoDigits < 50) ||
    (lastTwoDigits > 62.5 && lastTwoDigits < 75) ||
    (lastTwoDigits > 87.5 && lastTwoDigits < 100)) {
        while ((int)num % 25 != 0) {
            num++;
        }
    }
}