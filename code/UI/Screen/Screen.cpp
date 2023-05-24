#include "Screen.h"

Screen::Screen(const char* message, SDL_Color text_color, SDL_Rect text_pos)
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
    message_text = new Text(message, text_color, text_pos);
    continue_text = new Text(CONTINUE_TEXT, WHITE, {275,600,500,100});
}

Screen::~Screen()
{
    cout << "screen dest" << endl;
    delete message_text;
    delete continue_text;
}


void Screen::Update()
{
    if (Game::event.key.keysym.sym == SDLK_RETURN)
        Game::state = CREATE_NEW_LEVEL;

    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);

    message_text->Update();
    continue_text->Update();
}