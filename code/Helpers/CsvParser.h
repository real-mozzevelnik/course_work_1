#ifndef CsvParser_h
#define CsvParser_h

#include <vector>
#include "../Configs.h"

// Класс для парсинга csv файлов, необходимых для формирования игровой карты.
class CsvParser
{
    public:
        static vector<vector<int>> ParseCsv(const char* filepath);
};

#endif