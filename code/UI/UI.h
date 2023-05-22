#ifndef UI_h
#define UI_h

#include "../Game/Game.h"
#include "Text.h"

class UI
{
    public:
        SDL_Texture *health_bar;
        SDL_Rect health_bar_srcRect, health_bar_destRect;
        SDL_Rect health_destRect;
        Text* coins_num;
        SDL_Texture* coin;
        SDL_Rect coin_destRect, coin_srcRect;
    public:
        UI();
        ~UI();
        void Update();
        void UpdateCoinsNum();
};

#endif