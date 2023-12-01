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
Vector2 screenSize = {1280.0f, 720.0f};
Vector2 centerOfScreen = { (float)screenSize.x/2, (float)screenSize.y/2 };
TextureManagement textureManagement;
SoundManagement soundManagement;
Animation animation;
int selectedItemIndex = 0;
int difficultyLevel = 0;
float levelClearedTime = GetTime();
float timeOfDeath = GetTime();

enum GameState {
    MENU,
    PLAYING,
    EXIT
};

enum EnemyTypes {
    EASY,
    MEDIUM,
    HARD,
    SPEEDY
};

GameState currentGameState = MENU;
std::vector<std::string> menuItems = {"Start Game", "Fullscreen", "Exit Game"};
int selectedItem = 0;

// bool's to avoid sound repetition
bool gameOverSoundPlayed = false;
bool isGamePaused = false;
bool isLevelTransition = false;
bool lifePickupActive = false;
   
// Generate a random position for each enemy
Vector2 GenerateRandomPositionOutsideOfUserArea(int edge)
{
    Vector2 position;
    do {
        // Get random number for the x and y position, we do this until we find a position
        // that doesn't overlap with the user position with an additional radius of 200 around the user. 
        position.x = GetRandomValue(0, GetScreenWidth() - edge);
        position.y = GetRandomValue(0, GetScreenHeight() - edge);
    } while (CheckCollisionCircles(position, 50, centerOfScreen, 200));
    return position; 
}

bool IsLevelCleared(const std::vector<Enemy>& enemies) {
    return enemies.empty();
}

