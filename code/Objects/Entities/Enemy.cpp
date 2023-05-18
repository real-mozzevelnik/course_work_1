#include "Enemy.h"

Enemy::Enemy(const char* texturesheet, int x, int y) : Entity(texturesheet, x, y)
{
    facing = RIGHT;
}