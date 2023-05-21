#include "ParticleEffects.h"

ParticleEffects::ParticleEffects(const char* textures_path, int text_num, int x, int y)
{
    textures = TextureManager::LoadAnimationTextures(textures_path, text_num);
    srcRect.x = srcRect.y = 0;
    destRect.x = xpos = x;
    destRect.y = ypos = y;
    destRect.w = destRect.h = srcRect.w = srcRect.h = TILE_SIZE;

    animation_frame_num = 0;
}


ParticleEffects::~ParticleEffects() 
{
    TextureManager::DestroyAnimationTextures(textures);
}


bool ParticleEffects::Update()
{
    animation_frame_num += ANIMATION_SPEED;
    if (animation_frame_num <= textures.size())
    {
        SDL_RenderCopy(Game::renderer, textures[static_cast<int>(animation_frame_num)], &srcRect, &destRect);
        return true;
    }
    return false;
}