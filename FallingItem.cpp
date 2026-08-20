#include "FallingItem.hpp"

FallingItem::FallingItem(float startX, float startY, float fallSpeed, Texture2D texture)
    : x(startX), y(startY), width(30.0f), height(42.0f), 
      speed(fallSpeed), sprite(texture), active(true) {}

void FallingItem::update() {
    // fall downwards
    y += speed * GetFrameTime();
    
    // mark for deletion if it falls completely off bottom of screen
    if (y > GetScreenHeight()) {
        active = false;
    }
}

void FallingItem::draw() const {
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(sprite.width), static_cast<float>(sprite.height) };
    Rectangle dest = { x, y, width, height };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}

void FallingItem::markCaught() {
    active = false;
}