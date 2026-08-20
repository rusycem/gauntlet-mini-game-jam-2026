#include "Player.hpp"

Player::Player(float startX, float startY, Texture2D texture) : x(startX), y(startY), width(120.0f), height(56.0f), speed(500.0f), sprite(texture) {}

void Player::update() {
    // frame-independent movement (multiplied by GetFrameTime())
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed * GetFrameTime();

    // prevent leaf from leaving the screen
    if (x < 0) x = 0;
    if (x + width > GetScreenWidth()) x = GetScreenWidth() - width;
}

void Player::draw() const {
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(sprite.width), static_cast<float>(sprite.height) };
    
    Rectangle dest = { x, y, width, height };
    
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}