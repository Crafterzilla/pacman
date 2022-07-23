#include "../include/ai.h"

#define logStuff(x) std::cout << x << "\n";

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
    currentDirection = right;
}

void Ghosts::MoveGhost(Rectangle& pacman) {
    if (whichGhost == red) {
       RedAI(pacman);
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
}

void Ghosts::RedAI(Rectangle& pacman) {
    //Distance Formula
    // float distance = sqrt((x2 - x1)^2 + (y2 - y1)^2)

    //curDir, nextDir, possibleDir
    //enum Direction {right, left, down, up, nodir};
    possibleDirections[right] = sqrt(pow((this->x - pacman.x + 5), 2) + 
    pow((this->y - pacman.y), 2));
    possibleDirections[left] = sqrt(pow((this->x - pacman.x - 5), 2) + 
    pow((this->y - pacman.y), 2));
    possibleDirections[up] = sqrt(pow((this->x - pacman.x), 2) + 
    pow((this->y - pacman.y - 5), 2));
    possibleDirections[down] = sqrt(pow((this->x - pacman.x), 2) + 
    pow((this->y - pacman.y + 5), 2));

    //find the shortest distance
    int bestDirection = 0, bestDistance = possibleDirections[right];
    for (int i = 0; i < 4; i++) {
        if (possibleDirections[i] < bestDistance) {
            bestDistance = possibleDirections[i];
            bestDirection = i;
        }
    }
    
    nextDirection = bestDirection;

    static int moveX = 0, moveY = 0;
    float speed = 150.0f;

    //make the ghost move the best direction
    if (nextDirection == left) {
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }
    else if (nextDirection == right) {
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    } else if (nextDirection == up) {
        moveY = -1;
        moveX = 0;
        currentDirection = up;
    } else if (nextDirection == down) {
        moveY = 1;
        moveX = 0;
        currentDirection = down;
    }

    // if ((((int)this->y % 25 == 0) || (currentDirection == right)) && nextDirection == left) {
    //     RoundtoNearest25(this->y);
    //     moveX = -1;
    //     moveY = 0;
    //     currentDirection = left;
    // }
    // if ((((int)this->y % 25 == 0) || (currentDirection == left)) && nextDirection == right) {
    //     RoundtoNearest25(this->y);
    //     moveX = 1;
    //     moveY = 0;
    //     currentDirection = right;
    // }
    // if ((((int)this->x % 25 == 0) || (currentDirection == down)) && nextDirection == up) {
    //     RoundtoNearest25(this->x);
    //     moveY = -1;
    //     moveX = 0;
    //     currentDirection = up;
    // }
    // if ((((int)this->x % 25 == 0) || (currentDirection == up)) && nextDirection == down) {
    //     RoundtoNearest25(this->x);
    //     moveY = 1;
    //     moveX = 0;
    //     currentDirection = down;
    // }

    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime(); 

    logStuff(bestDirection);
    //logStuff(y);
}