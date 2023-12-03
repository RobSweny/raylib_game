#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

// The animation class was created from following a series of youtube tutorials, namely
// https://www.youtube.com/watch?v=weYACOm6d8Y
// https://www.youtube.com/watch?v=x3y16-cShdQ
struct Animation {
    Texture2D spriteSheet;
    Rectangle frameRec;
    int maxFrames;
    float frameTime;
    int currentFrame;
    float timer;

    // default constructor
    Animation() : spriteSheet({0}), frameRec({0}), maxFrames(0), frameTime(0), currentFrame(0), timer(0) {}

    // Constructor
    Animation(Texture2D spriteSheet, Vector2 frameSize, int maxFrames, float frameTime)
        : spriteSheet(spriteSheet),
          frameRec({ 0.0f, 0.0f, frameSize.x, frameSize.y }),
          maxFrames(maxFrames),
          frameTime(frameTime),
          currentFrame(0),
          timer(0.0f) {}

    // Update the animation based on the delta time since the last frame
    void Update(float deltaTime) {
        // Increment the timer by the elapsed time
        timer += deltaTime; 
        // Check if the frame time has elapsed
        if (timer >= frameTime) { 
            // Reset the timer
            timer = 0.0f; 
            // Move to the next frame
            currentFrame++; 
            // Check if the last frame has been reached
            if (currentFrame >= maxFrames) { 
                // Loop back to the first frame
                currentFrame = 0; 
            }
            // Update the x position of the frame rectangle
            frameRec.x = currentFrame * frameRec.width; 
        }
    }

    // Draw the current frame of the animation at a given position on the screen
    void Draw(Vector2 position, Color tint = WHITE) {
        // Draw the part of the sprite sheet defined by frameRec at the given position, with the given tint color
        DrawTextureRec(spriteSheet, frameRec, position, tint);
    }
};

#endif // ANIMATION_H