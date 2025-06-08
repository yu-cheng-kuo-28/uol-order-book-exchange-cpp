#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include "OperationMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;

OperationMain::OperationMain() {

}

void OperationMain::init() {
    loadOrderBook();

    int userOption;
    while (true) {
        printMenu();
        userOption = getUserOption();
        processUserOption(userOption);
    }
}

vector<string> tokenize(const string& csvLine, char sep) {
    if (csvLine.empty()) {
        return {};
    }

    vector<string> tokens;
    size_t start = 0;

    while (true) {
        size_t end = csvLine.find(sep, start);
        if (end == string::npos) {
            tokens.push_back(csvLine.substr(start));
            break;
        } else {
            tokens.push_back(csvLine.substr(start, end - start));
            start = end + 1;
        }
    }

    return tokens;
}

int OperationMain::loadOrderBook() {
    orders = CSVReader::readCSV("order_book_origin.csv");
    if (orders.empty()) {
        std::cerr << "Error: Could not load any orders from CSV!" << std::endl;
        return -1;
    }
    return 0;
}


void OperationMain::printMarketStats() {
    
    double sumPrice = 0.0;
    double minPrice = numeric_limits<double>::max();
    double maxPrice = numeric_limits<double>::lowest();
    int bidCount = 0;
    int askCount = 0;

    for (const auto &entry : orders) {
        double currentPrice = entry.getPrice();
        sumPrice += currentPrice;
        if (currentPrice < minPrice) minPrice = currentPrice;
        if (currentPrice > maxPrice) maxPrice = currentPrice;

        OrderType type = entry.getType();
        if (type == OrderType::bid) ++bidCount;
        else if (type == OrderType::ask) ++askCount;
    }

    cout << "Order Book size: " << orders.size() << " entries" << endl;
    cout << " - Number of Bids: " << bidCount << "\n";
    cout << " - Number of Asks: " << askCount << "\n";

    double avgPrice = (orders.empty() ? 0.0 : sumPrice / orders.size());

    cout << "\nBasic Stats over all entries:\n";
    cout << " - Average Price: " << avgPrice << "\n";
    cout << " - Minimum Price: " << minPrice << "\n";
    cout << " - Maximum Price: " << maxPrice << "\n";
}


void OperationMain::printMenu() {
    cout << "\n=========================" << endl;
    cout << "1: Print help" << endl;
    cout << "2: Print market statistics" << endl;
    cout << "3: Print exchange states" << endl;
    cout << "4: Place an ask" << endl;
    cout << "5: Place a bid" << endl;
    cout << "6: Print wallet" << endl;
    cout << "q: Exit\n" << endl;
}

int OperationMain::getUserOption() {
    std::string input;
    cout << "Type in 1 - 6 or q: ";
    cin >> input;

    if (input == "q" || input == "Q") {
        return 7;
    }

    try {
        int option = std::stoi(input);
        return option;
    } catch (...) {
        return -1;
    }
}

void OperationMain::processUserOption(int userOption) {
    cout << endl;
    switch (userOption) {
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            cout << "Exchange states: ???" << endl;
            break;
        case 4:
            cout << "Ask what? ..." << endl;
            break;
        case 5:
            cout << "Beat it!" << endl;
            break;
        case 6:
            walletStatus();
            break;
        case 7:
            cout << "Exiting program..." << endl;
            exit(0); // Quit the program
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 6." << endl;
            break;
    }
}

void OperationMain::printHelp() {
    cout << "Help -- choose options from the menu" << endl;
    cout << "and follow the on-screen instructions" << endl;
}

void OperationMain::walletStatus() {
    cout << "Wallet status: 0" << endl;
    cout << "You are broke man..." << endl;
}
