#ifndef Level_h
#define Level_h

#include "../Helpers/Keyboard.h"
#include "../Configs.h"
#include <vector>

class Background;
class Player;
class Tile;
class GameObject;
class Keyboard;
class Enemy;


// Класс, отвечающий за логику игрового уровня.
class Level
{
    public:
        // Фон текущего уровня.
        static Background *bg;
        // Игрок.
        static Player *player;
        // Тайлы.
        static vector<Tile*> tiles; 
        // Массив монет.
        static vector<Tile*> coins;
        // Массив врагов.
        static vector<Enemy*> enemies;
        static vector<Tile*> enemy_stoppers;
        // Массив объектов, с которыми игрок сталкивается.
        static vector<GameObject*> collidable_objects;
        // Массив объектов, которые будут передвигаться при движении игрока.
        static vector<SDL_Rect*> movable_objects;
        // Переменная, задающая условия для перемещения объектов.
        static bool do_move_objects;
        // Класс, для взаимодействия с клавиатурой.
        static Keyboard kb;
    public:
        Level();
        ~Level();
        // Коллизии.
        void HorizontalCollisions();
        void VerticalCollisions();
        // Сбор монет.
        void GetCoins();
        // Запуск уровня.
        void Run();
        // Обновление всех объектов на уровне.
        void Update();
        // Передвижение объектов.
        void MoveObjects();
        // Изменение движения врагов.
        void TurnEnemiesDirection();
        // Получение игроком урона.
        void GetDamage();
    private:
        // Скорость передвижения объектов.
        int objects_speed;
};

#endif