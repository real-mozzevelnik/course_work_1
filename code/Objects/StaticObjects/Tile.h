#ifndef Tile_h
#define Tile_h

#include "GameObject.h"

class Tile: public GameObject
{
    public:
        Tile(const char *texturesheet, int x, int y);
        ~Tile() {};
};

#endif