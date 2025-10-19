#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class OrderType {bid, ask, sale, unknown, asksale, bidsale};

class OrderBookEntry {
public:
	OrderBookEntry(const string& ts,
					const string& prod,
					const OrderType& typeStr,
					const double& p,
					const double& amt,
					std::string username = "dataset");

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
	static OrderType stringToOrderType(std::string s);

	inline static bool compareByTimestamp(const OrderBookEntry& o1, const OrderBookEntry& o2) {
		return o1.timestamp < o2.timestamp;
	}

	inline static bool compareByPriceAsc(const OrderBookEntry& o1, const OrderBookEntry& o2) {
		return o1.price < o2.price;
	}

	inline static bool compareByPriceDesc(const OrderBookEntry& o1, const OrderBookEntry& o2) {
		return o1.price > o2.price;
	}

	inline std::string getTimestamp() const { return timestamp; };
	inline std::string getProduct() const { return product; };
	inline OrderType getOrderType() const { return type; };
	inline double getPrice() const { return price; };
	inline double getAmount() const { return amount; };
	inline std::string getUsername() const { return username; };

	inline void setAmount(double amt) { amount = amt; };
	inline void setPrice(double price) { this->price = price; };
	inline void setTimestamp(const std::string& timestamp) { this->timestamp = timestamp; };
	inline void setProduct(const std::string& product) { this->product = product; };
	inline void setOrderType(OrderType type) { this->type = type; };
	inline void setUsername(const std::string& username) { this->username = username; };

private:
	std::string timestamp;
	std::string product;
	OrderType type;
	double price;
	double amount;
	std::string username;
};