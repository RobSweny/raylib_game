// https://en.wikipedia.org/wiki/Include_guard
#ifndef PROJECTILE_H
#define PROJECTILE_H

struct Projectile
{
    Vector2 position;
    Vector2 direction;
    float speed;
    Color color;
    int damage;
    int size;

    Projectile(Vector2 position, Vector2 direction, float speed, Color color, int damage, int size)
        : position(position), direction(direction), speed(speed), color(color), damage(damage), size(size) {}

    void Draw() const {
        DrawCircleV(position, 5, color);
    }
};

#endif // PROJECTILE_H