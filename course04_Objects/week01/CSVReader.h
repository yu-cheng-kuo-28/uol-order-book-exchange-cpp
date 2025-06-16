#pragma once

#include <vector>
#include <string>
#include "OrderBookEntry.h"

class CSVReader
{
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(const std::string& csvFile);

private:
    static std::vector<std::string> tokenize(const std::string& csvLine, char separator);

    static OrderBookEntry stringsToOBE(const std::vector<std::string>& tokens);
};

/*
#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        static std::vector<std::string> tokenize(std::string csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::string price, 
                                           std::string amount, 
                                           std::string timestamp,
                                           std::string product, 
                                           OrderBookType orderType);

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};
*/