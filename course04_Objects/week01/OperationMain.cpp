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
    // loadOrderBook();
    int userOption;

    currentTime = orderBook.getEarliestTime();

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

// int OperationMain::loadOrderBook() {
//     orders = CSVReader::readCSV("order_book_origin.csv");
//     if (orders.empty()) {
//         std::cerr << "Error: Could not load any orders from CSV!" << std::endl;
//         return -1;
//     }
//     return 0;
// }


void OperationMain::printMarketStats() {
    
    cout << "Order Book size: " << orderBook.getOrderCount() << " entries \n\n";

    for (std::string const prod : orderBook.getKnowProducts()) {
        std::cout << "Product: " << prod << std::endl;
        std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderType::ask, prod, currentTime);
        std::cout << " - Number of Asks: " << entriesAsk.size() << std::endl; 
        if (!entriesAsk.empty()) {
            std::cout << " - Highest Ask Price: " << OrderBook::getHighPrice(entriesAsk) << std::endl;
            std::cout << " - Lowest Ask Price: " << OrderBook::getLowestPrice(entriesAsk) << std::endl;
        } else {
            std::cout << " - Highest Ask Price: N/A" << std::endl;
            std::cout << " - Lowest Ask Price: N/A" << std::endl;
        }
    }   



    // double sumPrice = 0.0;
    // double minPrice = numeric_limits<double>::max();
    // double maxPrice = numeric_limits<double>::lowest();
    // int bidCount = 0;
    // int askCount = 0;

    // for (const auto &entry : orders) {
    //     double currentPrice = entry.getPrice();
    //     sumPrice += currentPrice;
    //     if (currentPrice < minPrice) minPrice = currentPrice;
    //     if (currentPrice > maxPrice) maxPrice = currentPrice;

    //     OrderType type = entry.getType();
    //     if (type == OrderType::bid) ++bidCount;
    //     else if (type == OrderType::ask) ++askCount;
    // }

    // cout << "Order Book size: " << orders.size() << " entries" << endl;
    // cout << " - Number of Bids: " << bidCount << "\n";
    // cout << " - Number of Asks: " << askCount << "\n";

    // double avgPrice = (orders.empty() ? 0.0 : sumPrice / orders.size());

    // cout << "\nBasic Stats over all entries:\n";
    // cout << " - Average Price: " << avgPrice << "\n";
    // cout << " - Minimum Price: " << minPrice << "\n";
    // cout << " - Maximum Price: " << maxPrice << "\n";
}


void OperationMain::getNextTimeFrame() {
    std::cout << "Getting next time frame..." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}


void OperationMain::printMenu() {
    cout << "\n=========================" << endl;
    cout << "1: Print help" << endl;
    cout << "2: Print current exchange states" << endl;
    cout << "3: Place an ask" << endl;
    cout << "4: Place a bid" << endl;
    cout << "5: Print wallet" << endl;
    cout << "6: Get next time frame" << endl;
    cout << "7: Print VWAP" << endl;
    cout << "q: Exit\n" << endl;
    cout << "=========================" << endl;
    cout << "Current time: " << currentTime << endl;
    printf("\n");
}

int OperationMain::getUserOption() {
    std::string input;
    cout << "Type in 1 - 7 or q: ";
    cin >> input;

    if (input == "q" || input == "Q") {
        return 8;
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
            cout << "Ask what? ..." << endl;
            break;
        case 4:
            cout << "Beat it!" << endl;
            break;
        case 5:
            walletStatus();
            break;
        case 6:
            getNextTimeFrame();
            break;
        case 7:
            getVWAP();
            break;
        case 8:
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

void OperationMain::getVWAP() {
    double vwapAll_1 = OrderBook::getVWAPMatchedAllTimes("BTC/USDT", orderBook);
    std::cout << "VWAP for BTC/USDT (all time): " << vwapAll_1 << std::endl;

    double vwapAll_2 = OrderBook::getVWAPMatchedAllTimes("DOGE/BTC", orderBook);
    std::cout << "VWAP for DOGE/BTC (all time): " << vwapAll_2 << std::endl;

    double vwapAll_3 = OrderBook::getVWAPMatchedAllTimes("DOGE/USDT", orderBook);
    std::cout << "VWAP for DOGE/USDT (all time): " << vwapAll_3 << std::endl;

    double vwapAll_4 = OrderBook::getVWAPMatchedAllTimes("ETH/BTC", orderBook);
    std::cout << "VWAP for ETH/BTC (all time): " << vwapAll_4 << std::endl;

    double vwapAll_5 = OrderBook::getVWAPMatchedAllTimes("ETH/USDT", orderBook);
    std::cout << "VWAP for ETH/USDT (all time): " << vwapAll_5 << std::endl;
}