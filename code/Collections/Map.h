#ifndef Map_h
#define Map_h

#include "../Configs.h"

class Map
{
    public:
        static SDL_Texture* terrain_img;
        static SDL_Texture* box_img;
        static SDL_Texture* coin_img;
        static SDL_Texture* stopper_img;
        static SDL_Texture* player_img;
        static SDL_Texture* bg_img;
    public:
        static void CreateMap();
        static void DestroyTextures();
};


#endif