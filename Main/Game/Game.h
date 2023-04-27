#ifndef Game_h
#define Game_h

#include "../Configs.h"

// Объявляем класс Level, чтобы была возможность создать у указатель этого типа как поле класса Game.
class Level;

// Класс, отвечающий за основной игровой цикл.
class Game
{
    public:
        // Рендерер.
        static SDL_Renderer *renderer;
        // Состояние игрового процесса.
        static string state;
        // Номер уровня.
        static int level_num;
        // Поле для считывания событий.
        static SDL_Event event;
        // Указатель на уровень.
        Level *level;

    public:
        // Конструктор, в который передаются основные характеристики игрового окна.
        Game(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen);
        ~Game();

        // Обновление объектов на экране.
        void Update();
        // Обрабатываем события (действия пользователя).
        void HandleEvents();
        // В зависимости от текущего состояния игры выполняем дейтсвия.
        void CheckState();
        // Запуск игры.
        void Run();

    private:
        // Дескриптор окна.
        SDL_Window *window;
        // Переменная, отвечающая за игровой цикл.
        bool isRunning;
};

#endif