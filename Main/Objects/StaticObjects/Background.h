#ifndef Background_h
#define Background_h

#include "GameObject.h"


// Наследуемся от класса GameObject.
// Класс background отличается только конструктором.
class Background: public GameObject
{
    public:
        Background(const char *texturesheet, int x, int y);
        ~Background() {cout << "Background destructor" << endl; };
};

#endif