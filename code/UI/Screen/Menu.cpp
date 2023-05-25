#include "Menu.h"

#include "../../Helpers/TextureManager.h"
#include "../Button.h"

Menu::Menu() : Screen(MENU_MAIN_TEXT, WHITE, {Game::screen_w/2 - 100, Game::screen_h/8, 200, 100})
{
    bg_tex = TextureManager::LoadTexture("../graphics/background/Menu.png");
    cout << SDL_GetError() << endl;
    bg_destRect.x = bg_destRect.y = 0;
    bg_destRect.w = Game::screen_w;
    bg_destRect.h = Game::screen_h;

    menu_state = MAIN_MENU;

    Button *tmp_button;
    tmp_button = new Button("EXIT", {300, 300, 200, 100}, EXIT);
    buttons.insert({EXIT, tmp_button});
}


Menu::~Menu()
{
    for (auto i : buttons)
        delete i.second;

    SDL_DestroyTexture(bg_tex);
    cout << "Menu dest" << endl;
}


void Menu::CheckMenuState()
{
    switch (menu_state)
    {
    case MAIN_MENU:
        buttons.at(EXIT)->Update();
        break;
    
    case ENTER_NAME:
        break;
    case EXIT:
        exit(EXIT_SUCCESS);
        break;
    }
}


void Menu::Update()
{
    SDL_RenderCopy(Game::renderer, bg_tex, NULL, &bg_destRect);
    message_text->Update();

    CheckMenuState();
}