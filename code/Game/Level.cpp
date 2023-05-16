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
Keyboard Level::kb;

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
    player->xpos += player->directionX;
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            if (player->directionX > 0) 
            {
                if ((player->xpos+BASIC_ENTITY_SIZE > i->xpos) && (player->ypos >= i->ypos))
                    { player->xpos = i->xpos-TILE_SIZE - 2; player->directionX = 0;}
            }
            if (player->directionX < 0)
            {   
                if ((player->xpos < i->xpos+TILE_SIZE) && (player->ypos >= i->ypos))
                    { player->xpos = i->xpos+TILE_SIZE + 2; player->directionX = 0; }
            }
            
        }
    }
}

void Level::VerticalCollisions()
{
    player->Gravity();
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            if (player->directionY > 0)
            {
                if ((player->ypos <= i->ypos-1) && ((player->xpos >= i->xpos-30) && (player->xpos < i->xpos+TILE_SIZE)))
                {
                    player->inAir = false;
                    player->ypos = i->ypos-TILE_SIZE; 
                    player->Yspeed = 0; 
                    player->GravitySpeed = 0;
                }
            }
            // if (player->directionY < 0)
                // if ((player->ypos >= i->ypos+1) && ((player->xpos >= i->xpos-30) && (player->xpos < i->xpos+TILE_SIZE)))
                //     { player->ypos = i->ypos + TILE_SIZE + 2; player->Yspeed = 0; }
        }
    }
    player->GravitySpeed = 0.2;
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
    VerticalCollisions();
}


void Level::Run()
{
    // Обновляем все объекты уровня.
    Update();
}