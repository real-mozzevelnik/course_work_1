#ifndef ParticleEffects_h
#define ParticleEffects_h

#include "../Objects/StaticObjects/GameObject.h"

// Класс для отображения визуальных эффектов.
class ParticleEffects
{
    public:
        // Координаты.
        int xpos, ypos;
        SDL_Rect destRect, srcRect;
        // Массив текстур для анимации.
        vector<SDL_Texture*> textures;
        // Номер текущего кадра.
        double animation_frame_num;
    public:
        ParticleEffects(const char* textures_path, int text_num, int x, int y);
        ~ParticleEffects();

        bool Update();

};

#endif