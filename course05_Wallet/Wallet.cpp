#include "Wallet.hpp"
#include "CSVReader.h"

Wallet::Wallet() {}

Wallet::~Wallet() {}

void Wallet::insertCurrency(std::string type, double amount) {
	// currencies[type] += amount;
	double balance = 0.0;
	if (amount < 0) {
		throw std::exception();
		// return;
	}
	if (currencies.count(type) == 0) {
		balance = 0.0;
	} else {
		balance = currencies[type];
	}
	balance += amount;
	currencies[type] = balance;
}

bool Wallet::containsCurrency(std::string type, double amount) {
	if (currencies.count(type) == 0) {
		return false;
	} else {
		return currencies[type] >= amount;
	}
}

std::string Wallet::toString() {
	std::string s;
	for (std::pair<std::string, double> p : currencies) {
		std::string currency = p.first;
		double amount = p.second; 
		s += currency + " : " + std::to_string(amount) + "\n";
	}
	return s;
}


bool Wallet::removeCurrency(std::string type, double amount) {
	if (amount < 0) {
		return false;
	}
	if (currencies.count(type) == 0) {
		std::cout << "No currency of type " << type << " found in wallet." << std::endl;
		return false;
	} else {
		if (containsCurrency(type, amount)) {
			std::cout << "Removing " << type << ": " << amount << std::endl;
			currencies[type] -= amount;
			return true;
		} else {
			return false;
		}
	}
}

bool Wallet::canFullfillOrder(OrderBookEntry order) {
	std::vector<std::string> currs = CSVReader::tokenize(order.getProduct(), '/');

	if (order.getOrderType() == OrderType::ask) {
		double amount = order.getAmount();
		std::string currency = currs[0];
		std::cout << "Wallet::canFullfillOrder " << currency << " : " << amount << std::endl;
		return containsCurrency(currency, amount);
	} else if (order.getOrderType() == OrderType::bid) {
		double amount = order.getAmount() * order.getPrice();
		std::string currency = currs[1];
		std::cout << "Wallet::canFullfillOrder " << currency << " : " << amount << std::endl;
		return containsCurrency(currency, amount);
	}

	return false;
}

void Wallet::processSale(OrderBookEntry& sale) {
	std::vector<std::string> currs = CSVReader::tokenize(sale.getProduct(), '/');

	if (sale.getOrderType() == OrderType::asksale) {
		double outgoingAmount = sale.getAmount();
		std::string outgoingCurrency = currs[0];
		double incomingAmount = sale.getAmount() * sale.getPrice();
		std::string incomingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;

		// std::cout << "Wallet::processSale (ask) " << incomingCurrency << " : " << outgoingAmount << std::endl;
		// insertCurrency(incomingCurrency, outgoingAmount);

	} else if (sale.getOrderType() == OrderType::bidsale) {
		double incomingAmount = sale.getAmount();
		std::string incomingCurrency = currs[0];
		double outgoingAmount = sale.getAmount() * sale.getPrice();
		std::string outgoingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
}