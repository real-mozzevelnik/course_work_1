#ifndef Screen_h
#define Screen_h

#include "../Text.h"

class Screen
{
    public:
        Text *message_text, *continue_text;
    public:
        Screen(const char* message, SDL_Color text_color, SDL_Rect text_pos);
        ~Screen();
        void Update();

};

#endif