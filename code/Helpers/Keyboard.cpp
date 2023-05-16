#include "Keyboard.h"

void Keyboard::HandleKeyEvent(int key_code, char active)
{
    keystate[key_code] = active;
}

