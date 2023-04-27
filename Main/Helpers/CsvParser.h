#ifndef CsvParser_h
#define CsvParser_h

#include <vector>
#include "../Configs.h"

class CsvParser
{
    public:
        static vector<vector<char>> ParseCsv(const char* filepath);
};

#endif