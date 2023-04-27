#ifndef GameObject_hpp
#define GameObject_hpp

#include "../../Helpers/TextureManager.h"


// Абстрактный класс, описывающий игровой объект.
class GameObject
{
    public:
        // Конструктор, принимает путь к файлу с изображением объекта, начальные координаты.
        GameObject(const char *texturesheet, int x, int y);
        // Вирутальный деструктор, дабы вызывались деструкторы наследников.
        virtual ~GameObject() {};

        // Обновление объекта.
        virtual void Update();


    public:
        // Координаты.
        int xpos;
        int ypos;

        // Текстура объекта.
        SDL_Texture *objTexture;
        // Область текстуры, с которой берется отображаемое изображение объекта.
        SDL_Rect srcRect;
        // Облать окна, на которой прорисовывается объект.
        SDL_Rect destRect;

};

#endif