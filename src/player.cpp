#include "../include/player.h"

Player::Player(Texture2D sprite) {
    this->pacmanSprite = sprite;
    this->x = 325;
    this->y = 625;
    this->pacman = {x, y, 25, 25};
};

void Player::DrawPlayer() {
    DrawTextureRec(pacmanSprite, pacman, {x, y}, RAYWHITE);
}