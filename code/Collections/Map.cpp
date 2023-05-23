#include "Map.h"
#include <map>
#include <sstream>

#include "../Helpers/CsvParser.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Game/Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/Entities/Enemy.h"
#include "../UI/UI.h"
#include "../Objects/StaticObjects/Coin.h"

void Map::CreateMap()
{
    string path;
    stringstream ss;
    
    ss << "../level/level_" << Game::level_num << "_csv/";
    path = ss.str();
    ss.str(string());
    ss.clear();

    // Загружаем все слои карты.
    map<string, vector<vector<int>>> layouts {
        {"terrain", CsvParser::ParseCsv((path+"terrain.csv").c_str())},
        {"box", CsvParser::ParseCsv((path+"box.csv").c_str())},
        {"door", CsvParser::ParseCsv((path+"door.csv").c_str())},
        {"coins", CsvParser::ParseCsv((path+"coins.csv").c_str())},
        {"enemies", CsvParser::ParseCsv((path+"enemies.csv").c_str())},
        {"stoppers", CsvParser::ParseCsv((path+"stoppers.csv").c_str())},
        {"player", CsvParser::ParseCsv((path+"player.csv").c_str())}
    };


    ss << "../graphics/tiles/terrain_tiles/level_" << Game::level_num << ".png";
    path = ss.str();
    ss.str(string());
    ss.clear();
    SDL_Texture* terrain_img = TextureManager::LoadTexture(path.c_str());
    vector<SDL_Rect> terrain_rects = TextureManager::CutGraphics(terrain_img, TILE_SIZE);
    vector<SDL_Texture*> enemy_lich_img = TextureManager::LoadAnimationTextures("../graphics/enemies/lich/", 28);
    vector<SDL_Texture*> enemy_ghost_img = TextureManager::LoadAnimationTextures("../graphics/enemies/ghost/", 7);
    vector<vector<SDL_Texture*>> enemies_imgs;
    enemies_imgs.push_back(enemy_lich_img);
    enemies_imgs.push_back(enemy_ghost_img);



    // Загружаем фон.
    ss << "../graphics/background/level_" << Game::level_num << ".png";
    path = ss.str();
    ss.str(string());
    ss.clear();
    Level::bg = new Background(path.c_str(), 0, 0);
    // Загружаем все объекты по слоям.
    for (const auto& [style, layout] : layouts)
    {
        for (int row_index = 0; row_index < layout.size(); row_index++)
        {
            for (int col_index = 0; col_index < layout[row_index].size(); col_index++)
            {
                if (layout[row_index][col_index] == -1)
                    continue;

                int x = col_index * TILE_SIZE;
                int y = row_index * TILE_SIZE;
                x -= 200;
                y += TILE_SIZE;

                if (style == "terrain")
                {
                    // ss << "../graphics/tiles/terrain_tiles/level_" << Game::level_num << ".png";
                    // path = ss.str();
                    // ss.str(string());
                    // ss.clear();
                    Tile* tile = new Tile("../graphics/tiles/terrain_tiles/level_1.png", x, y, terrain_rects[layout[row_index][col_index]]);
                    Level::tiles.push_back(tile);
                    Level::collidable_objects.push_back(static_cast<GameObject*>(tile));
                    Level::movable_objects.push_back(&tile->destRect);
                }
                else if (style == "box")
                {
                    Tile* box = new Tile("../graphics/tiles/crate.png", x, y, {0,0,58,42});
                    Level::tiles.push_back(box);
                    Level::collidable_objects.push_back(static_cast<GameObject*>(box)); 
                    Level::movable_objects.push_back(&box->destRect);
                }
                else if (style == "door")
                {
                    // create door
                }
                else if (style == "coins")
                {
                    Coin* coin = new Coin(x, y);
                    Level::coins.push_back(coin);
                    Level::movable_objects.push_back(&coin->destRect);
                }
                else if (style == "enemies")
                {
                    Enemy* enemy = new Enemy(enemies_imgs[col_index%2], x, y);
                    Level::movable_objects.push_back(&enemy->destRect);
                    Level::enemies.push_back(enemy);
                }
                else if (style == "stoppers")
                {
                    Tile *stopper = new Tile("../graphics/stopper.png", x, y, {0,0,BASIC_SIZE,BASIC_SIZE});
                    Level::enemy_stoppers.push_back(stopper);
                    Level::movable_objects.push_back(&stopper->destRect);
                }
                else if (style == "player")
                {
                    Level::player = new Player("../graphics/charlieTheCapybaraAnimationSheet.png", x, y);
                }
            }
        }
    }
    
    Level::ui = new UI;
}