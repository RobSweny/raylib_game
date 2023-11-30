#include "raylib.h"
#include "User.h"
#include "LifePickUp.h"
#include "Enemy.h"
#include "Projectile.h"
#include "SoundManagement.h"
#include "TextureManagement.h"
#include <math.h>
#include <string>
#include <vector>

// Determine the Game Window Width and Height
Vector2 screenSize = {1200.0f, 800.0f};
int projectileSpeed = 5;
int difficultyLevel = 0;
SoundManagement soundManagement;
TextureManagement textureManagement;
float levelClearedTime = GetTime();

// bool's to avoid sound repetition
bool gameOverSoundPlayed = false;
bool isGamePaused = false;
bool isLevelTransition = false;
bool lifePickupActive = false;

// creating the user
User user(50, { (float)screenSize.x/2, (float)screenSize.y/2 }, 4.0f, 3, soundManagement);

// Generate a random position for each enemy
Vector2 GenerateRandomPositionOutsideOfUserArea(int edge)
{
    Vector2 position;
    do {
        // Get random number for the x and y position, we do this until we find a position
        // that doesn't overlap with the user position with an additional radius of 200 around the user. 
        position.x = GetRandomValue(0, GetScreenWidth() - edge);
        position.y = GetRandomValue(0, GetScreenHeight() - edge);
    } while (CheckCollisionCircles(position, 50, user.position, 200));
    return position; 
}

LifePickUp lifepickup = { 1, 20, RED, GenerateRandomPositionOutsideOfUserArea(20), textureManagement.heart };

bool IsLevelCleared(const std::vector<Enemy>& enemies) {
    return enemies.empty();
}

Enemy GenerateEasyEnemy()
{
    Enemy easyEnemy (GenerateRandomPositionOutsideOfUserArea(10), 10, 0.5F, GREEN, 1);
    return easyEnemy;
}

Enemy GenerateHardEnemy()
{
    Enemy hardEnemy (GenerateRandomPositionOutsideOfUserArea(20), 20, 3.0F, RED, 5);
    return hardEnemy;
}

Enemy GenerateMediumEnemy()
{
    Enemy mediumEnemy (GenerateRandomPositionOutsideOfUserArea(15), 15, 2.0F, ORANGE, 3);
    return mediumEnemy;
}

Enemy GenerateSpeedyEnemy()
{
    Enemy speedBois (GenerateRandomPositionOutsideOfUserArea(8), 8, 4.0F, BLUE, 1);
    return speedBois;
}

// Based on the input parameter of the level of difficulty, we generate enemies.
// each level that the user passes, a more difficult set of enemies is created
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
        case 2:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateSpeedyEnemy());
            }
            break;
        case 3:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateMediumEnemy());
                enemies.push_back(GenerateHardEnemy());
            }
            break;
        case 4:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEasyEnemy());
                enemies.push_back(GenerateMediumEnemy());
                enemies.push_back(GenerateHardEnemy());
            }
            break;
        case 5:
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Victory!", GetScreenWidth() / 2 - MeasureText("Victory!", 50) / 2, GetScreenHeight() / 2, 50, BLACK);
            EndDrawing();
    }

    return enemies;
}

int main() {
    // Initialize the Window
    InitWindow(screenSize.x, screenSize.y, "My Game");
    // Setting the Frames Per Second
    SetTargetFPS(60);
    textureManagement.LoadTextures();
    soundManagement.PlayGameMusic();
    std::vector<Enemy> enemies = GenerateEnemies(difficultyLevel);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {
        // If the user presses 'P' the game is passed. The boolean sets its state as the opposite of the current state.
        if (IsKeyPressed(KEY_P)) {
            isGamePaused = !isGamePaused;
        }

        // if the life is ready to be set and it's not a level transition, create the object
        if (lifePickupActive && !isLevelTransition) {
            lifepickup.CreateLifePickUp();
        }

        // Collision detection with life pickup, play sound and prevent another life from being created.
        if (lifePickupActive && CheckCollisionCircles(user.position, user.size, lifepickup.position, lifepickup.size)) {
            user.GainHealth();
            lifepickup.LifePickedUp(soundManagement);
            lifePickupActive = false; // Deactivate the life pickup after collection
        }

        // If the user clears all the enemies and it's not currently a level transition
        if (IsLevelCleared(enemies) && !isLevelTransition) {
            // set the transition
            isLevelTransition = true;
            // capture what time the level was cleared, we use this to countdown the next level
            levelClearedTime = GetTime();
            soundManagement.PlayCountdownSound();

            // when the level is transitioning create 
            if (!lifePickupActive) {
                lifepickup.size = 20;
                lifepickup.position = GenerateRandomPositionOutsideOfUserArea(lifepickup.size);
                lifePickupActive = true;
            }
        }

        // Check if the enemies list has been cleared
        if (IsLevelCleared(enemies)) {
            // Pause the game for 3.5 seconds and introduce the next level
            if (GetTime() - levelClearedTime < 3.5f) {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), GetScreenWidth() / 2 - MeasureText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), 50) / 2, GetScreenHeight() / 2, 50, BLACK);
                EndDrawing();
                continue;
            }
            else {
                // When the next level starts, increase the difficult and generate the next set of enemies
                isLevelTransition = false;
                difficultyLevel++;
                lifepickup.CreateLifePickUp();
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
                DrawTexture(textureManagement.background, 0, 0, WHITE);
                if (user.CheckHealth()) {
                    if (!gameOverSoundPlayed) {
                        soundManagement.StopGameMusic();
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

                // For each of the enemies created, create their sprite and have them move towards the user
                for (Enemy &enemy : enemies)
                {
                    enemy.CreateEnemy();
                    enemy.MoveTowards(user);

                    // check collision with user
                    if (CheckCollisionCircles(user.position, user.size, enemy.position, enemy.size)) {
                        // If the user collides with an enemy, play a sound, remove user health and update
                        // the cooldown for when the user can be hit again.
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
    // Upload all loaded sounds
    soundManagement.UnloadSoundManagement();
    CloseWindow();
    return 0;
}