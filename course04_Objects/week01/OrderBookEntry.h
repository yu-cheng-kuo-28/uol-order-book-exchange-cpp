#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class OrderType { bid, ask };

class OrderBookEntry {
private:
    string timestamp;
    string product;
    OrderType type;
    double price;
    double amount;

public:
    OrderBookEntry(const string& ts,
                    const string& prod,
                    const string& typeStr,
                    double p,
                    double amt);

    // OrderBookEntry(const string& ts,
    //                const string& prod,
    //                const string& typeStr,
    //                double p,
    //                double amt)
    //     : timestamp(ts),
    //       product(prod),
    //       type(stringToOrderType(typeStr)),
    //       price(p),
    //       amount(amt) {}

    string getTimestamp() const { return timestamp; }
    string getProduct() const { return product; }
    OrderType getType() const { return type; }
    double getPrice() const { return price; }
    double getAmount() const { return amount; }

    void setAmount(double amt) { amount = amt; }
};