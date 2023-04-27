#include "Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/StaticObjects/Tile.h"

// Объявляем статические переменные.
vector<SDL_Rect*> Level::movable_objects;
bool Level::do_move_objects;

Level::Level()
{
    // Загружаем задний фон.
    bg = new Background("../graphics/background/level1.png", 0, 0);
    // Создаем игрока.
    player = new Player("../graphics/units/player/walk.png", 200, 20);

}


Level::~Level()
{
    // Удаляем задний фон.
    delete bg;
    // Удаляем игрока.
    delete player;
};


// Передвижение объектов.
void Level::MoveObjects()
{
    // Если игрок рядом с краем экрана - двигаем объекты.
    // Таким образом будет создаваться иллюзия движения игрока и камеры.
    if ((player->xpos > 700 || player->xpos < 200) && do_move_objects)
    {
        // Вычисляем в какую сторону двигать объекты.
        // Отбрасываем игрока на нужные координаты.
        if (player->xpos > 700) { objects_speed = PLAYER_SPEED; player->xpos = 700; }
        else if (player->xpos < 200) { objects_speed = -PLAYER_SPEED; player->xpos = 200; }
        // Передвигаем объекты.
        for (int i = 0; i < movable_objects.size(); i++)
        {
            movable_objects[i]->x -= objects_speed;
        }
    }
}


void Level::Update()
{
    MoveObjects();
    // Прорисовываем фон.
    bg->Update();
    player->Update();
}


void Level::Run()
{
    // Обновляем все объекты уровня.
    Update();
}