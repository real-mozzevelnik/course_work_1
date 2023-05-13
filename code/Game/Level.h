#ifndef Level_h
#define Level_h

#include "../Configs.h"
#include <vector>

class Background;
class Player;
class Tile;
class GameObject;


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
        static vector<GameObject*> collidable_objects;
        // Массив объектов, которые будут передвигаться при движении игрока.
        static vector<SDL_Rect*> movable_objects;
        // Переменная, задающая условия для перемещения объектов.
        static bool do_move_objects;
    public:
        Level();
        ~Level();
        void HorizontalCollisions();
        void VerticalCollisions();
        // Запуск уровня.
        void Run();
        // Обновление всех объектов на уровне.
        void Update();
        // Передвижение объектов.
        void MoveObjects();
    private:
        // Скорость передвижения объектов.
        int objects_speed;
};

#endif