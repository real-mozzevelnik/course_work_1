#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

#include <iostream>
using namespace std;
Map* map;


GameObject *player;
GameObject *enemy;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{

}


Game::~Game()
{

}


void Game::init(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen)
{
    int flags;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    else flags = SDL_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Init success" << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, heigth, flags);
        if (window)
        {
            cout << "Window success" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer success" << endl;
        }

        isRunning = true;

        player = new GameObject("../graphics/player.png", 100, 100);
        enemy = new GameObject("../graphics/enemy.png", 200, 0);
        map = new Map();
    }
    else isRunning = false;
}


void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}


void Game::update()
{
    player->Update();
    enemy->Update();
}


void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    map->DrawMap();
    player->Render();
    enemy->Render();
    SDL_RenderPresent(renderer);
}


void Game::clean()
{
    delete player;
    delete enemy;
    delete map;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "End" << endl;
}
