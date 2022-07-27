#include "../include/ai.h"

#define logStuff(x) std::cout << x << "\n";

Ghosts::Ghosts(Texture2D ghostSkin, Texture2D floatEyes, Texture2D scaredGhost, int whichGhost) {
    this->spriteSheet = ghostSkin;
    this->regGhost = ghostSkin;

    this->scaredGhost = scaredGhost;
    this->floatEyes = floatEyes;
    this->whichGhost = whichGhost;

    switch (whichGhost) {
    case red:
        this->x = 325;
        this->y = 400;
        break;
    case blue:
        this->x = 350;
        this->y = 325;
        break;
    case pink:
        this->x = 300;
        this->y = 400;
        break;
    case orange:
        this->x = 275;
        this->y = 400;
        break;
    }

    this->hitbox = {x, y, 25, 25};
    this->currentDirection = nodir;
    this->nextDirection = nodir;
    this->mode = gameStart;
    this->canGoThroughDoor = true;
    this->timer = 0.0f;
    //this->scaredTimer = 0.0f;
    this->modeTimer = 0.0f;
    this->speed = 200.0f;
}

void Ghosts::CheckConditions(bool hasPacmanEatenABigBall) {
    if (hasPacmanEatenABigBall)
        mode = scared;
}

void Ghosts::MoveGhost(const Player& pacman, const Rectangle& redGhost, const Walls& walls) {
    ModeChanger();

    //Choose right aiType for ghost
    switch (whichGhost) {
    case red:
        RedAI(pacman, walls);
        break;
    case blue:
        BlueAI(pacman, redGhost, walls);
        break;
    case pink:
        PinkAI(pacman, walls);
        break;
    case orange:
        OrangeAI(pacman, walls);
        break;
    }

    // make the ghost move the best direction
    switch (nextDirection) {
        case left:
            moveX = -1;
            moveY = 0;
            currentDirection = left;
            break;
        case right:
            moveX = 1;
            moveY = 0;
            currentDirection = right;
            break;
        case up:
            moveY = -1;
            moveX = 0;
            currentDirection = up;           
            break;
        case down:
            moveY = 1;
            moveX = 0;
            currentDirection = down;
            break;
    }

    Rectangle pipe1 = {0, 400, 25, 25}, pipe2 = {700, 400, 25, 25};

    if (walls.WallCollsion(hitbox) || 
    (!canGoThroughDoor && walls.DoorCollision(hitbox)) ||
    (CheckCollisionRecs(pipe1, hitbox) || CheckCollisionRecs(pipe2, hitbox))
    ) {
        RoundtoNearest25(this->y);
        RoundtoNearest25(this->x);
        //this->x -= 25;
        moveX = 0;
        moveY = 0;
    }

    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime();
}

void Ghosts::ModeChanger() {
    modeTimer += GetFrameTime();
    if (mode == chase || mode == scatter) {
        if (modeTimer > 6.5f)
            mode = scatter;
        else
            mode = chase;

        scaredTimer = 0.0f;
    }
    else if (mode == scared) {
        scaredTimer += GetFrameTime();
        if (scaredTimer > 7.0f) {
            scaredTimer = 0;
            mode = chase;
        }
    }
    if (modeTimer > 10.0f)
        modeTimer = 0.0f;
}

void Ghosts::RetreatMode(const Walls& walls) {
        canGoThroughDoor = true;
        Rectangle retreatRec = {275, 375, 25 * 3, 25 * 6};

        PathFind(retreatRec, walls);
        if (CheckCollisionRecs(retreatRec, hitbox)) {
            mode = gameStart;
        }
        spriteSheet = floatEyes;
        scaredTimer = 0.0f;
}

void Ghosts::ScaredMode(const Player& pacman, const Walls& walls) {
    int randX = 0, randY = 0;
    randX = GetRandomValue(0, 700);
    randY = GetRandomValue(50, 800);
    Rectangle random = {randX, randY, 25, 25};
    PathFind(random, walls);
    spriteSheet = scaredGhost;

    if (CheckCollisionRecs(pacman.hitbox, hitbox)) {
        mode = retreat;
    }
}

void Ghosts::GameStartMode(const Walls& walls) {
    Rectangle startRec = {225, 325, 250, 5};
    PathFind(startRec, walls);
    if (CheckCollisionRecs(startRec, hitbox)) {
        mode = chase;
        canGoThroughDoor = false;
    }
    spriteSheet = regGhost;
    scaredTimer = 0.0f;
}

void Ghosts::RedAI(const Player& pacman, const Walls& walls) {
    switch (mode) {
        case chase: 
            PathFind(pacman.hitbox, walls);
            spriteSheet = regGhost;
            break;
        case scatter: {
            Rectangle scatterCorner = {31 * 25, 2 * 25, 25, 25};
            PathFind(scatterCorner, walls);
            spriteSheet = regGhost;
        }
            break;
        case scared:
            ScaredMode(pacman, walls);
            break;
        case retreat:
            RetreatMode(walls);
            break;
        case gameStart:
            GameStartMode(walls);
            break;
    }
}

