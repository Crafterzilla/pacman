#include "../include/player.h"

#define logStuff(x) std::cout << x << "\n";

Player::Player(Texture2D sprite) {
    this->spriteSheet = sprite;
    this->x = 325;
    this->y = 625;
    this->hitbox = {x, y, 25, 25};
    this->currentDirection = nodir;
    this->timer = 0.0f;
    this->frame = 0;
};

void Entity::DrawEntity() {
    Vector2 position = {x, y};
    const int scaleFactor = 25;
    static float rotation = 0.0f;

    const float frameWidth = static_cast<float>(spriteSheet.width / 4),
    frameHeight = static_cast<float>(spriteSheet.height / 4);

    static Rectangle pacFrame = {static_cast<float>(frame), 25, frameWidth, frameHeight};

    switch (currentDirection) {
    case up:
        rotation = scaleFactor * up;
        break;
    case down:
        rotation = scaleFactor * down;
        break;
    case left:
        rotation = scaleFactor * left;
        break;
    case right:
    case nodir:
        rotation = scaleFactor * right;
        break;
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
    // logStuff(currentDirection);
}

void Player::MovePlayer(bool collision, bool doorCollision) {
    // static int moveX = 0, moveY = 0;
    float speed = 225.0f;

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
    if (IsKeyPressed(KEY_W) || (IsKeyPressed(KEY_UP) && currentDirection != nodir)) {
        nextDirection = up;
    }
    if (IsKeyPressed(KEY_S) || (IsKeyPressed(KEY_DOWN) && currentDirection != nodir)) {
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
    if ((((int)this->y % 25 == 0) || (currentDirection == right)) && nextDirection == left && currentDirection
    != nodir) {
        RoundtoNearest25(this->y);
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }
    if ((((int)this->y % 25 == 0) || (currentDirection == left)) && nextDirection == right && currentDirection
    != nodir) {
        RoundtoNearest25(this->y);
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    }

    if ((((int)this->x % 25 == 0) || (currentDirection == down)) && nextDirection == up && currentDirection
    != nodir) {
        RoundtoNearest25(this->x);
        moveY = -1;
        moveX = 0;
        currentDirection = up;
    }
    if ((((int)this->x % 25 == 0) || (currentDirection == up)) && nextDirection == down && currentDirection
    != nodir) {
        RoundtoNearest25(this->x);
        moveY = 1;
        moveX = 0;
        currentDirection = down;
    }

    if (collision || doorCollision) {
        RoundtoNearest25(this->y);
        RoundtoNearest25(this->x);
        //this->x -= 25;
        moveX = 0;
        moveY = 0;
    }

    if (this->y == 400 && this->x < 0)
        this->x = 700;
    else if (this->y == 400 && this-> x > 700)
        this->x = 0;

    // logStuff(x);
    // logStuff(y);
    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime(); 
}

void Entity::RoundtoNearest25(float& num) {
    num = round(num);
    int lastTwoDigits = (int)num % 100;

    float lowestNum = 0, highestNum = 12.5f;
    bool roundUp = false;
    for (int i = 0; i < 8; i++) {
        if (lastTwoDigits > lowestNum && lastTwoDigits < highestNum) {
            if (!roundUp) {
                while ((int)num % 25 != 0) {
                    num--;
                }
            }
            else {
                while ((int)num % 25 != 0) {
                    num++;
                }   
            }
            break;
        }
        lowestNum += 12.5f;
        highestNum += 12.5f;
        if (i % 2 == 0) {
            roundUp = true;
        } else {
            roundUp = false;
        }
    }
}

Vector2 Entity::Rotate180DegreesFromOrigin(Vector2 cord, Vector2 originPoint)  {
    float x = 2 * originPoint.x - cord.x;
    float y = 2 * originPoint.y - cord.y;
    return {x, y};
}