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
    tmp_button = new Button(START_GAME_BUTTON_TEXT, {Game::screen_w/2 - 150, static_cast<int>((Game::screen_h/8)*2), 300, 100},ENTER_NAME);
    buttons.insert({ENTER_NAME, tmp_button});

    // Создаем нужные элементы для страниц меню. 
    info_text = new Text(INFO_TEXT, WHITE, {50, static_cast<int>((Game::screen_h/8)*2), 
        Game::screen_w - 100, Game::screen_h - (Game::screen_h/8)*4});
    enter_name_text = new Text(ENTER_NAME_TEXT, WHITE, {Game::screen_w/2 - 175, static_cast<int>((Game::screen_h/8)*2), 350, 150});
    name_input_str = "";
    name_rect = {Game::screen_w/2 - 1, static_cast<int>((Game::screen_h/8)*3.5), 1, 100};
    name = new Text(name_input_str.c_str(), WHITE, name_rect);



}


Menu::~Menu()
{
    for (auto i : buttons)
        delete i.second;

    delete info_text;
    delete enter_name_text;
    delete name;

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


void Menu::EnterName()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_RETURN)
        {
            menu_state = START;
            return;
        }
        if (Game::event.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (name_input_str.size() > 0)
            {
                name_input_str.erase(name_input_str.end()-1);
                name_rect.w -= 20;
                name_rect.x += 10;
            }
        }
        else
        {
            if (name_input_str.size() < 20)
            {
                name_rect.w += 20;
                name_rect.x -= 10;
                if (Game::event.key.keysym.sym == SDLK_SPACE)
                    name_input_str += " ";
                else
                    name_input_str += *SDL_GetKeyName(Game::event.key.keysym.sym);
            }
        }
        delete name;
        name = new Text(name_input_str.c_str(), WHITE, name_rect);;
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
        Game::state = CREATE_NEW_LEVEL;
        menu_state = MAIN_MENU;
        break;
    
    case ENTER_NAME:
        enter_name_text->Update();
        name->Update();
        EnterName();
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