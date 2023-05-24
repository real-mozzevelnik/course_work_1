#include "Keyboard.h"

void Keyboard::HandleKeyEvent(int key_code, char active)
{
    // Изменяем состояние клавиши.
    keystate[key_code] = active;
}

