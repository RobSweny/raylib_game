// https://en.wikipedia.org/wiki/Include_guard
#ifndef HEALTH_H
#define HEALTH_H

struct Health
{
    int maxHealth;
    int currentHealth;

    void LoseHealth()
    {
        if (currentHealth == 1)
        {
            // Game Over
        } else {
            currentHealth--;
        }
    }

    void GainHealth()
    {
        if (currentHealth != maxHealth)
        {
            currentHealth++;
        }
    }
};
#endif // HEALTH