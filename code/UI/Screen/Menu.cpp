#include "Menu.h"

#include "../../Helpers/TextureManager.h"

Menu::Menu() : Screen(MENU_MAIN_TEXT, WHITE, {Game::screen_w/2 - 100, Game::screen_h/7, 200, 100})
{
    bg_tex = TextureManager::LoadTexture("../graphics/background/Menu.png");
    cout << SDL_GetError() << endl;
    bg_destRect.x = bg_destRect.y = 0;
    bg_destRect.w = Game::screen_w;
    bg_destRect.h = Game::screen_h;
}


Menu::~Menu()
{
    SDL_DestroyTexture(bg_tex);
    cout << "Menu dest" << endl;
}


void Menu::Update()
{
    SDL_RenderCopy(Game::renderer, bg_tex, NULL, &bg_destRect);
    message_text->Update();
}