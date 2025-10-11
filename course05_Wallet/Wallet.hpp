#include <cstring>

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


#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"

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