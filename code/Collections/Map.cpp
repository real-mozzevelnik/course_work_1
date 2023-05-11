#include "Map.h"
#include <map>

void Map::CreateMap()
{
    map<string, vector<vector<int>>> layouts {
        {"terrain", CsvParser::ParseCsv("../level/level_1_csv/terrain.csv")}
    };
    for (const auto& [key, value] : layouts)
    {
        cout << key << endl;
        for (int i = 0; i < value.size(); i++)
        {
            for (int j = 0; j < value[i].size(); j++)
                cout << value[i][j] << " ";
            cout << endl;
        }
    }
}