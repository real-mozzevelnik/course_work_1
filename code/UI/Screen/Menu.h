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
        Text *enter_name_text;
        Text *name;
        string name_input_str;
        SDL_Rect name_rect;
    public:
        Menu();
        ~Menu();
        void Update() override;
    private:
        void EnterName();
        void CheckMenuState();
        void PushButtons();
};

#endif