#include "raylib.h"
#include <math.h>
#include <vector>


// Determine the Game Window Width and Height
Vector2 screenSize = {1200.0f, 800.0f};
// Position the character in the middle of the screen
Vector2 charPosition = { (float) screenSize.x/2, (float) screenSize.y/2 };
// Set the size of the character
const int characterSize = 50;
// Character move speed
float moveSpeed = 4.0f;
int projectileSpeed = 5;
typedef struct Projectile
{
    Vector2 position;
    Vector2 direction;
    float speed;
} Projectile;

// Array of struct Projectile
std::vector<Projectile> projectiles;

/* 
* CREATE A CHARACTER
* INPUT: BALL_POSITION (VECT2)
*/
void CreateCharacter()
{
    // Create Circle
    DrawCircleV(charPosition, characterSize, MAROON);
}

void Shoot()
{
    // Calculate the direction vector from player to mouse when shooting starts
    Vector2 mousePos = GetMousePosition();
    Vector2 direction;

    // Calculate the direction vector from player to mouse when shooting starts
    direction.x = mousePos.x - charPosition.x;
    direction.y = mousePos.y - charPosition.y;
    
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normalize the direction vector and scale it by the projectile speed
    if (length > 0)
    {
        float scaleFactor = projectileSpeed / length;
        direction.x *= scaleFactor;
        direction.y *= scaleFactor;
    }
    
    Projectile newProjectile = {
        .position = charPosition,
        .direction = direction,
        .speed = 1.0f
    };

    // Push new projectile to the back of the array
    projectiles.push_back(newProjectile);
}


/*
* CREATING FUNCTION FOR MANAGING THE CONTROLLER
* INPUT: CHARACTER_POSITION (VECT2)
*/
Vector2 Controller()
{
    if (IsKeyDown(KEY_LEFT_SHIFT)) moveSpeed = 8.0f;
    else if (IsKeyReleased(KEY_LEFT_SHIFT)) moveSpeed = 4.0f;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) charPosition.y -= moveSpeed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) charPosition.x -= moveSpeed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) charPosition.y += moveSpeed;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) charPosition.x += moveSpeed;
    if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE))) Shoot();
    return charPosition;
}

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
            CreateCharacter();
            charPosition = Controller();
                
            for (size_t i = 0; i < projectiles.size(); ++i)
            {
                // Move the projectile based on the direction vector
                projectiles[i].position.x += projectiles[i].direction.x;
                projectiles[i].position.y += projectiles[i].direction.y;
                // Draw projectile
                DrawCircleV(projectiles[i].position, 5, BLUE);
            }
                
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}