// https://en.wikipedia.org/wiki/Include_guard
#ifndef USER_H
#define USER_H

#include <math.h>
#include <vector>
#include "raylib.h"
#include "Projectile.h"
#include "Health.h"

struct User : Health
{
    int size;
    Vector2 position;
    float speed;
    int maxHealth;
    // Array of struct Projectile
    std::vector<Projectile> projectiles{};

    User(int size, Vector2 position, float speed, int maxHealth) 
            : size(size), position(position), speed(speed), maxHealth(maxHealth) {}

    // Creating function for managing the controller
    Vector2 Controller()
    {
        if (IsKeyDown(KEY_LEFT_SHIFT)) speed = 8.0f;
        else if (IsKeyReleased(KEY_LEFT_SHIFT)) speed = 4.0f;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) position.y -= speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) position.x -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) position.y += speed;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) position.x += speed;
        if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE))) Shoot();
        return position;
    }

    // Creating a character
    void CreateCharacter()
    {
        // Create Circle
        DrawCircleV(position, size, MAROON);
    }

    // function
    void Shoot()
    {
        // Calculate the direction vector from player to mouse when shooting starts
        Vector2 mousePos = GetMousePosition();
        Vector2 direction;

        // Calculate the direction vector from player to mouse when shooting starts
        direction.x = mousePos.x - position.x;
        direction.y = mousePos.y - position.y;
        
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize the direction vector and scale it by the projectile speed
        if (length > 0)
        {
            float scaleFactor = speed / length;
            direction.x *= scaleFactor;
            direction.y *= scaleFactor;
        }
        
        Projectile newProjectile = { position, direction, 1.0f, RED };
        // Push new projectile to the back of the array
        projectiles.push_back(newProjectile);
    }
};

#endif // USER_H