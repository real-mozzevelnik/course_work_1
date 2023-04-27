#include "Game/Game.h"

int main(int argc, char **argv)
{
    // Создаем игру.
    Game game("Test", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK,
        SCREEN_WIDTH, SCREEN_HEIGHT, true);

    // Запускаем игру.
    game.Run();
    return 0;
}