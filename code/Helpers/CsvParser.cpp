#include "CsvParser.h"

#include <istream>
#include <fstream>
#include <sstream>

vector<vector<int>> CsvParser::ParseCsv(const char* filepath)
{
    ifstream file(filepath);

    if (file.fail()) cout << "csv fail" << endl;

    string line;
    string elem;
    

    vector<vector<int>> map;

    while (getline(file, line) && file.good())
    {
        istringstream token(line);
        vector<int> tmp;
        while (getline(token, elem, ','))
            tmp.push_back(stoi(elem));
        map.push_back(tmp);
    }

    file.close();

    return map;
}