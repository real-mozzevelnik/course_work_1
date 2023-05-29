#ifndef Text_h
#define Text_h

#include "../Game/Game.h"

class Text
{
    public:
        SDL_Texture* message_tex;
        SDL_Rect destRect;
    public:
        Text(const char* text, SDL_Color color, SDL_Rect destRect, int wraplen = 0);
        ~Text() {SDL_DestroyTexture(message_tex);};
        void Update();
};

#endif