#ifndef ParticleEffects_h
#define ParticleEffects_h

#include "../Objects/StaticObjects/GameObject.h"

class ParticleEffects
{
    public:
        int xpos, ypos;
        SDL_Rect destRect, srcRect;
        vector<SDL_Texture*> textures;
        double animation_frame_num;
    public:
        ParticleEffects(const char* textures_path, int text_num, int x, int y);
        ~ParticleEffects();

        bool Update();

};

#endif