#ifndef Menu_h
#define Menu_h

#include "Screen.h"
#include <map>

class Button;
class Text;

class Menu : public Screen
{
    public:
        SDL_Texture* bg_tex;
        SDL_Rect bg_destRect;
        int menu_state;
        map<int , Button*> buttons;
        int prev_button_press_time;
        Text *info_text;
    public:
        Menu();
        ~Menu();
        void Update() override;
        void CheckMenuState();
        void PushButtons();
};

#endif