#ifndef Background_h
#define Background_h

#include "GameObject.h"


// Наследуемся от класса GameObject.
// Класс background отличается только конструктором.
class Background: public GameObject
{
    public:
        Background(SDL_Texture* tex, int x, int y);
        ~Background() {cout << "Background destructor" << endl; };
};

#endif