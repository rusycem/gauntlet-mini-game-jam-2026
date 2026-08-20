#include "raylib.h"
#include "Player.hpp"
#include <memory>
#include <vector>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Nasi Lemak Drop");
    SetTargetFPS(60);

    // smart pointer
    std::unique_ptr<Player> leaf = std::make_unique<Player>(screenWidth / 2.0f - 60.0f, screenHeight - 40.0f);

    while (!WindowShouldClose()) {
        // update
        leaf->update();

        // render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        leaf->draw();
        DrawText("Move with Left/Right Arrows! Catch the ingredients!", 10, 10, 20, DARKGRAY);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}