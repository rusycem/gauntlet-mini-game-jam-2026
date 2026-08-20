#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
private:
    float x, y;
    float width, height;
    float speed;
    Texture2D sprite;

public:
    Player(float startX, float startY, Texture2D texture);
    
    void update() override;
    void draw() const override;
    
    // const-correct getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};