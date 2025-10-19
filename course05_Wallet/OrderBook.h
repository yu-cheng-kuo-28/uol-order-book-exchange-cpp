#pragma once
#include <string>
#include <set>
#include <algorithm>
#include "OrderBookEntry.h"
#include "CSVReader.h"

struct MatchResult {
	double tickPrice;
	double matchedVolume;
};
class OrderBook {
public:
	/** Default constructor */
	OrderBook(std::string filename);
	/** Get a list of known products in the order book */
	std::vector<std::string> getKnownProducts() const;
	/** Get a list of known order types in the order book */
	std::vector<OrderBookEntry> getOrders(OrderType type, 
										std::string product,
										std::string timestamp) const;
	size_t getOrderCount() const;
	std::string getEarliestTime();
	/** Return the next timestamp after the given one
	 * send time in the order book, it there's no next timestamp, return the last one
	 * @param timestamp the timestamp to compare with
	 * @return the next timestamp after the given one
	 */
	std::string getNextTime(std::string timestamp);
	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
	std::vector<std::string> getAllTimestamps() const;
	static double getVWAPMatchedAllTimes(const std::string& product, const OrderBook& ob);
	void insertOrder(const OrderBookEntry& entry);
	std::vector<OrderBookEntry> matchAsksToBids(const std::string product, 
												const std::string timestamp);

private:
	std::vector<OrderBookEntry> orders;

};

/*
class OrderBook {
private:
	vector<OrderBookEntry> orders;

public:
	OrderBook() = default;

	void addOrder(const OrderBookEntry& entry) {
		orders.push_back(entry);
	}

	const vector<OrderBookEntry>& getOrders() const {
		return orders;
	}

	void clear() {
		orders.clear();
	}
};
*/