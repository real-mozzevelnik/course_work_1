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

    // Состояние игры в начале.
    state = CREATE_NEW_LEVEL;
    // Номер уровня в начале игры.
    level_num = 1;
    // Узнаем размеры экрана.
    SDL_GetRendererOutputSize(renderer, &screen_w, &screen_h);
    // Инициализируем основные игровые поля.
    level = nullptr;
    death_screen = new Screen(DEATH_TEXT, RED, {screen_w/2-150, screen_h/2-200, 300, 200});
    next_level_screen = new Screen(NEXT_LEVEL_TEXT, WHITE, {screen_w/2-285, screen_h/2-200, 600, 150});

    // Начинаем игровой цикл.
    isRunning = true;
}


// Деструктор.
Game::~Game()
{
    // Удаляем уровень.
    if (level)
        delete level;
    // Удаляем разные экраны.
    delete death_screen;
    delete next_level_screen;
    // Освобождаем всю выделенную SDL память.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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
    // Парсим клавиатуру с помощью кастомного парсера.
    // (Причина, по которой был написан кастомный парсер состоит в том,
    // что SDL_Event - это union, из-за чего нет возможности обрабатывать несколько
    // одновременных нажатий клавиш).
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
        // Удаляем уровень, чтобы потом создать новый.
        if (level)
            { delete level; level = nullptr; }
        death_screen->Update();
    }
    else if (state == NEXT_LEVEL)
    {
        level_num++;
        // Удаляем уровень, чтобы потом создать новый.
        if (level)
            { delete level; level = nullptr; }
        next_level_screen->Update();
    }
    else if (state == CREATE_NEW_LEVEL)
    {
        // Создаем уровень и запускаем его.
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