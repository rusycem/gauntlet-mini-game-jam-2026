#pragma once
#include "raylib.h"

class GameObject {
public:
    virtual ~GameObject() = default; // raii virtual destructor
    
    virtual void update() = 0;
    
    // Dpure virtual
    virtual void draw() const = 0; 
};