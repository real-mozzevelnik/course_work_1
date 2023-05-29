#include "Menu.h"

#include "../../Helpers/TextureManager.h"
#include "../Button.h"
#include "../Text.h"

Menu::Menu() : Screen(MENU_MAIN_TEXT, WHITE, {Game::screen_w/2 - 100, Game::screen_h/8, 200, 100})
{
    bg_tex = TextureManager::LoadTexture("../graphics/background/Menu.png");

    bg_destRect.x = bg_destRect.y = 0;
    bg_destRect.w = Game::screen_w;
    bg_destRect.h = Game::screen_h;

    menu_state = MAIN_MENU;
    prev_button_press_time = 0;


    // Создаем все кнопки.
    Button *tmp_button;
    tmp_button = new Button(EXIT_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*6.5), 300, 100}, EXIT_MENU);
    buttons.insert({EXIT_MENU, tmp_button});
    tmp_button = new Button(INFO_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*5), 300, 100}, INFO);
    buttons.insert({INFO, tmp_button});
    tmp_button = new Button(BACK_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*6.5), 300, 100}, MAIN_MENU);
    buttons.insert({MAIN_MENU, tmp_button});
    tmp_button = new Button(RESULTS_TABLE_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*3.5), 300, 100}, RESULTS_TABLE);
    buttons.insert({RESULTS_TABLE, tmp_button});
    tmp_button = new Button(START_GAME_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*2), 300, 100}, START);
    buttons.insert({START, tmp_button});

    // Создаем нужные элементы для страниц меню. 
    info_text = new Text(INFO_TEXT, WHITE, {50, static_cast<int>((Game::screen_h/8)*2), 
        Game::screen_w - 100, Game::screen_h - (Game::screen_h/8)*4});

}


Menu::~Menu()
{
    for (auto i : buttons)
        delete i.second;

    delete info_text;

    SDL_DestroyTexture(bg_tex);
    cout << "Menu dest" << endl;
}


void Menu::PushButtons()
{
    int m_x, m_y;
    SDL_GetMouseState(&m_x, &m_y);

    SDL_Rect tmp_rect = {m_x, m_y, 1, 1};

    for (const auto& i : buttons)
    {
        if (SDL_HasIntersection(&i.second->destRect, &tmp_rect))
        {
            i.second->button_color.g = 150;
            if (Game::event.type == SDL_MOUSEBUTTONDOWN)
                if ((menu_state == MAIN_MENU && i.first != MAIN_MENU) || (menu_state != MAIN_MENU && i.first == MAIN_MENU))
                    if (SDL_GetTicks() - prev_button_press_time > BUTTON_PRESS_COOLDOWN)
                    {
                        prev_button_press_time = SDL_GetTicks();
                        menu_state = i.second->state_to_change;
                    }
        }

        else
            i.second->button_color.g = 120;
    }
}


void Menu::CheckMenuState()
{
    switch (menu_state)
    {
    case MAIN_MENU:
        for (const auto& i : buttons)
            if (i.first != MAIN_MENU)
                i.second->Update();
        break;

    case START:
        buttons.at(MAIN_MENU)->Update();
        break;
    
    case ENTER_NAME:
        buttons.at(MAIN_MENU)->Update();
        break;

    case RESULTS_TABLE:
        buttons.at(MAIN_MENU)->Update();
        break;

    case INFO:
        info_text->Update();
        buttons.at(MAIN_MENU)->Update();
        break;

    case EXIT_MENU:
        Game::state = EXIT;
        break;
    }
}


void Menu::Update()
{
    SDL_RenderCopy(Game::renderer, bg_tex, NULL, &bg_destRect);
    message_text->Update();

    CheckMenuState();

    PushButtons();
}