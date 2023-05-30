#ifndef Config_h
#define Config_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640
#define BASIC_SIZE 32
#define BASIC_ENTITY_SIZE 64
#define PLAYER_SPEED 2
#define ENEMY_SPEED 1
#define RIGHT 0
#define LEFT 1
#define TILE_SIZE 64
#define ANIMATION_SPEED 0.1
#define HEALTH_BAR_WIDTH 156
#define WHITE {255, 255, 255}
#define BLACK {0, 0, 0}
#define RED {180, 0, 0}
#define GREEN {124, 252, 0}
#define ENEMY_ATTACK_RADIUS_X 90
#define ENEMY_ATTACK_RADIUS_Y 30
#define ENEMY_STRENGTH 15
#define ENEMY_SLASH_FRAMES_NUM 4
#define ENEMY_LICH_FRAMES_NUM 28
#define ENEMY_GHOST_FRAMES_NUM 7
#define GRAVITY_SPEED 0.2
#define UPPER_BOUND 20
#define LEFT_BOUND 200
#define RIGHT_BOUND 700
#define KEYS_NUM 350
#define BUTTON_PRESS_COOLDOWN 300
#define CONTINUE_TEXT "НАЖМИТЕ ENTER, ЧТОБЫ ПРОДОЛЖИТЬ"
#define DEATH_TEXT "ПОМЕР"
#define NEXT_LEVEL_TEXT "СЛЕДУЮЩЕЕ ПРИКЛЮЧЕНИЕ"
#define MENU_MAIN_TEXT "МЕНЮ"
#define EXIT_BUTTON_TEXT "ВЫЙТИ"
#define START_GAME_BUTTON_TEXT "НАЧАТЬ"
#define RESULTS_TABLE_BUTTON_TEXT "ТАБЛИЦА РЕЗУЛЬТАТОВ"
#define INFO_BUTTON_TEXT "СПРАВКА"
#define BACK_BUTTON_TEXT "ВЕРНУТЬСЯ"
#define INFO_TEXT "ПРЕДЫСТОРИЯ:\n    КАПИБАРА НАТАША ОЧЕНЬ ЛЮБИТ ОПАСНЫЕ ПРИКЛЮЧЕНИЯ.\n    ПОМОГИ ЕЙ ПРОЙТИ ВСЕ ПРИКЛЮЧЕНИЯ И ВЫЖИТЬ.\nУПРАВЛЕНИЕ:\n    ДВИГАТЬСЯ НА КЛАВИШИ 'A', 'D', ПРЫЖОК НА 'ПРОБЕЛ'.\n    ПАУЗА - 'ESC'."
#define ENTER_NAME_TEXT "ВВЕДИТЕ ИМЯ ИГРОКА:\n(ENTER ДЛЯ ПРОДОЛЖЕНИЯ)"
#define PAUSE_TEXT "ПАУЗА"
#define EMPTY_RESULTS_TABLE_TEXT "ПУСТО"
#define END_SCREEN_TEXT "СПАСИБО ЗА ИГРУ!"

enum GAME_STATES
{
    MENU,
    RUN,
    DEATH,
    CREATE_NEW_LEVEL,
    NEXT_LEVEL,
    PAUSE,
    EXIT
};

enum MENU_STATES
{
    MAIN_MENU,
    ENTER_NAME,
    START,
    RESULTS_TABLE,
    SHOW_RESULTS,
    INFO,
    EXIT_MENU
};

#define FPS 120

// 1920x1080 pixels my screen

#endif
