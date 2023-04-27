#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Configs.h"
#include "Game.hpp"

using namespace std;

Game *game = nullptr;

int main(int argc, char **argv)
{
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Test", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, 
        SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        } 
    }

    game->clean();

    delete game;

    return 0;
}