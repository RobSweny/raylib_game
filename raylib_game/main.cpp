#include "raylib.h"
#include "User.h"
#include "Enemy.h"
#include "Projectile.h"
#include "SoundManagement.h"
#include <math.h>
#include <string>
#include <vector>

// Determine the Game Window Width and Height
Vector2 screenSize = {1200.0f, 800.0f};
int projectileSpeed = 5;
int difficultyLevel = 0;
SoundManagement soundManagement;
float levelClearedTime;

// bool's to avoid sound repetition
bool gameOverSoundPlayed = false;
bool isGamePaused = false;
bool isLevelTransition = false;

// creating the user
User user(50, { (float)screenSize.x/2, (float)screenSize.y/2 }, 4.0f, 2, soundManagement);

bool IsLevelCleared(const std::vector<Enemy>& enemies) {
    return enemies.empty();
}

Vector2 GenerateRandomPosition()
{
    Vector2 enemyPosition;
    do {
        enemyPosition.x = GetRandomValue(0, GetScreenWidth());
        enemyPosition.y = GetRandomValue(0, GetScreenHeight());
    } while (CheckCollisionCircles(enemyPosition, 50, user.position, 200));
    
    return enemyPosition; 
}

Enemy GenerateEasyEnemy()
{
    Enemy easyEnemy (GenerateRandomPosition(), 10, 0.5F, GREEN, 1);
    return easyEnemy;
}

Enemy GenerateHardEnemy()
{
    Enemy hardEnemy (GenerateRandomPosition(), 20, 3.0F, RED, 5);
    return hardEnemy;
}

Enemy GenerateMediumEnemy()
{
    Enemy mediumEnemy (GenerateRandomPosition(), 15, 2.0F, ORANGE, 3);
    return mediumEnemy;
}

Enemy GenerateSpeedyEnemy()
{
    Enemy speedBois (GenerateRandomPosition(), 8, 5.0F, BLUE, 1);
    return speedBois;
}

std::vector<Enemy> GenerateEnemies(int levelOfDifficulty)
{
    std::vector<Enemy> enemies{};
    int enemiesToGenerate = levelOfDifficulty * 10; 
    switch (levelOfDifficulty)
    {
        case 0:
            for (int i = 0; i < 10; i++)
            {
                enemies.push_back(GenerateEasyEnemy());
            }
            break;
        case 1:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEasyEnemy());
                enemies.push_back(GenerateMediumEnemy());
            }
            break;
        case 3:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateSpeedyEnemy());
            }
            break;
        case 4:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateMediumEnemy());
                enemies.push_back(GenerateHardEnemy());
            }
            break;
        case 5:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEasyEnemy());
                enemies.push_back(GenerateMediumEnemy());
                enemies.push_back(GenerateHardEnemy());
            }
            break;
    }

    return enemies;
}

int main() {
    // Initialize the Window
    InitWindow(screenSize.x, screenSize.y, "My Game");
    // Setting the Frames Per Second
    SetTargetFPS(60);
    soundManagement.PlayGameMusic();
    std::vector<Enemy> enemies = GenerateEnemies(difficultyLevel);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {
        // If the user presses 'P' the game is passed. The boolean sets its state as the opposite of the current state.
        if (IsKeyPressed(KEY_P)) {
            isGamePaused = !isGamePaused;
        }
        
        if (IsLevelCleared(enemies) && !isLevelTransition) {
            isLevelTransition = true;
            levelClearedTime = GetTime();
            soundManagement.PlayCountdownSound();
        }

        if (IsLevelCleared(enemies)) {
            if (GetTime() - levelClearedTime < 3.5f) {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), GetScreenWidth() / 2 - MeasureText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), 50) / 2, GetScreenHeight() / 2, 50, BLACK);
                EndDrawing();
                continue;
            } else {
                isLevelTransition = false;
                difficultyLevel++;
                enemies = GenerateEnemies(difficultyLevel);
            }
        }

        // If the game is passed, draw text on the screen to inform the user
        if (isGamePaused) {
            DrawText("Game Paused", screenSize.x / 2 - MeasureText("Game Paused", 20) / 2, screenSize.y / 2, 20, BLACK);
        } else {
            // Setup Canvas
            BeginDrawing();
                // Clear canvas to a specific color to avoid flicker
                ClearBackground(RAYWHITE);
                if (user.CheckHealth()) {
                    if (!gameOverSoundPlayed) {
                        soundManagement.GameOverSounds();
                        gameOverSoundPlayed = true;
                    }
                    // Display game over message
                    DrawText("Game Over", screenSize.x / 2 , screenSize.y / 2, 20, BLACK);
                    EndDrawing();
                    continue;  // Skip the rest of the game loop
                }
                
                user.CreateCharacter();
                user.position = user.Controller();
                // Draw player lives
                // https://github.com/raysan5/raylib-games/blob/master/classics/src/arkanoid.c
                for (int i = 0; i < user.currentHealth; i++) 
                {
                    DrawRectangle(20 + 40 * i, screenSize.y - 30, 35, 10, RED);
                }

                for (Enemy &enemy : enemies)
                {
                    enemy.CreateEnemy();
                    enemy.MoveTowards(user);

                    // check collision with user
                    if (CheckCollisionCircles(user.position, user.size, enemy.position, enemy.size)) {
                        soundManagement.PlayOuchSound();
                        user.LoseHealth();
                        user.UpdateCooldown();
                    }
                }
                // iterate over each item in the projectile vector (backwards, as it's furthest away from the user (origin))
                for (int i = user.projectiles.size() - 1; i >= 0; --i) {
                    bool projectileHit = false;
                    user.projectiles[i].position.x += user.projectiles[i].direction.x * user.projectiles[i].speed;
                    user.projectiles[i].position.y += user.projectiles[i].direction.y * user.projectiles[i].speed;

                    // iterate over the enemies backwards
                    for (int j = enemies.size() - 1; j >= 0; --j) {
                        // Check if the projectile position and size collides with the enemy position and size
                        if (CheckCollisionCircles(user.projectiles[i].position, user.projectileSize, enemies[j].position, enemies[j].size)) {
                            // if the enemy function 'TakeDamage' returns true, erase the enemy
                            // this function checks if the current health of the enemy is <= 0
                            if (enemies[j].TakeDamage(user.projectiles[i].damage)) {
                                enemies.erase(enemies.begin() + j);
                            }
                            // Break out of the loop if an enemy has been hit.
                            projectileHit = true;
                            break; 
                        }
                    }
                
                    // Check if the projectile has hit an enemy
                    if (projectileHit) {
                        // If the projectile has hit an enemy, remove it from the projectiles vector
                        user.projectiles.erase(user.projectiles.begin() + i); // Remove the used projectile
                    } else {
                        // If the projectile didn't hit an enemy, draw it at its new position
                        user.projectiles[i].Draw();
                    }
                }
        }
        // teardown Canvas
        EndDrawing();
    }
    soundManagement.UnloadSoundManagement();
    CloseWindow();
    return 0;
}