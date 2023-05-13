#include "Tile.h"
#include "../../Game/Level.h"

Tile::Tile(const char *texturesheet, int x, int y, SDL_Rect tex_num) : GameObject(texturesheet, x, y)
{
    Level::movable_objects.push_back(&destRect);
    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;
    destRect.x = x;
    destRect.y = y;
    xpos = x;
    ypos = y;
    srcRect = tex_num;
}

