#include "Background.h"
#include "../../Game/Level.h"


// Конструктор, также вызываем конструктор базового класса.
Background::Background(const char *texturesheet, int x, int y) : GameObject(texturesheet, x, y)
{
    // Добавляем фон в передвигаемые объекты.
    Level::movable_objects.push_back(&destRect);
    // Задаем координаты.
    srcRect.x = destRect.x = x;
    srcRect.y = destRect.y = y;

    // Узнаем размер изображения фона.
    SDL_QueryTexture(objTexture, NULL, NULL, &destRect.w, &destRect.h);
    // Задаем эти размеры для корректного изображения фона.
    srcRect.w = destRect.w;
    srcRect.h = destRect.h;

    destRect.h += TILE_SIZE;

}