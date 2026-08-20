#include "raylib.h"
#include "Player.hpp"
#include "FallingItem.hpp"
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

// aabb collsion
bool checkCollision(const Player& p, const FallingItem& item) {
    return (p.getX() < item.getX() + item.getWidth() &&
            p.getX() + p.getWidth() > item.getX() &&
            p.getY() < item.getY() + item.getHeight() &&
            p.getY() + p.getHeight() > item.getY());
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Nasi Lemak Drop");
    SetTargetFPS(60);

    std::unique_ptr<Player> leaf = std::make_unique<Player>(screenWidth / 2.0f - 60.0f, screenHeight - 40.0f);
    
    // vector container
    std::vector<std::unique_ptr<FallingItem>> items;
    
    float spawnTimer = 0.0f;
    int score = 0;

    while (!WindowShouldClose()) {
        // update
        leaf->update();

        // spawn a new item every 0.8 s
        spawnTimer += GetFrameTime();
        if (spawnTimer >= 0.8f) {
            float randomX = static_cast<float>(GetRandomValue(10, screenWidth - 30));
            items.push_back(std::make_unique<FallingItem>(randomX, -20.0f, 250.0f, RED)); // Red for Sambal
            spawnTimer = 0.0f;
        }

        // ipdate items and check collisions
        for (auto& item : items) {
            item->update();
            if (item->isActive() && checkCollision(*leaf, *item)) {
                item->markCaught();
                score += 10;
            }
        }

        // eraseclean up inactive items
        items.erase(std::remove_if(items.begin(), items.end(),
            [](const std::unique_ptr<FallingItem>& i) { return !i->isActive(); }), 
            items.end());

        // render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        leaf->draw();
        for (const auto& item : items) {
            item->draw();
        }
        
        DrawText(TextFormat("Score: %d", score), 10, 40, 20, DARKGRAY);
        DrawText("Move with Left/Right Arrows! Catch the Sambal!", 10, 10, 20, DARKGRAY);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}