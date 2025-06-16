#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
using namespace std;

class OperationMain {
public: 
    OperationMain();
    void init();
private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    int getUserOption();
    void processUserOption(int userOption);
    void walletStatus();
    void getNextTimeFrame();
    void getVWAP();
    void enterAsk();
    void enterBid();

    std::string currentTime;

    OrderBook orderBook{"test.csv"};
    // OrderBook orderBook{"order_book_origin.csv"};
};