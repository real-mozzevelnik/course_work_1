#ifndef Coin_h
#define Coin_h

#include "Tile.h"

class Coin : public Tile
{
    public:
        vector<SDL_Texture*> animation_textures;
        double animation_frame_num;
    public:
        Coin(SDL_Texture* tex, int x, int y);
        ~Coin();
        void Update() override;
};

#endif