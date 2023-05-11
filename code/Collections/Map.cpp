#include "Map.h"
#include <map>

#include "../Helpers/CsvParser.h"
#include "../Objects/StaticObjects/Tile.h"

void Map::CreateMap()
{
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

                if (style == "terrain")
                {
                    // create terrain
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
                    // create coins
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
                    // create player
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