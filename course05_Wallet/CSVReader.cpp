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
	if (tokens.size() != 5)
	{
		std::cout << "[CSVReader::stringsToOBE] Invalid line " << std::endl;
		throw std::exception{};
	}

	double price, amount;
	try {
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);
	} 
	catch (const std::exception& e) {
		std::cout << "[CSVReader::stringsToOBE] Error processing line (exception found): " << e.what() << std::endl;
		// std::cout << e.what() << std::endl;
	   throw std::exception{};
	}

	OrderBookEntry obe{ tokens[0], tokens[1], OrderBookEntry::stringToOrderType(tokens[2]), price, amount };
	return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string timestamp,
									   std::string product, 
									   OrderType orderType,
									   std::string priceStr,
									   std::string amountStr) {
	double price, amount;
	try {
		price = std::stod(priceStr);
		amount = std::stod(amountStr);
	} 
	catch (const std::exception& e) {
		std::cout << "[CSVReader::stringsToOBE Error processing line] (exception found): " << e.what() << std::endl;
		// std::cout << e.what() << std::endl;
		throw std::exception{};
	}
	OrderBookEntry obe{timestamp, product, orderType, price, amount};
	return obe;
}