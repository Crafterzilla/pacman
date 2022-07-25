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

void Ghosts::MoveGhost(Rectangle& pacman, Walls& walls) {
    if (whichGhost == red) {
       RedAI(pacman, walls);
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

void Ghosts::RedAI(Rectangle& pacman, Walls& walls) {

    //ex: a rectangle will be created in the left. that rectangle will create four tmp
    //rectangeles up, down, left, and right. If there is collision, those rectangles will be given
    //null values. Then, with the remaining rectangles, the distance formula will be used to determine the
    //fastest rectangle to find pacman. Once found, the rectangle will be placed into the list and this process
    //will be repeated until the path rectagnlees are in contact with pacman.
    //then this process will be done again with another path and that path will be added to a vector of lists


    //potential solution could also be to store 25, and whatever direction
    std::list<Rectangle> path;
    std::list<int> pathDirections;
    enum shouldIresetDirections {wait, yes};
    // static int nextDir[2], goToNextDir = wait;


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
        // if (goToNextDir == 0)
        while(CheckCollisionRecs(pacman, path.back()) == false) {
            float possibleDistacnes[4], bestDistance = 1000.0f;

            for (int i = 0; i < 4; i++) {
                if (walls.WallCollsion(tmpRec[i]) || CheckCollisionRecs(previousRec, tmpRec[i])) {
                    tmpRec[i] = {10000.0f, 10000.0f, 0, 0};
                }
            }

            possibleDistacnes[right] = sqrt(pow((tmpRec[right].x - pacman.x), 2) + 
            pow((tmpRec[right].y - pacman.y), 2));

            possibleDistacnes[left] = sqrt(pow((tmpRec[left].x - pacman.x), 2) + 
            pow((tmpRec[left].y - pacman.y), 2));

            possibleDistacnes[up] = sqrt(pow((tmpRec[up].x - pacman.x), 2) + 
            pow((tmpRec[up].y - pacman.y), 2));

            possibleDistacnes[down] = sqrt(pow((tmpRec[down].x - pacman.x), 2) + 
            pow((tmpRec[down].y - pacman.y), 2));


            for (int dir = 0; dir < 4; dir++) {
                if (possibleDistacnes[dir] < bestDistance) {
                    bestDistance = possibleDistacnes[dir];
                    nextDirection = dir;
                }
            }
            pathDirections.push_back(nextDirection);

            std::list<Rectangle>::iterator it = --path.end();
            previousRec = *it;
            path.push_back(tmpRec[nextDirection]);
            if (path.size() > 50)
                break;

            tmpRec[right] = {path.back().x + offset, path.back().y, 25, 25};
            tmpRec[left] = {path.back().x - offset, path.back().y, 25, 25};
            tmpRec[up] = {path.back().x, path.back().y - offset, 25, 25};
            tmpRec[down] = {path.back().x, path.back().y + offset, 25, 25};
        }
        nextDirection = pathDirections.front();


        // nextDir[0] = pathDirections.front();
        // if (pathDirections.size() > 1);
        //     nextDir[1] = ++pathDirections.front();
    }

    for (std::list<Rectangle>::iterator it = path.begin(); it != path.end(); ++it) {
        DrawRectangleRec(*it, RAYWHITE);
    }

    logStuff("path size: " << path.size());
    logStuff("Nextdir: " << nextDirection);

    //movment: if timer is greater than 0.25, than the ai will move 1 pixel to
    //whatever nextDir is. Once moved 25 pixels, pxielCounter will be reset back to 25
    //and new nextDir will be used



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

    // //logStuff();
}