#ifndef Player_h
#define Player_h

#include "Entity.h"


// Класс, описывающий игрока.
class Player: public Entity
{
    public:
        int directionX, directionY;
        float Yspeed;
        float GravitySpeed;
        float JumpSpeed;
        bool inAir;
    public:
        // Конструктор и деструктор.
        Player(SDL_Texture* tex, int x, int y);
        ~Player();
        // Передивжение игрока.
        void Move() override;
        // Обновление игрока.
        void Update() override;
        void Gravity();
        void Jump();
        void AnimatePlayer();

    private:
        // Считывание нажатий клавиш для взаимодействия с персонажем.
        void HandleInput();
};

#endif