Enemy GenerateEnemy(EnemyTypes enemyType)
{   
    switch (enemyType)
    {
        case EASY:
            return Enemy ( GenerateRandomPositionOutsideOfUserArea(0), 25, 0.5F, 1, textureManagement.easyEnemyAnimation );
            break;
        case MEDIUM:  
            return Enemy (GenerateRandomPositionOutsideOfUserArea(0), 30, 2.0F, 3, textureManagement.mediumEnemyAnimation);
            break;
        case HARD:
            return Enemy (GenerateRandomPositionOutsideOfUserArea(0), 35, 3.0F, 5, textureManagement.hardEnemyAnimation);
            break;
        case SPEEDY:  
            return Enemy (GenerateRandomPositionOutsideOfUserArea(0), 25, 4.0F, 1, textureManagement.speedyEnemyAnimation);
            break;  
    }
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
                enemies.push_back(GenerateEnemy(EASY));
            }
            break;
        case 1:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEnemy(EASY));
                enemies.push_back(GenerateEnemy(MEDIUM));
            }
            break;
        case 2:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEnemy(SPEEDY));
            }
            break;
        case 3:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEnemy(MEDIUM));
                enemies.push_back(GenerateEnemy(HARD));
            }
            break;
        case 4:
            for (int i = 0; i < enemiesToGenerate; i++)
            {
                enemies.push_back(GenerateEnemy(EASY));
                enemies.push_back(GenerateEnemy(MEDIUM));
                enemies.push_back(GenerateEnemy(HARD));
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
    InitWindow(screenSize.x, screenSize.y, "Bobble Bob's Last Dance");
    // Setting the Frames Per Second
    SetTargetFPS(60);
    textureManagement.Initialize();
    soundManagement.PlayGameMusic();
    User user(50, centerOfScreen, 4.0f, 3, soundManagement, textureManagement.playerRunningAnimation);
    LifePickUp lifepickup = { 1, 60, GenerateRandomPositionOutsideOfUserArea(20), textureManagement.heart};
    std::vector<Enemy> enemies = GenerateEnemies(difficultyLevel);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {
        // Update and Draw per frame
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentGameState) {
            case MENU:
                ClearBackground(WHITE);
                // Clear canvas to a specific color to avoid flicker
                DrawTexture(textureManagement.menu, 0, 0, WHITE);
                if (IsKeyPressed(KEY_DOWN)) {
                    selectedItemIndex = (selectedItemIndex + 1) % menuItems.size();
                }
                if (IsKeyPressed(KEY_UP)) {
                    selectedItemIndex = (selectedItemIndex - 1 + menuItems.size()) % menuItems.size();
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    switch (selectedItemIndex) {
                        // Start game
                        case 0:
                            currentGameState = PLAYING;
                            break;
                        // Fullscreen
                        case 1:
                            // After we toggle full screen we have to ensure existing variables get updated
                            ToggleFullscreen();
                            screenSize.x = (float) GetScreenWidth();
                            screenSize.y = (float) GetScreenHeight();
                            centerOfScreen = { screenSize.x / 2, screenSize.y / 2 };
                            break;
                        // Exit
                        case 2:
                            currentGameState = EXIT;
                            break;
                    }
                }

                // For each item in menu items
                for (int i = 0; i < menuItems.size(); ++i) {
                    // Tenory operator to check if the selectedItemIndex is the created menu item, if it is. Paint it Red.
                    Color color = (i == selectedItemIndex) ? YELLOW : WHITE;
                    // Draw the menu item.
                    DrawText(menuItems[i].c_str(), 100, 200 + 80 * i, 60, color);
                }
                break;
            case PLAYING:
            {
                float deltaTime = GetFrameTime();
                // If the user presses 'P' the game is passed. The boolean sets its state as the opposite of the current state.
                if (IsKeyPressed(KEY_P)) {
                    isGamePaused = !isGamePaused;
                }
 
                // if the life is ready to be set and it's not a level transition, create the object
                if (lifePickupActive && !isLevelTransition) {
                    lifepickup.CreateLifePickUp(lifepickup.position);
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
                        lifepickup.size = 60;
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
                            DrawText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), GetScreenWidth() / 2 - MeasureText(("Level " + std::to_string(difficultyLevel + 1)).c_str(), 75) / 2, GetScreenHeight() / 2, 50, BLACK);
                        EndDrawing();
                        continue;
                    }
                    else {
                        // When the next level starts, increase the difficult and generate the next set of enemies
                        isLevelTransition = false;
                        difficultyLevel++;
                        lifepickup.CreateLifePickUp(GenerateRandomPositionOutsideOfUserArea(20));
                        // Create the new array of enemies based on the difficulty level
                        enemies = GenerateEnemies(difficultyLevel);
                    }
                }

                // If the game is passed, draw text on the screen to inform the user
                if (isGamePaused) {
                    DrawText("Game Paused", screenSize.x / 2 - MeasureText("Game Paused", 60) / 2, screenSize.y / 2, 60, RED);
                } else {
                    // Setup Canvas
                    BeginDrawing();
                        ClearBackground(WHITE);
                        // Clear canvas to a specific color to avoid flicker
                        DrawTexture(textureManagement.background, 0, 0, WHITE);
                        if (user.CheckHealth()) {
                            if (!gameOverSoundPlayed) {
                                soundManagement.StopGameMusic();
                                soundManagement.GameOverSounds();
                                gameOverSoundPlayed = true;
                                timeOfDeath = GetTime();
                            }
                            // Display game over message
                            DrawText("Game Over!", GetScreenWidth() / 2 - MeasureText("Game Over!", 100) / 2, GetScreenHeight() / 2, 100, WHITE);
                            if (GetTime() - timeOfDeath > 3.0F)
                            {
                                currentGameState = MENU;
                            }
                            EndDrawing();
                            continue;  // Skip the rest of the game loop
                        }
                        
                        user.Update(deltaTime);
                        user.CreateCharacter();
                        user.Controller();
                        // Draw player lives
                        // https://github.com/raysan5/raylib-games/blob/master/classics/src/arkanoid.c
                        for (int i = 0; i < user.currentHealth; i++) 
                        {   
                            // Ternory operator to check where to draw the user health 
                            IsWindowFullscreen() ?
                            DrawRectangle(20 + 50 * i, GetScreenHeight() - 120, 40, 20, RED) :
                            DrawRectangle(20 + 40 * i, GetScreenHeight() - 30, 35, 10, RED);
                        }

                        // For each of the enemies created, create their sprite and have them move towards the user
                        for (Enemy &enemy : enemies)
                        {
                            enemy.Update(deltaTime, user);
                            enemy.CreateEnemy();

                            // check collision with user
                            if (CheckCollisionCircles(user.position, user.size, enemy.position, enemy.size)) {
                                if (!user.isOnHealthCooldown) {
                                    // If the user collides with an enemy, play a sound, remove user health and update
                                    // the cooldown for when the user can be hit again.
                                    soundManagement.PlayOuchSound();
                                    user.LoseHealth();
                                    user.UpdateCooldown();     
                                } else {
                                    user.UpdateCooldown();
                                }
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
                break;
            }
            case EXIT:
                EndDrawing();
                CloseWindow();
                return 0;
        }
        // teardown Canvas
        EndDrawing();
    }
    // Upload all loaded sounds and textures
    soundManagement.UnloadSoundManagement();
    textureManagement.UnloadTextureManagement();
    CloseWindow();
    return 0;
}