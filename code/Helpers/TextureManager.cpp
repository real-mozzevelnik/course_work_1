#include "TextureManager.h"

#include <string>


// Метод для загрузки текстуры, принимает имя загружаемого файла.
SDL_Texture* TextureManager::LoadTexture(const char *filename)
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

    // Узнаем размер текстуры.
    SDL_QueryTexture(texture, NULL, NULL, &columns, &rows);

    columns = columns / size;
    rows = rows / size;
    vector <SDL_Rect> cut_gr;
    int x;
    int y;
    // Режем текстуру на прямоугольники.
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


vector<SDL_Texture*> TextureManager::LoadAnimationTextures(const char* path, int tex_num)
{
    vector<SDL_Texture*> textures;
    string filename;
    // Загружаем массив текстур из указанной директории.
    for (int i = 0; i < tex_num; i++)
    {
        filename = path;
        // Если номер текстуры меньше 10 - добавляем в начало "0".
        if (i < 10)
            filename += "0";
        filename += to_string(i);
        filename += ".png";
        textures.push_back(TextureManager::LoadTexture(filename.c_str()));
    }
    return textures;
}


void TextureManager::DestroyAnimationTextures(vector<SDL_Texture*> texs)
{
    // Удаляем текстуры из массива.
    for (int i = 0; i < texs.size(); i++)
        SDL_DestroyTexture(texs[i]);
}