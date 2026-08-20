#include "FallingItem.hpp"

FallingItem::FallingItem(float startX, float startY, float fallSpeed, Color itemColor)
    : x(startX), y(startY), width(20.0f), height(20.0f), 
      speed(fallSpeed), color(itemColor), active(true) {}

void FallingItem::update() {
    // fall downwards
    y += speed * GetFrameTime();
    
    // mark for deletion if it falls completely off bottom of screen
    if (y > GetScreenHeight()) {
        active = false;
    }
}

void FallingItem::draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), 
                  static_cast<int>(width), static_cast<int>(height), color);
}

void FallingItem::markCaught() {
    active = false;
}