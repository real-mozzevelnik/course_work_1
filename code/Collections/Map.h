#ifndef Map_h
#define Map_h

#include "../Configs.h"

// Класс для формирования карты.
class Map
{
    public:
        // Запоминаем все загруженные текстуры, чтобы удалить их после.
        static SDL_Texture* terrain_img;
        static SDL_Texture* box_img;
        static SDL_Texture* coin_img;
        static SDL_Texture* stopper_img;
        static SDL_Texture* player_img;
        static SDL_Texture* bg_img;
        static SDL_Texture* door_img;
    public:
        // Создание карты.
        static void CreateMap();
        // Удаление текстур.
        static void DestroyTextures();
};


#endif