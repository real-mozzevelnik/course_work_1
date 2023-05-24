#include "Game.h"
#include "Level.h"
#include "../UI/Screen/Screen.h"

// Объявляем static поля класса.
SDL_Renderer* Game::renderer = nullptr;
int Game::state;
int Game::level_num = 1;
int Game::total_coins_earned = 0;
SDL_Event Game::event;
int Game::screen_h;
int Game::screen_w;


// Конструктор.
Game::Game(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen)
{
    // В зависимости от выбранного режима (полный / неполный экран) 
    // выбираем флаги.
    int flags;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    else flags = SDL_WINDOW_SHOWN;

    // Инициализация SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL INIT ERROR: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    // При завершении программы очистить ресурсы, выделенные SDL.
    atexit(SDL_Quit);
    
    // Инициализация TTF.
    if (TTF_Init() != 0)
    {
        cout << "TTF INIT ERROR: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }
    // При завершении программы очистить ресурсы, выделенные TTF.
    atexit(TTF_Quit);

    // Создаем окно.
    window = SDL_CreateWindow(title, xpos, ypos, width, heigth, flags);
    if (!window)
    {
        cout << "WINDOW CREATION ERROR: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    // Создаем рендерер.
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        cout << "RENDERER CREATION ERROR: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    SDL_GetRendererOutputSize(renderer, &screen_w, &screen_h);
    // Начинаем игровой цикл.
    isRunning = true;

    // Состояние игры в начале - меню.
    state = CREATE_NEW_LEVEL;
    // Номер уровня в начале игры - 0.
    level_num = 2;
    // Создаем уровень.
    // level = new Level();
    level = nullptr;
    death_screen = new Screen("ПОМЕР", RED, {screen_w/2-150, screen_h/2-200, 300, 200});
}


// Деструктор.
Game::~Game()
{
    // Удаляем уровень.
    if (level)
        delete level;
    // Удаляем разные экраны.
    delete death_screen;
    // Освобождаем всю выделенную SDL память.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cout << "End" << endl;
}


// Обновление объектов на экране.
void Game::Update()
{
    // Очищаем буфер рендерера.
    SDL_RenderClear(renderer);
    // Обрабатываем события.
    HandleEvents();
    // В зависимости от текущего состояния выполняем необходимые действия.
    CheckState();
    // Рисуем все объекты из рендерера.
    SDL_RenderPresent(renderer);
}


// Обрабатываем события (действия пользователя).
void Game::HandleEvents()
{
    // Считываем события.
    SDL_PollEvent(&event);
    switch (event.type)
    {
    // Если событие - выход, то останавливаем игровой цикл.
    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_KEYDOWN:
        Level::kb.HandleKeyEvent(static_cast<int>(event.key.keysym.sym % 350), 1);
        break;

    case SDL_KEYUP:
        Level::kb.HandleKeyEvent(static_cast<int>(event.key.keysym.sym % 350), 0);
    
    default:
        break;
    }
}


// В зависимости от текущего состояния игры выполняем дейтсвия.
void Game::CheckState()
{
    if (state == MENU)
    {
        
    }
    else if (state == RUN)
    {
        level->Run();
    }
    else if (state == DEATH)
    {
        if (level)
            { delete level; level = nullptr; }
        death_screen->Update();
    }
    else if (state == CREATE_NEW_LEVEL)
    {
        level = new Level();
        state = RUN;
    }
}


// Запуск игры.
void Game::Run()
{
    // Нужное кол-во FPS.
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    while (isRunning)
    {
        // Записываем кол-во мс с начала инициализации SDL.
        frameStart = SDL_GetTicks();

        // Обновляем всё.
        Update();

        // Высчитываем кол-во мс, прошедших за итерацию.
        frameTime = SDL_GetTicks() - frameStart;

        // Задержка для выравнивания fps.
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        } 
    }
}