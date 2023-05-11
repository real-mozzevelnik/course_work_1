#ifndef Player_h
#define Player_h

#include "Entity.h"


// Класс, описывающий игрока.
class Player: public Entity
{
    public:
        // Конструктор и деструктор.
        Player(const char *texturesheet, int x, int y);
        ~Player();
        // Передивжение игрока.
        void Move() override;
        // Обновление игрока.
        void Update() override;

    private:
        // Считывание нажатий клавиш для взаимодействия с персонажем.
        void HandleInput();
};

#endif