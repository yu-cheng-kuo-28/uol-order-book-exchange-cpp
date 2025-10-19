
#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet {
public:
	Wallet();
	~Wallet();
	void insertCurrency(std::string type, double amount);
	bool removeCurrency(std::string type, double amount);

	bool containsCurrency(std::string type, double amount);
	bool canFullfillOrder(OrderBookEntry order);
	/** Update the wallet based on a sale
	 * @param sale The sale entry to process
	 */
	void processSale(OrderBookEntry& sale);

	std::string toString();

private:
	std::map<std::string, double> currencies;
};

/*
class Wallet {
public:
	Wallet();
	~Wallet();
	void deposit(double amount);
	void withdraw(double amount);
	double getBalance() const;

private:
	double balance;
};
*/

/*
class Wallet {
public:
	Wallet();

	void insertCurrency(std::string currency, double amount);
	bool removeCurrency(std::string currency, double amount);
	bool containsCurrency(std::string currency, double amount);

	std::string toString();

	bool canFullfillOrder(OrderBookEntry order);
	void processSale(OrderBookEntry& sale);

private:
	std::map<std::string, double> currencies;
};
*/