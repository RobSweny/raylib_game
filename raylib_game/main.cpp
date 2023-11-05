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

User user =
{
    .size = 50,
    // users initial position is in the middle of the screen
    .charPosition = { (float) screenSize.x/2, (float) screenSize.y/2 },
    .speed = 4.0F,
    .projectiles = projectiles
};


Enemy easyEnemy =
{
    .position = { (float) 100, (float) 100 },
    .size = 10,
    .color = GREEN,
    .speed = 1.0F
};

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
            user.charPosition = user.Controller();

            easyEnemy.CreateEnemy();                

            for (size_t i = 0; i < projectiles.size(); ++i)
            {
                // Move the projectile based on the direction vector
                projectiles[i].position.x += projectiles[i].direction.x;
                projectiles[i].position.y += projectiles[i].direction.y;
                // Draw projectile
                Projectile projectile;
                projectile.CreateProjectile(projectiles[i].position, 5, BLUE);
            }
                
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}