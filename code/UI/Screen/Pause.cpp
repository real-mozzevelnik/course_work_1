#include "Pause.h"

#include "../../Helpers/TextureManager.h"
#include "../../Collections/Sounds.h"

Pause::Pause() : Screen(PAUSE_TEXT, WHITE, {Game::screen_w/2 - 100, Game::screen_h/8, 200, 100})
{
    bg_tex = TextureManager::LoadTexture("../graphics/background/Menu.png");

    bg_destRect.x = bg_destRect.y = 0;
    bg_destRect.w = Game::screen_w;
    bg_destRect.h = Game::screen_h;

    Button* tmp_but = new Button(MENU_MAIN_TEXT, {Game::screen_w/2 - 400, static_cast<int>((Game::screen_h/8)*6.5), 300, 100}, MENU);
    buttons.insert({MENU, tmp_but});
    tmp_but = new Button(BACK_BUTTON_TEXT, {Game::screen_w/2 + 100, static_cast<int>((Game::screen_h/8)*6.5), 300, 100}, RUN);
    buttons.insert({RUN, tmp_but});
}


Pause::~Pause()
{
    for (auto i : buttons)
        delete i.second;

    SDL_DestroyTexture(bg_tex);
}


void Pause::PushButtons()
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
            {
                Game::state = i.second->state_to_change;
                if (Game::state == MENU)
                {
                    SoundsManager::music[Game::level_num]->Stop();
                    SoundsManager::music[0]->Play();
                }
            }
        }
        else
            i.second->button_color.g = 120;
    }
}


void Pause::Update()
{
    SDL_RenderCopy(Game::renderer, bg_tex, NULL, &bg_destRect);
    message_text->Update();

    for (const auto& i : buttons)
        i.second->Update();

    PushButtons();
}