#include "Tile.h"

Tile::Tile(SDL_Texture* tex, int x, int y, SDL_Rect tex_num) : GameObject(tex, x, y)
{
    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;
    destRect.x = x;
    destRect.y = y;
    xpos = x;
    ypos = y;
    srcRect = tex_num;
}

