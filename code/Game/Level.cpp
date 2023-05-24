#include "Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Objects/Entities/Enemy.h"
#include "../Collections/Map.h"
#include "../Collections/ParticleEffects.h"
#include "../UI/UI.h"
#include "../Objects/StaticObjects/Coin.h"

// Объявляем статические переменные.
vector<SDL_Rect*> Level::movable_objects;
bool Level::do_move_objects;
Background* Level::bg;
Player* Level::player;
vector<Tile*> Level::tiles;
vector<GameObject*> Level::collidable_objects;
vector<Coin*> Level::coins;
Keyboard Level::kb;
vector<Enemy*> Level::enemies;
vector<Tile*> Level::enemy_stoppers;
vector<ParticleEffects*> Level::particles;
UI* Level::ui;
Tile* Level::door;
int Level::coins_earned;


Level::Level()
{
    coins_earned = 0;
    Map::CreateMap();
}


Level::~Level()
{
    // Обнуляем собранные монеты.
    coins_earned = 0;

    // Удаляем все текстуры.
    Map::DestroyTextures();
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
    // Удаляем эффекты.
    for (int i = 0; i < particles.size(); i++)
        delete particles[i];

    delete ui;
    delete door;

    // Очищаем все массивы.
    movable_objects.clear();
    tiles.clear();
    collidable_objects.clear();
    coins.clear();
    enemies.clear();
    enemy_stoppers.clear();
    particles.clear();
};


void Level::HorizontalCollisions()
{
    // Перемещаем игрока.
    player->xpos += player->directionX;

    // Если игрок соприкасается с объектами - перемещаем игрока на определенное расстояние
    // от объекта.
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            // Игрок идет вправо.
            if (player->directionX > 0) 
            {
                if ((player->xpos+BASIC_ENTITY_SIZE >= i->xpos) && (player->ypos >= i->ypos) && (player->xpos+BASIC_ENTITY_SIZE <= i->xpos+TILE_SIZE))
                    { player->xpos = i->xpos-TILE_SIZE ; player->directionX = 0;}
            }
            // Игрок идет влево.
            if (player->directionX < 0)
            {   
                if ((player->xpos <= i->xpos+TILE_SIZE) && (player->ypos >= i->ypos) && (player->xpos >= i->xpos))
                    { player->xpos = i->xpos+TILE_SIZE; player->directionX = 0; }
            }
            
        }
    }
}


