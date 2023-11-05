// https://en.wikipedia.org/wiki/Include_guard
#ifndef ENEMY_H
#define ENEMY_H

struct Enemy
{
    Vector2 position;
    int size;
    float speed;
    Color color;

    // Creating an Enemy
    void CreateEnemy()
    {
        // Create Circle
        DrawCircleV(position, size, color);
    }
};

#endif // ENEMY