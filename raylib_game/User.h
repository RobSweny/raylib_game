// https://en.wikipedia.org/wiki/Include_guard
#ifndef USER_H
#define USER_H

#include <math.h>
#include <vector>
#include "raylib.h"
#include "SoundManagement.h"
#include "Projectile.h"
#include "Health.h"

struct User : Health
{
    int size;
    Vector2 position;
    float speed;
    int maxHealth;
    int projectileSize;
    bool isOnHealthCooldown = false;
    // 2 second timer from being hit
    float cooldownTime = 2.0f;
    float lastHitTime;
    // Array of struct Projectile
    std::vector<Projectile> projectiles{};
    // Include reference to sound management
    SoundManagement& soundManagement;

    User(int size, Vector2 position, float speed, int maxHealth, SoundManagement& soundManagement) 
            : Health { maxHealth, maxHealth },
            size(size), position(position), speed(speed),
            soundManagement(soundManagement) {
            }

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

    // Update cooldown time, this is called when the user has been hit
    // it is to avoid the collision between enemy and user being called too often
    void UpdateCooldown() {
        // check if the bool flag is true
        if (isOnHealthCooldown) {
            // get the current time and minus it from the last time the user was hit, check if this is greater than the cooldown time (2 seconds)
            if (GetTime() - lastHitTime >= cooldownTime) {
                // if the time is greater than 2 seconds
                isOnHealthCooldown = false;
            }
        }
    }

    // We have to override LoseHealth from the 'Health' class
    void LoseHealth() {
        // if not on health cooldown and the user health is greater than 0
        if (!isOnHealthCooldown && currentHealth > 0) {
            // minus the health
            currentHealth--;
            // update last hit time to current time
            lastHitTime = GetTime();
            // set cooldown to true
            isOnHealthCooldown = true;
        }
    }

    // Creating a character
    void CreateCharacter()
    {
        // Create Circle
        DrawCircleV(position, size, MAROON);
    }

    // function to shoot a projectile
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
        
        soundManagement.PlayShootSound();

        Projectile newProjectile = { position, direction, 1.0f, RED, 1, projectileSize };
        // Push new projectile to the back of the array
        projectiles.push_back(newProjectile);
    }
};

#endif // USER_H