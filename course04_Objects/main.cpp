/*
g++ main.cpp OrderBookEntry.cpp -o main
*/
#include <iostream>

#include "OrderBookEntry.h"
#include "OperationMain.h"
using namespace std;

void printMenu();
int getUserOption();
void processUserOption(int userOption);
void printHelp();
void walletStatus();

int main() {

    OperationMain app{};
    app.init();

    
    return 0;
}