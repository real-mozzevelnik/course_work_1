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
        // Метод для нарезки текстуры на прямоугольные области для поочередной прорисовки.
        static vector<SDL_Rect> CutGraphics(SDL_Texture *texture, int size);
        // Метод для загрузки массива текстур из указанной директории.
        static vector<SDL_Texture*> LoadAnimationTextures(const char* path, int tex_num);
        // Метод для удаления массива текстур.
        static void DestroyAnimationTextures(vector<SDL_Texture*> texs);
};

#endif