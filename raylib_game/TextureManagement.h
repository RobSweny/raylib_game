// TextureManagement.h
#ifndef TEXTUREMANAGEMENT_H
#define TEXTUREMANAGEMENT_H

struct TextureManagement
{
    Texture2D heart;
    Texture2D background;

    void LoadTextures() {
        heart = LoadTexture("Sprites/health_sprite_small.png");
        background = LoadTexture("Sprites/background.png");
    }
    
    void UnloadTextureManagement() {
        UnloadTexture(heart);
        UnloadTexture(background); 
    }
};
#endif // TEXTUREMANAGEMENT_H