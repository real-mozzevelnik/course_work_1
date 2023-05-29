#ifndef Button_h
#define Button_h

#include "Text.h"

class Button
{
    public:
        SDL_Rect destRect;
        Text* text;
        int state_to_change;
        SDL_Color button_color;
    public:
        Button(const char* button_text, SDL_Rect destRect, int state);
        ~Button();
        void Update();
};

#endif