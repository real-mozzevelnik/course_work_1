#ifndef Enemy_h
#define Enemy_h

#include "Entity.h"

class Enemy: public Entity
{
    public:
        vector<SDL_Texture*> animation_textures;
    public:
        Enemy(vector<SDL_Texture*> animations, int x, int y);
        ~Enemy();
        void Animate();
        void Update() override;
        void Move() override;
};

#endif