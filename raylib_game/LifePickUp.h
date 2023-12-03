// https://en.wikipedia.org/wiki/Include_guard
#ifndef LIFEPICKUP_H
#define LIFEPICKUP_H

#include "TextureManagement.h"

struct LifePickUp
{
    int value;
    int size;
    Vector2 position;
    Texture2D heartTexture;

    // default constructor
    LifePickUp() : value(0), size(0), position({0, 0}), heartTexture({0}) {}

    void CreateLifePickUp()
    {
        DrawTexture(heartTexture, position.x, position.y, WHITE);
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