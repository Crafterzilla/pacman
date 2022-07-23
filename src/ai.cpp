#include "../include/ai.h"

Ghosts::Ghosts(Texture2D ghostSkin, int whichGhost) {
    this->spriteSheet = ghostSkin;
    this->whichGhost = whichGhost;

    if (whichGhost == red) {
        this->x = 325;
        this->y = 325;
    }
    else if (whichGhost == blue) {
        /* code */
    }
    else if (whichGhost == pink) {
        /* code */
    }
    else if (whichGhost == orange) {
        /* code */
    }

    hitbox = {x, y, 25, 25};
    currentDirection = nodir;
}

void Ghosts::DrawGhost() {
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