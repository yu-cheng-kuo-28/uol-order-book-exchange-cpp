#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
using namespace std;

class OperationMain {
public: 
    OperationMain();
    /** Call init() to start */
    void init();
private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    int getUserOption();
    void processUserOption(int userOption);
    void walletStatus();
    void getNextTimeFrame();

    std::string currentTime;

    OrderBook orderBook{"order_book_origin.csv"};
};