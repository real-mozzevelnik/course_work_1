#include "Game.h"
#include "Level.h"

// Объявляем static поля класса.
SDL_Renderer* Game::renderer = nullptr;
string Game::state;
int Game::level_num = 0;
SDL_Event Game::event;


// Конструктор.
Game::Game(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen)
{
    // В зависимости от выбранного режима (полный / неполный экран) 
    // выбираем флаги.
    int flags;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    else flags = SDL_WINDOW_SHOWN;

    // Инициализация SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Init success" << endl;

        // Создаем окно.
        window = SDL_CreateWindow(title, xpos, ypos, width, heigth, flags);
        if (window)
        {
            cout << "Window success" << endl;
        }

        // Создаем рендерер.
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            // Заполняем фон черным.
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "Renderer success" << endl;
        }
        // Начинаем игровой цикл.
        isRunning = true;

        // Состояние игры в начале - меню.
        state = "Menu";
        // Номер уровня в начале игры - 0.
        level_num = 0;
        // Создаем уровень.
        level = new Level();
    }
    else isRunning = false;
}


// Деструктор.
Game::~Game()
{
    // Удаляем уровень.
    delete level;
    // Освобождаем всю выделенную SDL память.
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "End" << endl;
}


// Обновление объектов на экране.
void Game::Update()
{
    // Очищаем буфер рендерера.
    SDL_RenderClear(renderer);
    // В зависимости от текущего состояния выполняем необходимые действия.
    CheckState();
    // Обрабатываем события.
    HandleEvents();
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
    
    default:
        break;
    }
}


// В зависимости от текущего состояния игры выполняем дейтсвия.
void Game::CheckState()
{
    if (state == "Menu")
    {
        level->Run();
    }
    else if (state == "Run")
    {

    }
    else if (state == "Death")
    {

    }
}


// Запуск игры.
void Game::Run()
{
    // Нужное кол-во fps - 60.
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