void Ghosts::PinkAI(const Player& pacman, const Walls& walls) {
    switch (mode) {
        case chase: {
            Rectangle fourAwayPacmanHitbox = {0, 0, 25, 25};
            switch(pacman.currentDirection) {
                case right:
                case nodir:
                    fourAwayPacmanHitbox = {pacman.hitbox.x + 100, pacman.hitbox.y, 25, 25};
                    break;
                case left:
                    fourAwayPacmanHitbox = {pacman.hitbox.x - 100, pacman.hitbox.y, 25, 25};
                    break;
                case up:
                    fourAwayPacmanHitbox = {pacman.hitbox.x, pacman.hitbox.y - 100, 25, 25};
                    break;
                case down:
                    fourAwayPacmanHitbox = {pacman.hitbox.x, pacman.hitbox.y + 100, 25, 25};
                    break;
            }
            PathFind(fourAwayPacmanHitbox, walls);
        }
        spriteSheet = regGhost;
            break;
        case scatter: {
            Rectangle scatterCorner = {50, 50, 25, 25};
            PathFind(scatterCorner, walls);
        }
            break;
        spriteSheet = regGhost;
            break;
        case scared:
            ScaredMode(pacman, walls);
            break;
        case retreat:
            RetreatMode(walls);
            break;
        case gameStart:
            GameStartMode(walls);
            break;
    }
}

void Ghosts::OrangeAI(const Player& pacman, const Walls& walls) {
    float distance = sqrt(pow((pacman.hitbox.x - hitbox.x), 2) + 
    pow((pacman.hitbox.y - hitbox.y), 2));

    if (distance > 250 && (mode == chase || mode == scatter))
        mode = chase;
    else if (distance < 250 && (mode == chase || mode == scatter))
        mode = scatter;

    switch (mode) {
        case chase:
            PathFind(pacman.hitbox, walls); 
            spriteSheet = regGhost;
            break;
        case scatter: {
            Rectangle scatterCorner = {25, 775, 25, 25};
            PathFind(scatterCorner, walls);
        }
        spriteSheet = regGhost;
            break;
        case scared:
            ScaredMode(pacman, walls);
            break;
        case retreat:
            RetreatMode(walls);
            break;
        case gameStart:
            GameStartMode(walls);
            break;
    }
}

void Ghosts::BlueAI(const Player& pacman, const Rectangle& redGhost, const Walls& walls) {
    switch (mode) {
        case chase: {
            Rectangle twoAwayPacmanHitbox = {0, 0, 25, 25};
            switch(pacman.currentDirection) {
                case right:
                case nodir:
                    twoAwayPacmanHitbox = {pacman.hitbox.x + 50, pacman.hitbox.y, 25, 25};
                    break;
                case left:
                    twoAwayPacmanHitbox = {pacman.hitbox.x - 50, pacman.hitbox.y, 25, 25};
                    break;
                case up:
                    twoAwayPacmanHitbox = {pacman.hitbox.x, pacman.hitbox.y - 50, 25, 25};
                    break;
                case down:
                    twoAwayPacmanHitbox = {pacman.hitbox.x, pacman.hitbox.y + 50, 25, 25};
                    break;
            }

            Vector2 originBox = {twoAwayPacmanHitbox.x, twoAwayPacmanHitbox.y},
            redGhostPos = {redGhost.x, redGhost.y};

            Vector2 rotatedTarget = Rotate180DegreesFromOrigin(redGhostPos, originBox);
            Rectangle rotatedTargetRec = {rotatedTarget.x, rotatedTarget.y, 25, 25};

            PathFind(rotatedTargetRec, walls);
            spriteSheet = regGhost;
        }
            break;
        case scatter: {
            Rectangle scatterCorner = {700, 775, 25, 25};
            PathFind(scatterCorner, walls);
            spriteSheet = regGhost;
        }
            break;
        case scared:
            ScaredMode(pacman, walls);
            break;
        case retreat:
            RetreatMode(walls);
            break;
        case gameStart:
            GameStartMode(walls);
            break;
    }
}

