// https://en.wikipedia.org/wiki/Include_guard
#ifndef LIFEPICKUP_H
#define LIFEPICKUP_H

#include "TextureManagement.h"

struct LifePickUp
{
    int value;
    int size;
    Color color;
    Vector2 position;
    Texture2D &heartTexture;

    LifePickUp(int value, int size, Color color, Vector2 position, Texture2D &heartTexture)
        : value(value), size(size), color(color), position(position), heartTexture(heartTexture) {}

    void CreateLifePickUp()
    {
        DrawTexture(heartTexture, position.x, position.y, color);
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