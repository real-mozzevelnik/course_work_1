#include "CsvParser.h"

#include <istream>
#include <fstream>
#include <sstream>

vector<vector<int>> CsvParser::ParseCsv(const char* filepath)
{
    // Открываем csv файл.
    ifstream file(filepath);

    if (file.fail()) cout << "csv fail" << endl;

    string line;
    string elem;
    
    // Двумерный массив для считывания числовой матрицы.
    vector<vector<int>> map;

    // Парсим файл построчно.
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