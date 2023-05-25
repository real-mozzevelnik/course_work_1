#include "Button.h"

Button::Button(const char* button_text, SDL_Rect button_destRect, int state)
{
    text = new Text(button_text, WHITE, 
    {button_destRect.x + 30, button_destRect.y + 30, button_destRect.w - 60, button_destRect.h - 60});
    destRect = button_destRect;

    state_to_change = state;
}



Button::~Button()
{
    delete text;
    cout << "Button dest" << endl;
}


void Button::Update()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 100, 0, 0);
    SDL_RenderFillRect(Game::renderer, &destRect);
    text->Update();
}