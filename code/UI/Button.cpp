#include "Button.h"

Button::Button(const char* button_text, SDL_Rect button_destRect, int state)
{
    text = new Text(button_text, WHITE, 
    {button_destRect.x + 30, button_destRect.y + 30, button_destRect.w - 60, button_destRect.h - 60});
    destRect = button_destRect;

    button_color.g = 120;
    button_color.a = button_color.b = button_color.r = 0;

    state_to_change = state;
}



Button::~Button()
{
    delete text;
    cout << "Button dest" << endl;
}


void Button::Update()
{
    SDL_SetRenderDrawColor(Game::renderer, button_color.r, button_color.g, button_color.b, button_color.a);
    SDL_RenderFillRect(Game::renderer, &destRect);
    text->Update();
}