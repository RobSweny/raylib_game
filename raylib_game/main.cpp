#include "raylib.h"


/* 
* CREATE A CHARACTER
* INPUT: BALL_POSITION (VECT2)
*/
void CreateCharacter(Vector2 ballPosition)
{
    // Create Circle
    DrawCircleV(ballPosition, 50, MAROON);
}

/*
* CREATING FUNCTION FOR MANAGING THE CONTROLLER
* INPUT: CHARACTER_POSITION (VECT2)
*/
Vector2 Controller(Vector2 charPosition)
{
    float moveSpeed = 4.0f;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) charPosition.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) charPosition.x -= moveSpeed;
    return charPosition;
}

int main() {
    // Determine the Game Window Width and Height
    const int screenWidth = 800;
    const int screenHeight = 450;
    Vector2 charPosition = { (float)screenWidth/2, (float)screenHeight/2 };


    // Initialize the Window
    InitWindow(screenWidth, screenHeight, "My Game");

    // Setting the Frames Per Second
    SetTargetFPS(60);

    // The Game Loop
    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/) {

        // Setup Canvas
        BeginDrawing();
        // Clear canvas to a specific color to avoid flicker
        ClearBackground(RAYWHITE);
        // Here goes all the Game Logic
        CreateCharacter(charPosition);
        charPosition = Controller(charPosition);

        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

