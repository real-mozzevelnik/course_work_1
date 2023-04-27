#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Game
{
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen);
        
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running() { return isRunning; };

        static SDL_Renderer *renderer;

    private:
        bool isRunning;
        SDL_Window *window;

};

#endif