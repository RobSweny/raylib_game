// TextureManagement.h
#ifndef TEXTUREMANAGEMENT_H
#define TEXTUREMANAGEMENT_H

struct TextureManagement
{
    Texture2D heart;
    

    void LoadTextures() {
        heart = LoadTexture("Sprites/health_sprite_small.png");
    }
    
    void UnloadTextureManagement() {
        UnloadTexture(heart);
  
    }
};
#endif // TEXTUREMANAGEMENT_H