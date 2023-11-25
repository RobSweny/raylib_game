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

User user(50, { (float)screenSize.x/2, (float)screenSize.y/2 }, 4.0f, 3);
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

            for (Projectile &projectile : user.projectiles)
            {
                projectile.position.x += projectile.direction.x * projectile.speed;
                projectile.position.y += projectile.direction.y * projectile.speed;
                projectile.Draw();
            }
                
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}