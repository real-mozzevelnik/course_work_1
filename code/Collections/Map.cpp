#include "Map.h"
#include <map>

#include "../Helpers/CsvParser.h"
#include "../Objects/StaticObjects/Tile.h"
#include "../Game/Level.h"
#include "../Objects/StaticObjects/Background.h"
#include "../Objects/Entities/Player.h"
#include "../Objects/Entities/Enemy.h"
#include "../UI/UI.h"

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
    vector<SDL_Texture*> enemy_lich_img = TextureManager::LoadAnimationTextures("../graphics/enemies/lich/", 28);
    vector<SDL_Texture*> enemy_ghost_img = TextureManager::LoadAnimationTextures("../graphics/enemies/ghost/", 7);
    vector<vector<SDL_Texture*>> enemies_imgs;
    enemies_imgs.push_back(enemy_lich_img);
    enemies_imgs.push_back(enemy_ghost_img);



    // Загружаем фон.
    Level::bg = new Background("../graphics/background/level_1.png", 0, 0);
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
                    Tile* box = new Tile("../graphics/tiles/crate.png", x, y, {0,0,58,42});
                    Level::tiles.push_back(box);
                    Level::collidable_objects.push_back(static_cast<GameObject*>(box)); 
                }
                else if (style == "door")
                {
                    // create door
                }
                else if (style == "coins")
                {
                    Tile* coin = new Tile("../graphics/tiles/coin.png", x, y, {0,0,BASIC_SIZE,BASIC_SIZE});
                    Level::coins.push_back(coin);
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
    
    Level::ui = new UI;
}