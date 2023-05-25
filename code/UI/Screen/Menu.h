#ifndef Menu_h
#define Menu_h

#include "Screen.h"
#include <map>

class Button;

class Menu : public Screen
{
    public:
        SDL_Texture* bg_tex;
        SDL_Rect bg_destRect;
        int menu_state;
        map<int , Button*> buttons;
    public:
        Menu();
        ~Menu();
        void Update() override;
        void CheckMenuState();
};

#endif