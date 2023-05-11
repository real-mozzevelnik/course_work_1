#ifndef Entity_h
#define Entity_h

#include "../StaticObjects/GameObject.h"
#include <vector>


// Абстрактный класс, описывающий живые сущности в игре. 
class Entity: public GameObject
{
    public:
        // Скорость передвижения.
        int speed;
        // Скорость анимации.
        double animation_speed;
        // Области текстуры, с которых берутся кадры для анимации.
        vector<SDL_Rect> animation_frames;
        // Кол-во кадров в анимации.
        int frames_num;
        // Направление взгляда.
        int facing;
    public:
        // Конструктор.
        Entity(const char *texturesheet, int x, int y);
        virtual ~Entity() {};
        // Передвижение юнита.
        virtual void Move() = 0;
        // Выгрузка в вектор областей для анимаций.
        void LoadAnimationRects();
};

#endif