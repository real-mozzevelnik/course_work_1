#include "Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Collections/Map.h"

// Объявляем статические переменные.
vector<SDL_Rect*> Level::movable_objects;
bool Level::do_move_objects;
Background* Level::bg;
Player* Level::player;
vector<Tile*> Level::tiles;
vector<GameObject*> Level::collidable_objects;

Level::Level()
{
    Map::CreateMap();
}


Level::~Level()
{
    // Удаляем задний фон.
    delete bg;
    // Удаляем игрока.
    delete player;
    for (int i = 0; i < tiles.size(); i++)
        delete tiles[i];
};


void Level::HorizontalCollisions()
{
    player->Gravity();
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            if (player->directionX > 0) 
            {
                    player->xpos -= 2; 
                    player->directionX = 0; 
            }
            if (player->directionX < 0)
            {
                    player->xpos += 2; 
                    player->directionX = 0; 
            }
            if (player->directionY > 0)
            {
                    player->inAir = false;
                    player->ypos -= 2; 
                    player->Yspeed = 0; 
            }
            if (player->directionY < 0)
                player->ypos = i->ypos;
        }
    }
}

void Level::VerticalCollisions()
{
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            
        }
    }
}


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
    for (int i = 0; i < tiles.size(); i++)
        tiles[i]->Update();

    player->Update();
    HorizontalCollisions();
}


void Level::Run()
{
    // Обновляем все объекты уровня.
    Update();
}