#include "ParticleEffects.h"

ParticleEffects::ParticleEffects(const char* textures_path, int text_num, int x, int y)
{
    // Загружаем кадры для анимации.
    textures = TextureManager::LoadAnimationTextures(textures_path, text_num);

    // Формируем области отображения.
    srcRect.x = srcRect.y = 0;
    destRect.x = xpos = x;
    destRect.y = ypos = y;
    destRect.w = destRect.h = srcRect.w = srcRect.h = TILE_SIZE;

    animation_frame_num = 0;
}


ParticleEffects::~ParticleEffects() 
{
    // Удаляем текстуры.
    TextureManager::DestroyAnimationTextures(textures);
}


bool ParticleEffects::Update()
{
    // Увеличиваем номер кадра.
    animation_frame_num += ANIMATION_SPEED;
    // Если кадры еще не закончились - продолжаем прогружать эффект.
    if (animation_frame_num <= textures.size())
    {
        SDL_RenderCopy(Game::renderer, textures[static_cast<int>(animation_frame_num)], &srcRect, &destRect);
        return true;
    }
    // Иначе сигнализируем о конце отображения эффекта.
    return false;
}