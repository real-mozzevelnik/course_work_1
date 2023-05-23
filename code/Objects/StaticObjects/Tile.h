#ifndef Tile_h
#define Tile_h

#include "GameObject.h"

class Tile: public GameObject
{
    public:
        Tile(SDL_Texture* tex, int x, int y, SDL_Rect tex_num);
        ~Tile() {};
};

#endif