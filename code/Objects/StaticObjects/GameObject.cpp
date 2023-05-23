#include "GameObject.h"


// Конструктор.
GameObject::GameObject(SDL_Texture* tex, int x, int y)
{
    // Загружаем текстуру.
    objTexture = tex;

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