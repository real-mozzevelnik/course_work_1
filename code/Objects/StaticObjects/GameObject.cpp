#include "GameObject.h"


// Конструктор.
GameObject::GameObject(const char *texturesheet, int x, int y)
{
    if (texturesheet)
        // Загружаем текстуру.
        objTexture = TextureManager::LaodTexture(texturesheet);

    // Задаем координаты.
    destRect.x =  xpos = x;
    destRect.y =  ypos = y;
}


// Обновление объекта.
void GameObject::Update()
{
    xpos = destRect.x;
    ypos = destRect.y;
    // Добавляем объект в буфер рендерера.
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}