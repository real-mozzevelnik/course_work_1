#include "Map.h"
#include <map>

#include "../Helpers/CsvParser.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Game/Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/Entities/Enemy.h"

void Map::CreateMap()
{
    // Загружаем все слои карты.
    map<string, vector<vector<int>>> layouts {
        {"terrain", CsvParser::ParseCsv("../level/level_1_csv/terrain.csv")},
        {"box", CsvParser::ParseCsv("../level/level_1_csv/box.csv")},
        {"door", CsvParser::ParseCsv("../level/level_1_csv/door.csv")},
        {"coins", CsvParser::ParseCsv("../level/level_1_csv/coins.csv")},
        {"enemies", CsvParser::ParseCsv("../level/level_1_csv/enemies.csv")},
        {"stoppers", CsvParser::ParseCsv("../level/level_1_csv/stoppers.csv")},
        {"player", CsvParser::ParseCsv("../level/level_1_csv/player.csv")},
        {"grass", CsvParser::ParseCsv("../level/level_1_csv/grass.csv")},
        {"dialog", CsvParser::ParseCsv("../level/level_1_csv/dialog.csv")}
    };

    SDL_Texture* terrain_img = TextureManager::LaodTexture("../graphics/tiles/terrain_tiles/level_1.png");
    vector<SDL_Rect> terrain_rects = TextureManager::CutGraphics(terrain_img, TILE_SIZE);
    vector<SDL_Texture*> enemy_lich_img = TextureManager::LoadAnimationTextures("../graphics/enemies/lich", 27);
    vector<SDL_Texture*> enemy_ghost_img = TextureManager::LoadAnimationTextures("../graphics/enemies/ghost", 6);



    // Загружаем фон.
    Level::bg = new Background("../graphics/background/level_1.png", 0, TILE_SIZE);
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
                    Tile* tile = new Tile("../graphics/tiles/terrain_tiles/level_1.png", x, y, terrain_rects[layout[row_index][col_index]]);
                    Level::tiles.push_back(tile);
                    Level::collidable_objects.push_back(static_cast<GameObject*>(tile));
                }
                else if (style == "box")
                {
                    // create box
                }
                else if (style == "door")
                {
                    // create door
                }
                else if (style == "coins")
                {
                    Tile* tile = new Tile("../graphics/tiles/coin.png", x, y, {0,0,32,32});
                    Level::coins.push_back(tile);
                }
                else if (style == "enemies")
                {
                    // create enemy
                }
                else if (style == "stoppers")
                {
                    // create stoppers
                }
                else if (style == "player")
                {
                    Level::player = new Player("../graphics/charlieTheCapybaraAnimationSheet.png", x, y);
                }
                else if (style == "grass")
                {
                    // create grass
                }
                else if (style == "dialog")
                {
                    // create dialog
                }
            }
        }
    }
    
}