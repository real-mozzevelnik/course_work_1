#ifndef Enemy_h
#define Enemy_h

#include "Entity.h"

class Enemy: public Entity
{
    public:
        vector<SDL_Texture*> animation_textures;
        int attack_cooldown;
    public:
        Enemy(vector<SDL_Texture*> animations, int x, int y);
        ~Enemy();
        void Animate();
        void Update() override;
        void Move() override;
        bool Attack(int x, int y);
    private:
        int prev_attack_time;
};

#endif