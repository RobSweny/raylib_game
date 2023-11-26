// https://en.wikipedia.org/wiki/Include_guard
#ifndef ENEMY_H
#define ENEMY_H

struct Enemy : Health
{
    Vector2 position;
    int size;
    float speed;
    Color color;
    int currentHealth;
    int maxHealth;
    std::vector<Projectile> enemies{};

    Enemy(Vector2 position, int size, float speed, Color color, int maxHealth) 
            : position(position), size(size), speed(speed), color(color), maxHealth(maxHealth) {}

    // boolean fucntion that returns when the enemy health is less than or equal to 0
    bool TakeDamage(int damageAmount) {
        currentHealth -= damageAmount;
        return currentHealth <= 0;
    }

    // https://stackoverflow.com/questions/2625021/game-enemy-move-towards-player
    /// @brief 
    /// @param userPosition 
    void MoveTowards(Vector2 userPosition)
    {
        Vector2 direction = {
            userPosition.x - position.x,
            userPosition.y - position.y
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

    // Creating an Enemy
    void CreateEnemy()
    {
        // Create Circle
        DrawCircleV(position, size, color);
    }
};

#endif // ENEMY