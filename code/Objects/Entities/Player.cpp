#include "Player.h"
#include "../../Game/Level.h"

Player::Player(const char *texturesheet, int x, int y) : Entity(texturesheet, x, y)
{
    directionX = directionY = 0;
    JumpSpeed = -10;
    GravitySpeed = 0.2;
    Yspeed = 0;
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


// // Считывание нажатий клавиш для взаимодействия с персонажем.
// void Player::HandleInput()
// {
//     // Если действие - нажатие клавиши.
//     if (Game::event.type == SDL_KEYDOWN || inAir)
//     {
//         switch (Game::event.key.keysym.sym)
//         {
//         // Если клавиша "a" - персонаж идет влево.
//         case SDLK_a:
//             // Разрешаем двигать объекты.
//             Level::do_move_objects = true;
//             // Игрок смотрит налево.
//             facing = LEFT;
//             directionX = -PLAYER_SPEED;
//             break;
        
//         // Если клавиша "d" - персонаж идет вправо.
//         case SDLK_d:
//             // Разрешаем двигать объекты.
//             Level::do_move_objects = true;
//             // Игрок смотрит направо.
//             facing = RIGHT;
//             directionX = PLAYER_SPEED;
//             break;

//         case SDLK_SPACE:
//             Jump();
//             directionY = -1;
//             inAir = true;
//             break;

//         default:
//             break;
//         }
//     }
//     // Если действие - отпуск клавиши.
//     if (Game::event.type == SDL_KEYUP)
//     {
//         directionX = 0;
//         Level::do_move_objects = false;
//     }
// }

// Считывание нажатий клавиш для взаимодействия с персонажем.
void Player::HandleInput()
{
    // Если клавиша "a" - персонаж идет влево.
    if (Level::kb.keystate[SDLK_a])
    {
        // Разрешаем двигать объекты.
        Level::do_move_objects = true;
        // Игрок смотрит налево.
        facing = LEFT;
        directionX = -PLAYER_SPEED;
    }
        
    // Если клавиша "d" - персонаж идет вправо.
    if (Level::kb.keystate[SDLK_d])
    {
        // Разрешаем двигать объекты.
        Level::do_move_objects = true;
        // Игрок смотрит направо.
        facing = RIGHT;
        directionX = PLAYER_SPEED;
    }

    if (Level::kb.keystate[SDLK_SPACE])
    {
            Jump();
            directionY = -1;
            inAir = true;

    }
    // Если действие - отпуск клавиши.
    if (Game::event.type == SDL_KEYUP)
    {
        directionX = 0;
        Level::do_move_objects = false;
    }
}




void Player::Gravity()
{
    Yspeed += GravitySpeed;
    ypos += Yspeed;
    if (Yspeed > 0) directionY = 1;
}

void Player::Jump()
{
    Yspeed = JumpSpeed;
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
    SDL_RenderCopy(Game::renderer, objTexture, &animation_frames[9], &destRect);
}