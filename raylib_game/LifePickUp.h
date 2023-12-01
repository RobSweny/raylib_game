// https://en.wikipedia.org/wiki/Include_guard
#ifndef LIFEPICKUP_H
#define LIFEPICKUP_H

#include "TextureManagement.h"

struct LifePickUp
{
    int value;
    int size;
    Vector2 position;
    Texture2D &heartTexture;

    LifePickUp(int value, int size, Vector2 position, Texture2D &heartTexture)
        : value(value), size(size), position(position), heartTexture(heartTexture) {}

    void CreateLifePickUp(Vector2 position)
    {
        DrawTexture(heartTexture, position.x, position.y, RED);
    }
    
    // When a life is picked up, set the size to 0 and play a pick up life sound.
    // This should give the appearance that the life disappeared.
    void LifePickedUp(SoundManagement soundManagement)
    {
        size = 0;
        soundManagement.PlayLifePickUpSound();
    }
};
#endif // LIFEPICKUP