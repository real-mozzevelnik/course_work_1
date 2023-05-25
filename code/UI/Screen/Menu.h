#ifndef Menu_h
#define Menu_h

#include "Screen.h"


class Menu : public Screen
{
    public:
        SDL_Texture* bg_tex;
        SDL_Rect bg_destRect;
    public:
        Menu();
        ~Menu();
        void Update() override;
};

#endif