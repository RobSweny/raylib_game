// TextureManagement.h
#ifndef TEXTUREMANAGEMENT_H
#define TEXTUREMANAGEMENT_H

#include "Animation.h"

struct TextureManagement
{   
    Texture2D background;
    Texture2D heart;
    Texture2D player;
    Texture2D playerIdle;
    Texture2D playerRunning;
    Texture2D easyZombieSpriteSheet;
    Texture2D mediumZombieSpriteSheet;
    Texture2D hardZombieSpriteSheet;
    Texture2D speedyZombieSpriteSheet;
    Animation easyZombieAnimation;
    Animation mediumZombieAnimation;
    Animation hardZombieAnimation;
    Animation speedyZombieAnimation;
    Animation playerIdleAnimation;
    Animation playerRunningAnimation;

    void Initialize() {
        LoadTextures();
        easyZombieAnimation = Animation(easyZombieSpriteSheet, {40, 40}, 7, 1.0f / 12.0f);
        mediumZombieAnimation = Animation(mediumZombieSpriteSheet, {45, 45}, 7, 1.0f / 12.0f);
        hardZombieAnimation = Animation(hardZombieSpriteSheet, {50, 50}, 7, 1.0f / 12.0f);
        speedyZombieAnimation = Animation(speedyZombieSpriteSheet, {35, 35}, 7, 1.0f / 12.0f);
        playerIdleAnimation = Animation(playerIdle, {40, 40}, 7, 1.0f / 12.0f);
        playerRunningAnimation = Animation(playerRunning, {60, 60}, 7, 1.0f / 12.0f);
    }

    void LoadTextures() {
        player = LoadTexture("Sprites/Player.png");
        heart = LoadTexture("Sprites/health_sprite_small.png");
        background = LoadTexture("Sprites/background.png");
        playerIdle = LoadTexture("Sprites/Player_idle.png");
        playerRunning = LoadTexture("Sprites/Player_run.png");
        easyZombieSpriteSheet = LoadTexture("Sprites/Easy_Enemy.png");           
        mediumZombieSpriteSheet = LoadTexture("Sprites/Medium_Enemy.png");
        hardZombieSpriteSheet = LoadTexture("Sprites/Hard_Enemy.png");
        speedyZombieSpriteSheet = LoadTexture("Sprites/Speedy_Enemy.png");
    }

    void UnloadTextureManagement() {
        UnloadTexture(player);
        UnloadTexture(playerIdle);
        UnloadTexture(playerRunning);
        UnloadTexture(heart);
        UnloadTexture(background);
        UnloadTexture(easyZombieSpriteSheet);
        UnloadTexture(mediumZombieSpriteSheet);
        UnloadTexture(hardZombieSpriteSheet);
        UnloadTexture(speedyZombieSpriteSheet); 
    }
};
#endif // TEXTUREMANAGEMENT_H