#ifndef TextureManager_h
#define TextureManager_h

#include "../Game/Game.h"
#include <vector>

// Класс, отвечающий за загрузку текстур.
class TextureManager
{
    public:
        // Метод для загрузки текстуры, принимает имя загружаемого файла.
        static SDL_Texture* LoadTexture(const char *filename);
        static vector<SDL_Rect> CutGraphics(SDL_Texture *texture, int size);
        static vector<SDL_Texture*> LoadAnimationTextures(const char* path, int tex_num);
        static void DestroyAnimationTextures(vector<SDL_Texture*> texs);
};

#endif