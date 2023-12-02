// TextureManagement.h
#ifndef TEXTUREMANAGEMENT_H
#define TEXTUREMANAGEMENT_H

#include "Animation.h"

struct TextureManagement
{   
    Texture2D menu;
    Texture2D background;
    Texture2D heart;
    Texture2D player;
    Texture2D playerIdle;
    Texture2D playerRunning;
    Texture2D easyEnemySpriteSheet;
    Texture2D mediumEnemySpriteSheet;
    Texture2D hardEnemySpriteSheet;
    Texture2D speedyEnemySpriteSheet;
    Animation easyEnemyAnimation;
    Animation mediumEnemyAnimation;
    Animation hardEnemyAnimation;
    Animation speedyEnemyAnimation;
    Animation playerIdleAnimation;
    Animation playerRunningAnimation;

    void Initialize() {
        LoadTextures();
        easyEnemyAnimation = Animation(easyEnemySpriteSheet, {40, 40}, 7, 1.0f / 12.0f);
        mediumEnemyAnimation = Animation(mediumEnemySpriteSheet, {45, 45}, 7, 1.0f / 12.0f);
        hardEnemyAnimation = Animation(hardEnemySpriteSheet, {50, 50}, 7, 1.0f / 12.0f);
        speedyEnemyAnimation = Animation(speedyEnemySpriteSheet, {30, 30}, 7, 1.0f / 12.0f);
        playerIdleAnimation = Animation(playerIdle, {40, 40}, 7, 1.0f / 12.0f);
        playerRunningAnimation = Animation(playerRunning, {60, 60}, 7, 1.0f / 12.0f);
    }

    void LoadTextures() {
        menu = LoadTexture("Sprites/menu.png");
        player = LoadTexture("Sprites/Player.png");
        heart = LoadTexture("Sprites/health_sprite_small.png");
        background = LoadTexture("Sprites/background.png");
        playerIdle = LoadTexture("Sprites/Player_idle.png");
        playerRunning = LoadTexture("Sprites/Player_run.png");
        easyEnemySpriteSheet = LoadTexture("Sprites/Easy_Enemy.png");           
        mediumEnemySpriteSheet = LoadTexture("Sprites/Medium_Enemy.png");
        hardEnemySpriteSheet = LoadTexture("Sprites/Hard_Enemy.png");
        speedyEnemySpriteSheet = LoadTexture("Sprites/Speedy_Enemy.png");
    }

    void UnloadTextureManagement() {
        UnloadTexture(menu);
        UnloadTexture(player);
        UnloadTexture(playerIdle);
        UnloadTexture(playerRunning);
        UnloadTexture(heart);
        UnloadTexture(background);
        UnloadTexture(easyEnemySpriteSheet);
        UnloadTexture(mediumEnemySpriteSheet);
        UnloadTexture(hardEnemySpriteSheet);
        UnloadTexture(speedyEnemySpriteSheet); 
    }
};
#endif // TEXTUREMANAGEMENT_H