#include "raylib.h"

// Initialise the camera
Camera2D camera = { 0 };
// Determine the Game Window Width and Height
Vector2 screenSize = {1000.0f, 550.0f};
// Position the character in the middle of the screen
Vector2 charPosition = { (float)screenSize.x/2, (float)screenSize.y/2 };
// Set the size of the character
const int characterSize = 50;
// Character move speed
const float moveSpeed = 6.0f;

/* 
* CREATE A CHARACTER
* INPUT: BALL_POSITION (VECT2)
*/
void CreateCharacter()
{
    // Create Circle
    DrawCircleV(charPosition, characterSize, MAROON);
}

/*
* CREATING FUNCTION FOR MANAGING THE CONTROLLER
* INPUT: CHARACTER_POSITION (VECT2)
*/
Vector2 Controller()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        if (charPosition.x) charPosition.x += moveSpeed;
        
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        if (charPosition.x) charPosition.x -= moveSpeed;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) 
        camera.zoom += 0.005f;
    else 
        camera.zoom -= 0.005f;
    return charPosition;
}

/*
* CREATING FUNCTION TO SET UP CAMERA
*/
void CameraSetup()
{
    camera.target = charPosition;
    camera.offset = (Vector2){ screenSize.x/2, screenSize.y/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

int main() {
    CameraSetup();

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
        camera.target = charPosition;
        // Prevent the zoom value to avoid extreme zoom levels
        if (camera.zoom > 0.8f) camera.zoom = 0.8f;
        if (camera.zoom < 0.5f) camera.zoom = 0.5f;
        BeginMode2D(camera);  // Start 2D camera mode
            // Here goes all the Game Logic
            CreateCharacter();
            charPosition = Controller();
        EndMode2D();  // End 2D camera mode
        // teardown Canvas
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

