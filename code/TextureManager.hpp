#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager
{
    public:
        static SDL_Texture* LaodTexture(const char *filename);
        static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};

#endif