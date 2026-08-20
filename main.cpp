#include "raylib.h"
#include "Player.hpp"
#include "FallingItem.hpp"
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

enum class GameState {
    PLAYING,
    GAMEOVER
};

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

    Texture2D playerTex = LoadTexture("nasi_lemak.png");
    Texture2D chiliTex = LoadTexture("chili.png");

    std::unique_ptr<Player> leaf = std::make_unique<Player>(screenWidth / 2.0f - 60.0f, screenHeight - 60.0f, playerTex);
    
    // vector container
    std::vector<std::unique_ptr<FallingItem>> items;

    GameState state = GameState::PLAYING;
    float spawnTimer = 0.0f;
    int score = 0;
    int lives = 3;

    while (!WindowShouldClose()) {
        // update
        if (state == GameState::PLAYING) {
            leaf->update();

            // spawn a new item every 0.8 seconds
            spawnTimer += GetFrameTime();
            if (spawnTimer >= 0.8f) {
                float randomX = static_cast<float>(GetRandomValue(10, screenWidth - 30));
                items.push_back(std::make_unique<FallingItem>(randomX, -20.0f, 250.0f, chiliTex));
                spawnTimer = 0.0f;
            }

            // update items and check collisions
            for (auto& item : items) {
                item->update();
                if (item->isActive() && checkCollision(*leaf, *item)) {
                    item->markCaught();
                    score += 10;
                }
            }

            // cleanup and penalty check
            items.erase(std::remove_if(items.begin(), items.end(),
                [&lives, screenHeight](const std::unique_ptr<FallingItem>& i) { 
                    if (!i->isActive()) {
                        // if inactive AND at bottom of screen, reduce health
                        if (i->getY() >= screenHeight) {
                            lives--;
                        }
                        return true; 
                    }
                    return false;
                }), 
                items.end());

            if (lives <= 0) {
                state = GameState::GAMEOVER;
            }
        } 
        else if (state == GameState::GAMEOVER) {
            // Restart game logic
            if (IsKeyPressed(KEY_R)) {
                state = GameState::PLAYING;
                score = 0;
                lives = 3;
                items.clear();
                leaf = std::make_unique<Player>(screenWidth / 2.0f - 60.0f, screenHeight - 60.0f, playerTex);
            }
        }

        // render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (state == GameState::PLAYING) {
            leaf->draw();
            for (const auto& item : items) {
                item->draw();
            }
            
            DrawText(TextFormat("Score: %d", score), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("Lives: %d", lives), 10, 70, 20, RED);
            DrawText("Move with Left/Right Arrows! Catch the Sambal!", 10, 10, 20, DARKGRAY);
        } 
        else if (state == GameState::GAMEOVER) {
            DrawText("GAME OVER!", screenWidth / 2 - 100, screenHeight / 2 - 40, 40, RED);
            DrawText(TextFormat("Final Score: %d", score), screenWidth / 2 - 80, screenHeight / 2 + 10, 20, DARKGRAY);
            DrawText("Press 'R' to Restart", screenWidth / 2 - 110, screenHeight / 2 + 50, 20, DARKGRAY);
        }
        
        EndDrawing();
    }

    UnloadTexture(playerTex);
    UnloadTexture(chiliTex);

    CloseWindow();
    return 0;
}