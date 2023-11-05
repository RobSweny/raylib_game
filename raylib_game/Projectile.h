// https://en.wikipedia.org/wiki/Include_guard
#ifndef PROJECTILE_H
#define PROJECTILE_H

struct Projectile
{
    Vector2 position;
    Vector2 direction;
    float speed;
    Color color;

    void CreateProjectile(Vector2 position, float speed, Color color)
    {
        // Draw projectile
        DrawCircleV(position, speed, color);
    }

};

#endif // PROJECTILE_H