#include "Enemy.h"

Enemy::Enemy(vector<SDL_Texture*> animations, int x, int y) : Entity(nullptr, x, y)
{
    facing = RIGHT;
    speed = ENEMY_SPEED;
    animation_textures = animations;
    animation_speed = ANIMATION_SPEED;
    animation_frame_num = 0;
    srcRect = {0, 0, BASIC_SIZE, BASIC_SIZE};
    destRect.w = destRect.h = BASIC_ENTITY_SIZE;
    attack_cooldown = 2000;
    prev_attack_time = 0;
}


Enemy::~Enemy()
{
    cout << "enemy dest" << endl;
}


void Enemy::Move()
{
    destRect.x += speed;
}


void Enemy::Animate()
{
    animation_frame_num += animation_speed;
    if (animation_frame_num > animation_textures.size() - 1)
        animation_frame_num = 0;

    if (facing == RIGHT)
        flip = SDL_FLIP_NONE;
    else if (facing == LEFT)
        flip = SDL_FLIP_HORIZONTAL;
}


bool Enemy::Attack(int x, int y)
{
    if (SDL_GetTicks() - prev_attack_time > attack_cooldown)
    {
        prev_attack_time = SDL_GetTicks();
        return true;
    }

    return false;
}


void Enemy::Update()
{
    // Задаем координаты для прорисовки.
    xpos = destRect.x;
    ypos = destRect.y;
    Move();
    Animate();
    // Отправляем в рендерер.
    SDL_RenderCopyEx(Game::renderer, animation_textures[static_cast<int>(animation_frame_num)], &srcRect, &destRect, 0, NULL, flip);
}