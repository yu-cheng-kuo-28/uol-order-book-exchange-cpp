#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& csvFile)
{
    std::vector<OrderBookEntry> entries;
    std::ifstream file(csvFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << csvFile << std::endl;
        return entries;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = tokenize(line, ',');
        if (tokens.size() != 5) continue;
        try {
            entries.push_back(stringsToOBE(tokens));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << "\n" << e.what() << std::endl;
        }
    }
    file.close();
    return entries;
}

std::vector<std::string> CSVReader::tokenize(const std::string& csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::stringstream ss(csvLine);
    std::string item;
    while (std::getline(ss, item, separator)) {
        tokens.push_back(item);
    }
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens)
{
    std::string timestamp = tokens[0];
    std::string product = tokens[1];
    std::string typeStr = tokens[2];
    double price = std::stod(tokens[3]);
    double amount = std::stod(tokens[4]);
    return OrderBookEntry(timestamp, product, typeStr, price, amount);
}