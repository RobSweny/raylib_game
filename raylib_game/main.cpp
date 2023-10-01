#include "raylib.h"


/* 
* CREATE A CHARACTER
* INPUT: BALL_POSITION (VECT2)
*/
void CreateCharacter(Vector2 ballPosition, int charSize)
{
    // Create Circle
    DrawCircleV(ballPosition, charSize, MAROON);
}

/*
* CREATING FUNCTION FOR MANAGING THE CONTROLLER
* INPUT: CHARACTER_POSITION (VECT2)
*/
Vector2 Controller(Vector2 charPosition, float frameWidth, int charSize)
{
    float moveSpeed = 6.0f;
    int rightHandBorder = frameWidth - charSize;
    int leftHandBorder = charSize;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        if (charPosition.x < rightHandBorder) charPosition.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        if (charPosition.x > leftHandBorder) charPosition.x -= moveSpeed;
    return charPosition;
}

int main() {
    // Determine the Game Window Width and Height
    Vector2 screenSize = {800.0f, 450.0f};
    // Position the character in the middle of the screen
    Vector2 charPosition = { (float)screenSize.x/2, (float)screenSize.y/2 };
    int charSize = 50;

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
        // Here goes all the Game Logic
        CreateCharacter(charPosition, charSize);
        charPosition = Controller(charPosition, screenSize.x, charSize);

        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

