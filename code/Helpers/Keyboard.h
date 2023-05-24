#ifndef Keyboard_h
#define Keyboard_h

#include "../Configs.h"

// Класс для парсинга клавиатуры.
class Keyboard
{
    public:
        // Массив, хранящий состояние каждой клавиши.
        char keystate[KEYS_NUM];
    public:
        Keyboard() {};
        ~Keyboard() {};
        void HandleKeyEvent(int key_code, char active);
};

#endif