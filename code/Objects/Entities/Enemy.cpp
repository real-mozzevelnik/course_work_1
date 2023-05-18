#include "Enemy.h"

Enemy::Enemy(vector<SDL_Texture*> animations, int x, int y) : Entity(nullptr, x, y)
{
    facing = RIGHT;
    animation_textures = animations;
}

Enemy::~Enemy()
{
    cout << "enemy dest" << endl;
}

void Enemy::Move()
{

}


void Enemy::Update()
{
    // Задаем координаты для прорисовки.
    destRect.x = xpos;
    destRect.y = ypos;
    // Отправляем в рендерер.
    SDL_RenderCopyEx(Game::renderer, animation_textures[0], NULL, &destRect, 0, NULL, SDL_FLIP_NONE);
}