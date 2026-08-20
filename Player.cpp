#include "Player.hpp"

Player::Player(float startX, float startY) 
    : x(startX), y(startY), width(120.0f), height(20.0f), speed(500.0f) {}

void Player::update() {
    // frame-independent movement (multiplied by GetFrameTime())
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed * GetFrameTime();

    // prevent leaf from leaving the screen
    if (x < 0) x = 0;
    if (x + width > GetScreenWidth()) x = GetScreenWidth() - width;
}

void Player::draw() const {
    // Draw a green rectangle representing the Banana Leaf
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), 
                  static_cast<int>(width), static_cast<int>(height), GREEN);
}