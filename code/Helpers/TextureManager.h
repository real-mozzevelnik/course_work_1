#ifndef TextureManager_h
#define TextureManager_h

#include "../Game/Game.h"
#include <vector>

// Класс, отвечающий за загрузку текстур.
class TextureManager
{
    public:
        // Метод для загрузки текстуры, принимает имя загружаемого файла.
        static SDL_Texture* LaodTexture(const char *filename);
        static vector<SDL_Rect> CutGraphics(SDL_Texture *texture, int size);
};

#endif