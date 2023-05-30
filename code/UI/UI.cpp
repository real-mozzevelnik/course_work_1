#include "UI.h"

#include "../Helpers/TextureManager.h"
#include "../Game/Level.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/StaticObjects/Tile.h"

UI::UI()
{
    health_bar = TextureManager::LoadTexture("../graphics/ui/health_bar.png");
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

    coin = TextureManager::LoadTexture("../graphics/tiles/coin.png");
    coin_srcRect = {0,0,32,32};
    coin_destRect = {23,110,40,40};

    coins_num = new Text(to_string(Game::total_coins_earned).c_str(), WHITE, {63,117,30,30});

}


UI::~UI()
{
    SDL_DestroyTexture(health_bar);
    SDL_DestroyTexture(coin);
    if (coins_num)
        delete coins_num;
    cout << "ui dest" << endl;
}


void UI::UpdateCoinsNum()
{
    delete coins_num;
    coins_num = nullptr;
    coins_num = new Text(to_string(Game::total_coins_earned+Level::coins_earned).c_str(), WHITE, {63,117,30,30});
}


void UI::Update()
{
    SDL_SetRenderDrawColor(Game::renderer, 180, 0, 0, 0);

    coins_num->Update();

    SDL_RenderCopy(Game::renderer, coin, &coin_srcRect, &coin_destRect);

    health_destRect.w = static_cast<int>((Level::player->heal_points / 100.)*HEALTH_BAR_WIDTH);
    if (health_destRect.w < 0)
        health_destRect.w = 0;
    SDL_RenderCopy(Game::renderer, health_bar, &health_bar_srcRect, &health_bar_destRect);
    SDL_RenderFillRect(Game::renderer, &health_destRect);
}