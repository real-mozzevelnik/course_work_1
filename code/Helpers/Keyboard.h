#ifndef Keyboard_h
#define Keyboard_h

#include "../Configs.h"

class Keyboard
{
    public:
        char keystate[350];
    public:
        Keyboard() {};
        ~Keyboard() {};
        void HandleKeyEvent(int key_code, char active);
};

#endif