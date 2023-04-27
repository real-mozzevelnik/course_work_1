#include "CsvParser.h"

#include <istream>
#include <fstream>

vector<vector<char>> CsvParser::ParseCsv(const char* filepath)
{
    ifstream file(filepath);

    if (file.fail()) cout << "csv fail" << endl;

    string line;

    vector<vector<char>> map;

    int count = 0;
    while (getline(file, line) && file.good())
    {
        vector<char> tmp;
        for (int i = 0; i < line.size(); i++)
        {
            tmp.push_back(line[i]);
        }
        map.push_back(tmp);
        count++;
    }

    file.close();

    return map;

}

int main()
{
    vector<vector<char>> map = CsvParser::ParseCsv("../levels/hhh.csv");

    for (int i= 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); i++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}