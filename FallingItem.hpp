#pragma once
#include "GameObject.hpp"

class FallingItem : public GameObject {
private:
    float x, y;
    float width, height;
    float speed;
    Color color;
    Texture2D sprite;
    bool active; 

public:
    FallingItem(float startX, float startY, float fallSpeed, Texture2D texture);
    
    void update() override;
    void draw() const override;
    
    //const-correct getters for collision math
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    bool isActive() const { return active; }
    
    void markCaught();
};