void Level::VerticalCollisions()
{
    // Применяем гравитацию к игроку.
    player->Gravity();

    // Если игрок соприкасается с объектами - перемещаем игрока на определенное расстояние
    // от объекта.
    for (auto& i : collidable_objects)
    {
        if (SDL_HasIntersection(&player->destRect, &i->destRect))
        {
            // Игрок движется вниз.
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
    // Обновляем силу гравитации.
    player->GravitySpeed = GRAVITY_SPEED;

    // Коллизия с верхней границей экрана.
    if (player->ypos+UPPER_BOUND < 0)
        { player->ypos = -UPPER_BOUND; player->Yspeed = 0; }
}


void Level::GetCoins()
{
    Tile* tmp_tile;

    // Если игрок соприкасается с монетой
    for (int i = 0; i < coins.size(); i++)
    {
        if (SDL_HasIntersection(&player->destRect, &coins[i]->destRect))
        {
            // Обновляем кол-во собранных монет.
            coins_earned++;
            ui->UpdateCoinsNum();
            // Запоминаем собранную монету.
            tmp_tile = coins[i];
            // Удаляем её из массива монет.
            coins.erase(coins.begin() + i);
            // Удаляем ее из массива движущихся объектов.
            for (int j = 0; j < movable_objects.size(); j++)
            {
                if (movable_objects[j] == &tmp_tile->destRect)
                    movable_objects.erase(movable_objects.begin() + j);
            }
            // Удаляем монету.
            delete tmp_tile;
        }
    }
}


void Level::TurnEnemiesDirection()
{
    // Если враг соприкасается со стоппером (объект с прозрачным спрайтом),
    // то разворачиваем врага и меняем его сторону движения.
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
    // Если игрок находится на определенном расстоянии от врагов
    for (auto& enemy : enemies)
    {
        if ((player->ypos >= enemy->ypos - ENEMY_ATTACK_RADIUS_Y) && (player->ypos <= enemy->ypos + ENEMY_ATTACK_RADIUS_Y))
        {
            if ((player->xpos >= enemy->xpos - ENEMY_ATTACK_RADIUS_X) && (player->xpos <= enemy->xpos + ENEMY_ATTACK_RADIUS_X))
            {
                if (enemy->Attack(player->xpos, player->ypos))
                {
                    // Уменьшаем хп игрока.
                    player->heal_points -= ENEMY_STRENGTH;
                    // Проигрываем анимацию аттаки.
                    ParticleEffects *p = new ParticleEffects("../graphics/particles/slash/", ENEMY_SLASH_FRAMES_NUM, player->xpos, player->ypos);
                    particles.push_back(p);
                    movable_objects.push_back(&p->destRect);
                }
            }
        }
    }

    // Если игрок провалился в пропасть - обнуляем хп.
    if (player->ypos >= Game::screen_h)
        player->heal_points = 0;

    // Если хп кончилось - отправляем игрока на экран смерти.
    if (player->heal_points <= 0)
        Game::state = DEATH;
}


void Level::GoToNextLevel()
{
    if (player->xpos >= door->xpos-TILE_SIZE)
    {
        Game::total_coins_earned += coins_earned;
        Game::state = NEXT_LEVEL;
        Game::level_num++;
    }
}


// Передвижение объектов.
void Level::MoveObjects()
{
    // Если игрок рядом с краем экрана - двигаем объекты.
    // Таким образом будет создаваться иллюзия движения игрока и камеры.
    if ((player->xpos > RIGHT_BOUND || player->xpos < LEFT_BOUND) && do_move_objects)
    {
        // Вычисляем в какую сторону двигать объекты.
        // Отбрасываем игрока на нужные координаты.
        if (player->xpos > 700) { objects_speed = PLAYER_SPEED; player->xpos = RIGHT_BOUND; }
        else if (player->xpos < 200) { objects_speed = -PLAYER_SPEED; player->xpos = LEFT_BOUND; }
        // Передвигаем объекты.
        for (int i = 0; i < movable_objects.size(); i++)
        {
            movable_objects[i]->x -= objects_speed;
        }
    }
}


void Level::Update()
{
    // Двигаем объекты.
    MoveObjects();

    // Прорисовываем фон.
    bg->Update();

    // Прорисовываем тайлы.
    for (int i = 0; i < tiles.size(); i++)
        tiles[i]->Update();

    // Прорисовываем монеты.
    for (int i = 0; i < coins.size(); i++)
        coins[i]->Update();

    // Прорисовываем стопперы для врагов.
    for (int i = 0; i < enemy_stoppers.size(); i++)
        enemy_stoppers[i]->Update();

    // Прорисовываем врагов.
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->Update();

    // Прорисовываем игрока.
    player->Update();

    // Прорисовываем эффекты.
    for (int i = 0; i < particles.size(); i++)
    {
        // Если эффект перестал обновляться
        if (!particles[i]->Update())
        {   
            // Запоминаем эффект
            ParticleEffects *p = particles[i];

            // Удаляем эффект из массива движущихся объектов.
            for (int j = 0; j < movable_objects.size(); j++)
            {
                if (movable_objects[j] == &particles[i]->destRect)
                    movable_objects.erase(movable_objects.begin() + j);
            }
            // Удаляем эффект из массива эффектов.
            particles.erase(particles.begin() + i);
            // Удаляем эффект.
            delete p;

        }
    }

    // Обновляем интерфейс.
    ui->Update();

    // Обновляем дверь на следующий уровень.
    door->Update();

    // Проверяем коллизии.
    HorizontalCollisions();
    VerticalCollisions();
    // Сбор монет.
    GetCoins();
    // Разворот и движение врагов.
    TurnEnemiesDirection();
    // Получение урона игроком.
    GetDamage();
    // Переход на следующий уровень.
    GoToNextLevel();
}


void Level::Run()
{
    // Обновляем все объекты уровня.
    Update();
}