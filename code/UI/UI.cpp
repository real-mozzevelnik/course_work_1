#include "UI.h"

#include "../Helpers/TextureManager.h"
#include "../Game/Level.h"
#include "../Objects/Entities/Player.h"

UI::UI()
{
    health_bar = TextureManager::LaodTexture("../graphics/ui/health_bar.png");
    health_bar_srcRect.x = health_bar_srcRect.y = 0;
    health_bar_srcRect.w = 192;
    health_bar_srcRect.h = 64;
    health_bar_destRect.x = health_bar_destRect.y = 30;
    health_bar_destRect.w = 192;
    health_bar_destRect.h = 80;

    health_destRect.x = 62;
    health_destRect.y = 64;
    health_destRect.w = HEALTH_BAR_WIDTH;
    health_destRect.h = 10;
    SDL_SetRenderDrawColor(Game::renderer, 180, 0, 0, 0);
}


UI::~UI()
{
    cout << "ui dest" << endl;
}


void UI::Update()
{
    health_destRect.w = static_cast<int>((Level::player->heal_points / 100.)*HEALTH_BAR_WIDTH);
    SDL_RenderCopy(Game::renderer, health_bar, &health_bar_srcRect, &health_bar_destRect);
    SDL_RenderFillRect(Game::renderer, &health_destRect);
}