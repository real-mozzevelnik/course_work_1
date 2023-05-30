#ifndef Pause_h
#define Pause_h

#include "Screen.h"
#include <map>
#include "../Button.h"

class Pause : public Screen
{
    public:
        SDL_Texture* bg_tex;
        SDL_Rect bg_destRect;
        map<int, Button*> buttons;
    public:
        Pause();
        ~Pause();
        void Update() override;
        void PushButtons();
};

#endif