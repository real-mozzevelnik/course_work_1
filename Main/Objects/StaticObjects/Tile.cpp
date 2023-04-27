#include "Tile.h"
#include "../../Game/Game.h"

Tile::Tile(const char *texturesheet, int x, int y) : GameObject(texturesheet, x, y)
{
    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;
    srcRect.x = srcRect.y = 10;

    srcRect.w = srcRect.h = TILE_SIZE;

}

