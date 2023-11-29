// https://en.wikipedia.org/wiki/Include_guard
#ifndef LIFEPICKUP_H
#define LIFEPICKUP_H

struct LifePickUp
{
    int value = 1;
    int size = 5;
    Vector2 position;

    void CreateLife()
    {
        DrawCircleV(GenerateRandomHealthPosition(), size, RED);
    }
    
    void LifePickedUp(SoundManagement soundManagement)
    {
        size = 0;
        soundManagement.PlayLifePickUpSound();
    }

    Vector2 GenerateRandomHealthPosition()
    {
        Vector2 position;
        position.x = GetRandomValue(0, GetScreenWidth());
        position.y = GetRandomValue(0, GetScreenHeight());
        return position; 
    }
};
#endif // LIFEPICKUP