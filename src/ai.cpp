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
        this->x = 350;
        this->y = 325;
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

void Ghosts::MoveGhost(Rectangle& pacman, Walls& walls) {

    if (whichGhost == red) {
       RedAI(pacman, walls, 0);
    //    RedAIScatter(walls);
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

void Ghosts::RedAI(Rectangle& pacman, Walls& walls, int mode) {


    switch (mode) {
        case chase: 
            PathFind(pacman, walls); 
            break;
        case scatter: 
            Rectangle scatterCorner = {31 * 25, 2 * 25, 25, 25};
            PathFind(scatterCorner, walls);
            break;
    }

    static int moveX = 0, moveY = 0;
    float speed = 200.0f;

    // make the ghost move the best direction

    if (nextDirection == left) {
        //RoundtoNearest25(this->y);
        moveX = -1;
        moveY = 0;
        currentDirection = left;
    }
    else if (nextDirection == right) {
        //RoundtoNearest25(this->y);
        moveX = 1;
        moveY = 0;
        currentDirection = right;
    } else if (nextDirection == up) {
        //RoundtoNearest25(this->x);
        moveY = -1;
        moveX = 0;
        currentDirection = up;
    } else if (nextDirection == down) {
        //RoundtoNearest25(this->x);
        moveY = 1;
        moveX = 0;
        currentDirection = down;
    }

    if (walls.WallCollsion(hitbox)) {
        RoundtoNearest25(this->y);
        RoundtoNearest25(this->x);
        //this->x -= 25;
        moveX = 0;
        moveY = 0;
    }

    this->x += moveX * speed * GetFrameTime();
    this->y += moveY * speed * GetFrameTime();
}

void Ghosts::PathFind(Rectangle& rec, Walls& walls) {
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
    static int nextDir[10], goToNextDir = 4;
    static int sizeNextDir = sizeof(nextDir) / sizeof(*nextDir);

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
    

    for (std::list<Rectangle>::iterator it = path.begin(); it != path.end(); ++it) {
        DrawRectangleRec(*it, RAYWHITE);
    }
    logStuff("Goto num: " << goToNextDir);

    for (int i = 0; i < sizeNextDir; i++) {
        logStuff("num" << i << ": " << nextDir[i]);
    }
    // logStuff("num1: " << nextDir[0]);
    // logStuff("num2: " << nextDir[1]);
    // logStuff("num3: " << nextDir[2]);
    // logStuff("num3: " << nextDir[3]);
    logStuff("Nextdir: " << nextDirection);
    logStuff("Size of Next Dir Array: " << sizeNextDir);

}




