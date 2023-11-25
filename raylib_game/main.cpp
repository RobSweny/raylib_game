#include "raylib.h"
#include "User.h"
#include "Enemy.h"
#include "Projectile.h"
#include <math.h>
#include <vector>

// Determine the Game Window Width and Height
Vector2 screenSize = {1200.0f, 800.0f};
int projectileSpeed = 5;
std::vector<Projectile> projectiles;

// creating the user
User user(50, { (float)screenSize.x/2, (float)screenSize.y/2 }, 4.0f, 3);
/// creating different types of enemies
Enemy easyEnemy({ (float) 100, (float) 100 }, 10, 1.0F, GREEN, 1);
Enemy mediumEnemy({ (float) 100, (float) 100 }, 25, 2.0F, GREEN, 3);
Enemy hardEnemy({ (float) 100, (float) 100 }, 40, 4.0F, GREEN, 5);

int main() {
    // Initialize the Window
    InitWindow(screenSize.x, screenSize.y, "My Game");

    // Setting the Frames Per Second
    SetTargetFPS(60);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/) {


        // Setup Canvas
        BeginDrawing();
            // Clear canvas to a specific color to avoid flicker
            ClearBackground(RAYWHITE);
            user.CreateCharacter();
            user.position = user.Controller();

            easyEnemy.CreateEnemy();                
            easyEnemy.MoveTowards(user.position);

            // iterates over each projectile and updates it x and y position based on direction and speed
            // it then re-draws the projectile
            for (Projectile &projectile : user.projectiles)
            {
                projectile.position.x += projectile.direction.x * projectile.speed;
                projectile.position.y += projectile.direction.y * projectile.speed;
                projectile.Draw();
            }

            // iterate over each item in the projectile vector (backwards, as it's furthest away from the user (origin))
            for (int i = user.projectiles.size() - 1; i >= 0; --i) {
                // check if the current position of the project position and size, collides with the enemy position and size
                if (CheckCollisionCircles(user.projectiles[i].position, user.projectileSize, easyEnemy.position, easyEnemy.size)) {
                    // take damage from that enemy
                    easyEnemy.TakeDamage(user.projectiles[i].damage);
                    if (easyEnemy.currentHealth <= 0)
                    {
                        easyEnemy.size = 0;
                    }
                    // when we find a projectile that has collided with the user, erase that project from the vector
                    user.projectiles.erase(user.projectiles.begin() + i);
                }
            }
                
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}