void Ghosts::PathFind(const Rectangle& rec, const Walls& walls) {
    //Project Bertha

    //ex: a rectangle will be created in the left. that rectangle will create four tmp
    //rectangeles up, down, left, and right. If there is collision, those rectangles will be given
    //null values. Then, with the remaining rectangles, the distance formula will be used to determine the
    //fastest rectangle to find pacman. Once found, the rectangle will be placed into the list and this process
    //will be repeated until the path rectagnlees are in contact with pacman.
    //then this process will be done again with another path and that path will be added to a vector of lists


    //potential solution could also be to store 25, and whatever direction
    std::list<Rectangle> path;
    std::list<int> pathDirections;
    enum shouldIresetDirections {veryFarAwayMode = 10, farMode = 4, mediumMode = 5, closeMode = 3};

    path.push_back(hitbox);

    float roundedX = this->x;
    RoundtoNearest25(roundedX);
    float roundedY = this->y;
    RoundtoNearest25(roundedY);

    Rectangle tmpRec[4];
    Rectangle previousRec = {roundedX, roundedY, 25, 25};
    float offset = 25.0f;

    tmpRec[right] = {roundedX + offset, roundedY, 25, 25};
    tmpRec[left] = {roundedX - offset, roundedY, 25, 25};
    tmpRec[up] = {roundedX, roundedY - offset, 25, 25};
    tmpRec[down] = {roundedX, roundedY + offset, 25, 25};

    if ((int)this->x % 25 == 0 && (int)this->y % 25 == 0) {
        if (goToNextDir == sizeNextDir) {
            float possibleDistacnes[4];

            while(CheckCollisionRecs(rec, path.back()) == false) {
                float bestDistance = 1000.0f;

                //Cehck the four tmp rectangles and see if it was an already moved to position or
                //if that rec is in contact with a wall. If so, give them huge numbers so 
                //that they are too big to pass the distance test
                for (int i = 0; i < 4; i++) {
                    if (walls.WallCollsion(tmpRec[i]) || CheckCollisionRecs(previousRec, tmpRec[i])) {
                        tmpRec[i] = {10000.0f, 10000.0f, 0, 0};
                    }
                }
                
                //Find the distance of all four directions. The direction ruled out 
                //will have larger than usual values
                possibleDistacnes[right] = sqrt(pow((tmpRec[right].x - rec.x), 2) + 
                pow((tmpRec[right].y - rec.y), 2));

                possibleDistacnes[left] = sqrt(pow((tmpRec[left].x - rec.x), 2) + 
                pow((tmpRec[left].y - rec.y), 2));

                possibleDistacnes[up] = sqrt(pow((tmpRec[up].x - rec.x), 2) + 
                pow((tmpRec[up].y - rec.y), 2));

                possibleDistacnes[down] = sqrt(pow((tmpRec[down].x - rec.x), 2) + 
                pow((tmpRec[down].y - rec.y), 2));

                //Compare all the distances and find the smallest one
                //once found, next direction will be the direction found
                for (int dir = 0; dir < 4; dir++) {
                    if (possibleDistacnes[dir] < bestDistance) {
                        bestDistance = possibleDistacnes[dir];
                        nextDirection = dir;
                    }
                }

                //Store that direction into a list of directions
                pathDirections.push_back(nextDirection);
                
                //make the second to last rectnagle the previous rectangle
                std::list<Rectangle>::iterator it = --path.end();
                previousRec = *it;

                //In case of some errors which may happen, break of the function
                //if size is greater than 50. This will save the game from
                //crashing tho I propbably should find why it was crashing ngl
                path.push_back(tmpRec[nextDirection]);
                if (path.size() > 50)
                    break;

                //Make the new tmp rec based off the rec just found
                tmpRec[right] = {path.back().x + offset, path.back().y, 25, 25};
                tmpRec[left] = {path.back().x - offset, path.back().y, 25, 25};
                tmpRec[up] = {path.back().x, path.back().y - offset, 25, 25};
                tmpRec[down] = {path.back().x, path.back().y + offset, 25, 25};
            }

            int i = 0;
            for (std::list<int>::iterator it = pathDirections.begin(); i < sizeNextDir;
            i++, ++it ) {
                nextDir[i] = *it;
            }
            goToNextDir = 0;
            nextDirection = nextDir[0];

            if (pathDirections.size() > 20) {
                sizeNextDir = veryFarAwayMode;
            } else if (pathDirections.size() > 12) {
                sizeNextDir = farMode;
            } else if (pathDirections.size() > 5) {
                sizeNextDir = mediumMode;
            } else {
                sizeNextDir = closeMode;
            }

            // logStuff(mainDistanceAway);
            // logStuff(sizeNextDir);
        } else {
            goToNextDir++;
            nextDirection = nextDir[goToNextDir];
        }
    }
    //Debug tools

    // for (std::list<Rectangle>::iterator it = path.begin(); it != path.end(); ++it) {
    //     DrawRectangleRec(*it, RAYWHITE);
    // }
    // logStuff("Goto num: " << goToNextDir);

    // for (int i = 0; i < sizeNextDir; i++) {
    //     logStuff("num" << i << ": " << nextDir[i]);
    // }
    // logStuff("Nextdir: " << nextDirection);
    // logStuff("Size of Next Dir Array: " << sizeNextDir);

}




