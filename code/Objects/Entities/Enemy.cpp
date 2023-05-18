#include "Enemy.h"

Enemy::Enemy(const char* texturesheet = "", vector<SDL_Texture*> animations, int x, int y) : Entity(texturesheet, x, y)
{
    facing = RIGHT;
    animation_textures = animations;
}