#include "Text.h"

Text::Text(const char* text, SDL_Color color, SDL_Rect destRect)
{
    this->destRect = destRect;
    TTF_Font* font = TTF_OpenFont("../graphics/fonts/Kurland.ttf", 13);
    SDL_Surface* message_surf = TTF_RenderText_Solid(font, text, color);
    message_tex = SDL_CreateTextureFromSurface(Game::renderer, message_surf);
    SDL_FreeSurface(message_surf);
    TTF_CloseFont(font);
}


void Text::Update()
{
    SDL_RenderCopy(Game::renderer, message_tex, NULL, &destRect);
}