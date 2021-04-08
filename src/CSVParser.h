#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string> Row;

class CSVParser
{
public:
    CSVParser();
    ~CSVParser();

    std::vector<Row> parse(const std::string filename);
};
