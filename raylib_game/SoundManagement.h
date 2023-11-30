// SoundManagement.h
#ifndef SOUNDMANAGEMENT_H
#define SOUNDMANAGEMENT_H

struct SoundManagement
{
    Sound shoot;
    Sound gameOverMusic;
    Sound gameOver;
    Sound ouch;
    Sound gameMusic;
    Sound enemyCreatedSound;
    Sound countDown;
    Sound bomb;
    Sound lifePickup;

    SoundManagement()
    {
        InitAudioDevice();
        LoadSounds();
    }

    void LoadSounds() {
        shoot = LoadSound("Sounds/laserShoot.wav");
        gameOverMusic = LoadSound("Sounds/dead_game_music.mp3");
        gameOver = LoadSound("Sounds/game_over.mp3");
        ouch = LoadSound("Sounds/ouch.wav");
        gameMusic = LoadSound("Sounds/game_music.mp3");
        enemyCreatedSound = LoadSound("Sounds/enemy_spawn.mp3");
        countDown = LoadSound("Sounds/game_countdown.mp3");
        bomb = LoadSound("Sounds/big_blast.mp3");
        lifePickup = LoadSound("Sounds/pickup.wav");
    }
    
    void PlayCountdownSound() {
        PlaySound(countDown);
    }

    void PlayEnemySpawnSound() {
        PlaySound(enemyCreatedSound);
    }

    void PlayLifePickUpSound() {
        PlaySound(lifePickup);
    }

    void PlayGameMusic() {
        PlaySound(gameMusic);
    }

    void StopGameMusic() {
        StopSound(gameMusic);
    }

    void PlayOuchSound() {
        PlaySound(ouch);
    }

    void PlayShootSound() {
        PlaySound(shoot);
    }

    void PlayBombSound() {
        PlaySound(bomb);
    }

    void GameOverSounds() {
        PlaySound(gameOver);
        PlaySound(gameOverMusic);
    }

    void UnloadSoundManagement()
    {
        UnloadSound(gameMusic);
        UnloadSound(enemyCreatedSound);
        UnloadSound(shoot);
        UnloadSound(ouch);
        UnloadSound(gameOver);
        UnloadSound(gameOverMusic);
        UnloadSound(countDown);
        UnloadSound(bomb);
        UnloadSound(lifePickup);
         // Close audio device
        CloseAudioDevice();
    }
};
#endif // SOUNDMANAGEMENT