#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include "OperationMain.h"
#include "OrderBookEntry.h"
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

    ifstream file("order_book_origin.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file!" << endl;
        return -1;
    }

    string line;
    vector<string> tokens; 

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        tokens = tokenize(line, ',');
        if (tokens.size() != 5) {
            cout << "Bad line!" << endl;
            continue;
        }

        string timestamp, product, typeStr;
        timestamp = tokens[0];
        product = tokens[1];
        typeStr = tokens[2];

        double price, amount;

        try {
            price = stod(tokens[3]);
            amount = stod(tokens[4]);
        } catch (const exception& e) {
            cout << "Bad float! " << tokens[3] << endl;
            cout << "Bad float! " << tokens[4] << endl;
            continue; // break;
        }

        OrderBookEntry obe(timestamp, product, typeStr, price, amount);
        orders.push_back(obe);
    }

    file.close();
    return 0;
}

void OperationMain::printMarketStats() {
    
    cout << "Order Book size: " << orders.size() << " entries" << endl;

    double sumPrice = 0.0;
    double minPrice = numeric_limits<double>::max();
    double maxPrice = numeric_limits<double>::lowest();

    for (const auto &entry : orders) {
        double currentPrice = entry.getPrice();
        sumPrice += currentPrice;
        if (currentPrice < minPrice) minPrice = currentPrice;
        if (currentPrice > maxPrice) maxPrice = currentPrice;
    }

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
    cout << "7: Continue\n" << endl;
}

int OperationMain::getUserOption() {
    int userOption;
    cout << "Type in 1 - 6: ";
    cin >> userOption;
    return userOption;
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
            cout << "To be continued..." << endl;
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
