#include "Entity.h"

// Конструктор.
Entity::Entity(SDL_Texture* tex, int x, int y) : GameObject(tex, x, y)
{
    // Задаем размеры объекта.
    destRect.w = srcRect.w = BASIC_ENTITY_SIZE;
    destRect.h = srcRect.h = BASIC_ENTITY_SIZE;
    // Нарезаем текстуру на спрайты для анимации.
    LoadAnimationRects();
}


void Entity::LoadAnimationRects()
{
    animation_frames = TextureManager::CutGraphics(objTexture, BASIC_ENTITY_SIZE);
}