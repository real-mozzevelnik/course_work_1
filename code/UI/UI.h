#ifndef UI_h
#define UI_h

#include "../Game/Game.h"

class UI
{
    public:
        SDL_Texture *health_bar;
        SDL_Rect health_bar_srcRect, health_bar_destRect;
        SDL_Rect health_destRect;
    public:
        UI();
        ~UI();
        void Update();
};

#endif