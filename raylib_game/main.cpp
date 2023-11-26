#include "raylib.h"
#include "User.h"
#include "Enemy.h"
#include "Projectile.h"
#include <math.h>
#include <vector>

// Determine the Game Window Width and Height
Vector2 screenSize = {1200.0f, 800.0f};
int projectileSpeed = 5;
std::vector<Enemy> enemies;

// creating the user
User user(50, { (float)screenSize.x/2, (float)screenSize.y/2 }, 4.0f, 3);
// creating different types of enemies
Enemy easyEnemy({ (float) 100, (float) 100 }, 10, 1.0F, GREEN, 1);
Enemy mediumEnemy({ (float) 100, (float) 100 }, 25, 2.0F, ORANGE, 3);
Enemy hardEnemy({ (float) 100, (float) 100 }, 40, 4.0F, RED, 5);

int main() {
    // Initialize the Window
    InitWindow(screenSize.x, screenSize.y, "My Game");

    // Setting the Frames Per Second
    SetTargetFPS(60);

    enemies.push_back(easyEnemy);
    enemies.push_back(mediumEnemy);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {
        // Setup Canvas
        BeginDrawing();
            // Clear canvas to a specific color to avoid flicker
            ClearBackground(RAYWHITE);

            if (user.CheckHealth()) {
                // Display game over message
                DrawText("Game Over", screenSize.x / 2 , screenSize.y / 2, 20, BLACK);
                EndDrawing();
                continue;  // Skip the rest of the game loop
            }
            
            user.CreateCharacter();
            user.position = user.Controller();

            // easyEnemy.CreateEnemy();
            for (Enemy &enemy : enemies)
            {
                enemy.CreateEnemy();
                enemy.MoveTowards(user);

                // check collision with user
                if (CheckCollisionCircles(user.position, user.size, enemy.position, enemy.size)) {
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
                
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}