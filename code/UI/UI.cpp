#include "UI.h"

#include "../Helpers/TextureManager.h"

UI::UI()
{
    health_bar = TextureManager::LaodTexture("../graphics/ui/health_bar.png");
    health_bar_srcRect.x = health_bar_srcRect.y = 0;
    health_bar_srcRect.w = 192;
    health_bar_srcRect.h = 64;
    health_bar_destRect.x = health_bar_destRect.y = 30;
    health_bar_destRect.w = 192;
    health_bar_destRect.h = 80;
}


UI::~UI()
{
    cout << "ui dest" << endl;
}


void UI::Update()
{
    SDL_RenderCopy(Game::renderer, health_bar, &health_bar_srcRect, &health_bar_destRect);
    // SDL_RenderDrawRect()
}