/*
g++ main.cpp OrderBookEntry.cpp -o main
*/
#include <iostream>

#include "OrderBookEntry.h"
#include "OperationMain.h"
#include "Wallet.hpp"
using namespace std;

void printMenu();
int getUserOption();
void processUserOption(int userOption);
void printHelp();
void walletStatus();

int main() {

	OperationMain app{};
	app.init();

	// Wallet wallet;
	// wallet.insertCurrency("BTC", 10.0);
	// wallet.insertCurrency("USDT", 10000.0);
	// cout << "Wallet has BTC " << wallet.containsCurrency("BTC", 10.0) << endl;
	// wallet.removeCurrency("USDT", 1000.0);
	// cout << wallet.toString() << endl;

	return 0;
}