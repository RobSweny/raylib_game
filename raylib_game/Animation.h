#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

// https://www.youtube.com/watch?v=weYACOm6d8Y
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

    // Update the animation based on the delta time since the last frame.
    void Update(float deltaTime) {
        timer += deltaTime; // Increment the timer by the elapsed time.
        if (timer >= frameTime) { // Check if the frame time has elapsed.
            timer = 0.0f; // Reset the timer.
            currentFrame++; // Move to the next frame.
            if (currentFrame >= maxFrames) { // Check if the last frame has been reached.
                currentFrame = 0; // Loop back to the first frame.
            }
            frameRec.x = currentFrame * frameRec.width; // Update the x position of the frame rectangle.
        }
    }

    // Draw the current frame of the animation at a given position on the screen.
    void Draw(Vector2 position, Color tint = WHITE) {
        // Draw the part of the sprite sheet defined by frameRec at the given position, with the given tint color.
        DrawTextureRec(spriteSheet, frameRec, position, tint);
    }
};

#endif // ANIMATION_H