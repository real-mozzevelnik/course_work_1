#include "Player.h"
#include "../../Game/Level.h"

Player::Player(const char *texturesheet, int x, int y) : Entity(texturesheet, x, y)
{
    // Задаем скорость.
    speed = PLAYER_SPEED;
    // Задаем начальное направляение игрока.
    facing = RIGHT;
    // Задаем скорость анимации.
    animation_speed = 0.2;
    // Задаем кол-во спрайтов для анимации персонажа.
    frames_num = 6;
}

Player::~Player()
{
    cout << "Player destructor" << endl;
}


// Передивжение игрока.
void Player::Move()
{
    HandleInput();
}


// Считывание нажатий клавиш для взаимодействия с персонажем.
void Player::HandleInput()
{
    // Если действие - нажатие клавиши.
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        // Если клавиша "a" - персонаж идет влево.
        case SDLK_a:
            // Разрешаем двигать объекты.
            Level::do_move_objects = true;
            // Игрок смотрит налево.
            facing = LEFT;
            // Двигаем игрока.
            xpos -= speed;
            break;
        
        // Если клавиша "d" - персонаж идет вправо.
        case SDLK_d:
            // Разрешаем двигать объекты.
            Level::do_move_objects = true;
            // Игрок смотрит направо.
            facing = RIGHT;
            // Двигаем игрока.
            xpos += speed;
            break;

        default:
            break;
        }
    }
    // Если действие - отпуск клавиши.
    else if (Game::event.type == SDL_KEYUP)
    {
        // Запрещаем двигать объекты.
        Level::do_move_objects = false;
    }
}


// Обновление игрока.
void Player::Update()
{
    // Двигаем игрока.
    Move();
    // Задаем координаты для прорисовки.
    destRect.x = xpos;
    destRect.y = ypos;
    // Отправляем в рендерер.
    SDL_RenderCopy(Game::renderer, objTexture, &animation_frames[0], &destRect);
}