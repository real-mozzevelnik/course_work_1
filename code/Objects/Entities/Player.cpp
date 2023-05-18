#include "Player.h"
#include "../../Game/Level.h"

Player::Player(const char *texturesheet, int x, int y) : Entity(texturesheet, x, y)
{
    flip = SDL_FLIP_NONE;
    directionX = directionY = 0;
    JumpSpeed = -10;
    GravitySpeed = 0.2;
    Yspeed = 0;
    animation_frame_num = 0;
    // Задаем скорость.
    speed = PLAYER_SPEED;
    // Задаем начальное направляение игрока.
    facing = RIGHT;
    // Задаем скорость анимации.
    animation_speed = 0.2;
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


void Player::AnimatePlayer()
{
    float left_border, right_border;
    animation_frame_num += ANIMATION_SPEED;
    if (inAir)
    {
        left_border = 20;
        right_border = 20;
    }
    else if ((directionX == 0) && (Yspeed < 2) && (Yspeed > -2))
    {
        left_border = 9;
        right_border = 17;
    }
    else if ((directionX != 0) && (Yspeed < 2) && (Yspeed > -2))
    {
        left_border = 72;
        right_border = 78;
    }
    else
    {
        left_border = 20;
        right_border = 20;
    }

    if (facing == RIGHT)
        flip = SDL_FLIP_NONE;
    if (facing == LEFT)
        flip = SDL_FLIP_HORIZONTAL;

    if (animation_frame_num < left_border)
        animation_frame_num = left_border;
    if (animation_frame_num >= right_border)
        animation_frame_num = left_border;
}


// Обновление игрока.
void Player::Update()
{
    // Двигаем игрока.
    Move();
    // Задаем координаты для прорисовки.
    destRect.x = xpos;
    destRect.y = ypos;
    AnimatePlayer();
    // Отправляем в рендерер.
    SDL_RenderCopyEx(Game::renderer, objTexture, &animation_frames[int(animation_frame_num)], &destRect, 0, NULL, flip);
}