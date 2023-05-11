#include "TextureManager.h"


// Метод для загрузки текстуры, принимает имя загружаемого файла.
SDL_Texture* TextureManager::LaodTexture(const char *filename)
{
    // Загружаем изображение как поверхность.
    SDL_Surface *tempSurface = IMG_Load(filename);
    // Создаем текстуру.
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    // Удаляем поверхность.
    SDL_FreeSurface(tempSurface);

    return tex;
}


vector<SDL_Rect> TextureManager::CutGraphics(SDL_Texture *texture, int size)
{
    int rows;
    int columns;
    SDL_QueryTexture(texture, NULL, NULL, &columns, &rows);
    columns = columns / size;
    rows = rows / size;
    vector <SDL_Rect> cut_gr;
    int x;
    int y;
    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            x = column * size;
            y = row * size;
            cut_gr.push_back({x, y, size, size});
        }
    }

    return cut_gr;
}