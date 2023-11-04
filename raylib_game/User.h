// https://en.wikipedia.org/wiki/Include_guard
#ifndef USER_H
#define USER_H

#include <math.h>
#include <vector>
#include "raylib.h"
#include "Projectile.h"

struct User
{
    int size;
    Vector2 charPosition;
    float speed;
    // Array of struct Projectile
    std::vector<Projectile>& projectiles;

    // Creating function for managing the controller
    Vector2 Controller()
    {
        if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 8.0f;
        else if (IsKeyReleased(KEY_LEFT_SHIFT)) speed = 4.0f;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) charPosition.y -= speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) charPosition.x -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) charPosition.y += speed;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) charPosition.x += speed;
        if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE))) Shoot();
        return charPosition;
    }

    // Creating a character
    void CreateCharacter()
    {
        // Create Circle
        DrawCircleV(charPosition, size, MAROON);
    }

    // function
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
            float scaleFactor = speed / length;
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
};

#endif // USER_H