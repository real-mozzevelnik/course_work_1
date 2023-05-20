#include "Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Objects/Entities/Enemy.h"
#include "../Collections/Map.h"

// Объявляем статические переменные.
vector<SDL_Rect*> Level::movable_objects;
bool Level::do_move_objects;
Background* Level::bg;
Player* Level::player;
vector<Tile*> Level::tiles;
vector<GameObject*> Level::collidable_objects;
vector<Tile*> Level::coins;
Keyboard Level::kb;
vector<Enemy*> Level::enemies;
vector<Tile*> Level::enemy_stoppers;


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
    // Удаляем тайлы.
    for (int i = 0; i < tiles.size(); i++)
        delete tiles[i];
    // Удаляем монеты.
    for (int i = 0; i < coins.size(); i++)
        delete coins[i];
    // Удаляем врагов.
    for (int i = 0; i < enemies.size(); i++)
        delete enemies[i];
    // Удаляем стопперы.
    for (int i = 0; i < enemy_stoppers.size(); i++)
        delete enemy_stoppers[i];
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

    if (player->ypos < 0)
        { player->ypos = 0; player->Yspeed = 0; }
}


void Level::GetCoins()
{
    Tile* tmp_tile;
    for (int i = 0; i < coins.size(); i++)
    {
        if (SDL_HasIntersection(&player->destRect, &coins[i]->destRect))
        {
            tmp_tile = coins[i];
            coins.erase(coins.begin() + i);
            for (int j = 0; j < movable_objects.size(); j++)
            {
                if (movable_objects[j] == &tmp_tile->destRect)
                    movable_objects.erase(movable_objects.begin() + j);
            }
            delete tmp_tile;
        }
    }
}


void Level::TurnEnemiesDirection()
{
    for (auto& enemy : enemies)
    {
        for (auto& stopper : enemy_stoppers)
        {
            if (SDL_HasIntersection(&enemy->destRect, &stopper->destRect))
            {
                enemy->facing = !enemy->facing;
                enemy->speed = -enemy->speed;
            }
        }
    }
}


void Level::GetDamage()
{
    for (auto& enemy : enemies)
    {
        if ((player->ypos >= enemy->ypos - 50) && (player->ypos <= enemy->ypos + 50))
        {
            if ((player->xpos >= enemy->xpos - 150) && (player->xpos <= enemy->xpos + 150))
            {
                if (enemy->Attack(player->xpos, player->ypos))
                    player->heal_points -= 30;
            }
        }
    }
    cout << player->heal_points << endl;
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

    for (int i = 0; i < coins.size(); i++)
        coins[i]->Update();

    for (int i = 0; i < enemy_stoppers.size(); i++)
        enemy_stoppers[i]->Update();

    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->Update();

    player->Update();
    HorizontalCollisions();
    VerticalCollisions();
    GetCoins();
    TurnEnemiesDirection();
    GetDamage();
}


void Level::Run()
{
    // Обновляем все объекты уровня.
    Update();
}