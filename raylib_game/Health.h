// https://en.wikipedia.org/wiki/Include_guard
#ifndef HEALTH_H
#define HEALTH_H

struct Health
{
    int maxHealth;
    int currentHealth;
    
    bool CheckHealth()
    {
        return currentHealth <= 0;
    }

    void LoseHealth() {
        if (currentHealth > 0) {
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