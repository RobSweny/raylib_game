// https://en.wikipedia.org/wiki/Include_guard
#ifndef ENEMY_H
#define ENEMY_H

#include "Animation.h"

struct Enemy : Health
{
    Vector2 position;
    int size;
    float speed;
    Animation runAnimation;

    Enemy(Vector2 position, int size, float speed, int maxHealth, const Animation& animation) 
            : Health { maxHealth, maxHealth},
            position(position), size(size), speed(speed),
            runAnimation(animation) {}

    // Method to update the enemy's state
    void Update(float deltaTime, User user) {
        // Update the animation
        runAnimation.Update(deltaTime);
        MoveTowards(user);
    }

    // boolean function that returns when the enemy health is less than or equal to 0
    bool TakeDamage(int damageAmount) {
        currentHealth -= damageAmount;
        return currentHealth <= 0;
    }

    // https://stackoverflow.com/questions/2625021/game-enemy-move-towards-player
    /// @brief 
    /// @param user 
    void MoveTowards(User user)
    {
        Vector2 direction = {
            user.position.x - position.x,
            user.position.y - position.y
        };

        // Normalize direction
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0.0f) {
            direction.x /= length;
            direction.y /= length;
        }

        // Move enemy towards player
        position.x += direction.x * speed;
        position.y += direction.y * speed;
    }

    // Method to draw the enemy on the screen
    void CreateEnemy() {
        // Draw the run animation at the enemy's current position
        runAnimation.Draw(position);
    }
};

#endif // ENEMY