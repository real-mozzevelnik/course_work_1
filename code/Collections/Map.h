#ifndef Map_h
#define Map_h

#include <vector>

#include "../Objects/StaticObjects/Tile.h"

class Map
{
    public:
        vector<Tile *> tiles;
        vector<char> tiles_csv;

    public:
        Map();
        ~Map() {};
};


#endif