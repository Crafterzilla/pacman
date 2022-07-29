#include "../include/gameConditions.h"

GameConditions::GameConditions(Ghosts& redGhost, Ghosts& blueGhost,
Ghosts& pinkGhost, Ghosts& orangeGhost, 
Player& pacman, Balls& balls, Walls& walls, Texture2D list[]) :
    redGhost(redGhost), 
    blueGhost(blueGhost), 
    pinkGhost(pinkGhost),
    orangeGhost(orangeGhost), 
    pacman(pacman), 
    balls(balls), 
    walls(walls) {
    IsPlayerAlive = true;
    IsPlayerWinner = false;
    IsPaused = false;
    lives = 3;
    score = 0;
    round = 0;
    timer = 0.0f;
    gameStart = true;
    this->list = list; 


    //Sound Init

    pacRemix = LoadMusicStream("audio/pacmanRemixi.mp3");
    chompSound = LoadSound("audio/chomp.mp3");
    sirenB = LoadSound("audio/sirenB.mp3");
    sirenC = LoadSound("audio/sirenC.mp3");
    deathSound = LoadSound("audio/death.mp3");
    ghostEaten = LoadSound("audio/eatGhost.mp3");
}

void GameConditions::CheckIfPacmanAteBigBall() {
    redGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    pinkGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    orangeGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
    blueGhost.CheckConditions(balls.BigBallCollision(pacman.hitbox));
}

void GameConditions::MoveAllGhosts() {
    redGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    pinkGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    orangeGhost.MoveGhost(pacman, redGhost.hitbox, walls);
    blueGhost.MoveGhost(pacman, redGhost.hitbox, walls);
}

void GameConditions::DrawAllEntities() {
    pacman.DrawEntity();
    redGhost.DrawEntity();
    pinkGhost.DrawEntity();
    orangeGhost.DrawEntity();
    blueGhost.DrawEntity();
}

bool GameConditions::PauseGame() {
    if (IsKeyPressed(KEY_P) && !IsPaused) {
        IsPaused = true;
    }
    else if (IsKeyPressed(KEY_P) && IsPaused) {
        IsPaused = false;
    }

    return IsPaused;
}
void GameConditions::DrawPauseMenu() {
    if (IsPaused) {
        Rectangle pauseMenu = {175, 275, 25 * 14, 25 * 12};
        Color offPurple = {178, 102, 255, 200};
        DrawRectangleRec(pauseMenu, offPurple);

        DrawText("Game\nPaused", 225, 325, 50, RAYWHITE);

        Rectangle resumeBox = {225, 475, 25 * 4, 25 * 3};
        Color lessOffPurple = {127, 0, 255, 200}, 
        moreOffPurple= {229, 204, 255, 200};

        DrawRectangleLinesEx(resumeBox, 3.0f, WHITE);

        if (CheckMouseCollisionRec(resumeBox)) {
            DrawRectangleRec(resumeBox, moreOffPurple);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                IsPaused = false;
        }
        else
            DrawRectangleRec(resumeBox, lessOffPurple);

        DrawText("Resume", 245, 505, 17, RAYWHITE);

        Rectangle playAgainBox = {375, 475, 25 * 4, 25 * 3};

        DrawRectangleLinesEx(playAgainBox, 3.0f, RAYWHITE);
        if (CheckMouseCollisionRec(playAgainBox)) {
            DrawRectangleRec(playAgainBox, moreOffPurple);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                IsPaused = false;
                RestartMap(true);
            }
        }
        else
            DrawRectangleRec(playAgainBox, lessOffPurple);

        DrawText("Play\nAgain?", 405, 495, 17, RAYWHITE);
    }
}

void GameConditions::DrawGUI(Texture2D pacman) {
    const Rectangle pacmanSprite = {25, 0, 25, 25};

    Rectangle pos = {0, 825, 25, 25};
    for (int i = 0; i < lives; i++) {
        DrawTexturePro(pacman, pacmanSprite, pos, {0, 0}, 0.0f, RAYWHITE);
        pos.x += 25;
    }

    std::string scoreText = "Score: " + std::to_string(score);

    DrawText(scoreText.c_str(), 0, 0, 50, RAYWHITE);

    std::string roundText = "Round: " + std::to_string(round);

    DrawText(roundText.c_str(), 425, 0, 50, RAYWHITE);
}

bool GameConditions::CheckMouseCollisionRec(const Rectangle& rec) {
    float x = GetMouseX(), y = GetMouseY();
    if (x > rec.x && x < (rec.x + rec.width) && y > rec.y
    && y < (rec.y + rec.height)) {
        return true;
    }
    return false;
}

void GameConditions::CheckGameOverOrWon() {
    Ghosts ghosts[4] = {redGhost, blueGhost, 
    pinkGhost, orangeGhost};
    if (balls.GetBallCount() == 0) {
        round++;
        score += 1000;
        RestartMap(false);
    } 
    
    for (int i = 0; i < 4; i++) {
        if (CheckCollisionRecs(ghosts[i].hitbox, pacman.hitbox) && (ghosts[i].GetGhostMode()
        != 2 && ghosts[i].GetGhostMode() != 3)) {
            lives--;
            RestartMap(false);
        }
    }

    if (lives == 0) {
        RestartMap(true);
    }
}

void GameConditions::RestartMap(bool fullRestart) {
    IsPlayerAlive = false;

    StopMusicStream(pacRemix);
    PlaySound(deathSound);







    enum TextureNames {redTex, pinkTex, orangeTex, blueTex, floating, scared, pacmanSprite};
    enum {red, blue, pink, orange};

    Ghosts redGhost(list[redTex], list[floating], list[scared], red);
    Ghosts blueGhost(list[blueTex], list[floating], list[scared],blue);
    Ghosts pinkGhost(list[pinkTex], list[floating], list[scared], pink);
    Ghosts orangeGhost(list[orangeTex], list[floating], list[scared], orange);

    Player pacman(list[pacmanSprite]);
    Balls balls(walls);

    this->redGhost = redGhost;
    this->blueGhost = blueGhost;
    this->orangeGhost = orangeGhost;
    this->pinkGhost = pinkGhost;
    this->pacman = pacman;

    if (fullRestart) {
        this->balls = balls;
        lives = 3;
        score = 0;
        round = 0;
        timer = 0.0f;
    }

}

void GameConditions::CheckAllConditions() {
    CheckGameOverOrWon();
    CheckIfPacmanAteBigBall();
}

void GameConditions::StartGame() {

}

void GameConditions::PlayAllSound() {
    UpdateMusicStream(pacRemix);

    if (IsPlayerAlive) {
        if (!IsPaused)
            SetMusicVolume(pacRemix, 0.25f);
        else
            SetMusicVolume(pacRemix, 0.5f);

        if (!IsMusicStreamPlaying(pacRemix)) {
            PlayMusicStream(pacRemix);
        }      
        // PlayMusicStream(pacRemix);
        if (balls.BallCollision(pacman.hitbox) || balls.BigBallCollision(pacman.hitbox)) {
            SetSoundVolume(chompSound, 0.5f);
            PlaySound(chompSound);
            score += 10;
        }

        // for (int i = 0; i < 4; i++) {
        //     switch(ghosts[i].GetGhostMode()) {
        //         case 0:
        //         case 1:
        //             PlaySound(sirenB);
        //             break;
        //         case 2:
        //         case 3:
        //             break;
        //     }
        // }
    }
}

GameConditions::~GameConditions() {
    UnloadMusicStream(pacRemix);
    UnloadSound(sirenB);
    UnloadSound(sirenC);
    UnloadSound(deathSound);
    UnloadSound(ghostEaten);
}