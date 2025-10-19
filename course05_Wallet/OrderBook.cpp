#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

/** Default constructor */
OrderBook::OrderBook(std::string filename) {
	orders = CSVReader::readCSV(filename);

	if (orders.empty()) {
		std::cerr << "Error: Could not load any orders from CSV!" << std::endl;
	}
}

/** Get a list of known products in the order book */
std::vector<std::string> OrderBook::getKnownProducts() const {
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;

	for (const OrderBookEntry& e : orders) {
		prodMap[e.getProduct()] = true;
	}

	for (auto const& pair : prodMap) {
		products.push_back(pair.first);
	}

	return products;

	// Assuming orders is a member variable containing all OrderBookEntry objects
	// for (const auto& order : orders) {
	//     std::string product = order.getProduct();
	//     if (std::find(products.begin(), products.end(), product) == products.end()) {
	//         products.push_back(product);
	//     }
	// }
}

/** Get a list of known order types in the order book */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderType type, 
									std::string product,
									std::string timestamp) const {
	std::vector<OrderBookEntry> orders_sub;
	  for(const auto& e : orders){
		  if(e.getTimestamp() <= timestamp && e.getOrderType() == type && e.getProduct() == product)
			  orders_sub.push_back(e);
	  }
	return orders_sub;
}

size_t OrderBook::getOrderCount() const {
	return orders.size();
}

std::string OrderBook::getEarliestTime() {
	return orders[0].getTimestamp();
}

std::string OrderBook::getNextTime(std::string timestamp) {
	for (const OrderBookEntry& e : orders) {
		if (e.getTimestamp() > timestamp) {
			return e.getTimestamp();
		}
	}
	return orders[0].getTimestamp();
	// return "";
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
	double max = orders[0].getPrice();
	for (OrderBookEntry& e : orders) {
		if (e.getPrice() > max) {
			max = e.getPrice();
		}
	}
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
	double min = orders[0].getPrice();
	for (OrderBookEntry& e : orders) {
		if (e.getPrice() < min) {
			min = e.getPrice();
		}
	}
	return min;
}

std::vector<std::string> OrderBook::getAllTimestamps() const {
	std::set<std::string> tsSet;
	for (const auto& entry : orders) {
		tsSet.insert(entry.getTimestamp());
	}
	return std::vector<std::string>(tsSet.begin(), tsSet.end());
}

double OrderBook::getVWAPMatchedAllTimes(const std::string& product, const OrderBook& ob) {

	std::vector<std::string> timestamps = ob.getAllTimestamps();

	double totalPriceVolume = 0.0;
	double totalVolume = 0.0;

	for (const std::string& timestamp : timestamps) {
		std::vector<OrderBookEntry> bids = ob.getOrders(OrderType::bid, product, timestamp);
		std::vector<OrderBookEntry> asks = ob.getOrders(OrderType::ask, product, timestamp);

		if (bids.empty() || asks.empty()) continue;

		double maxBid = OrderBook::getHighPrice(bids);
		double minAsk = OrderBook::getLowPrice(asks);
		std::cout << "Timestamp: " << timestamp << " " << product
				<< " MaxBid: " << maxBid << " MinAsk: " << minAsk << std::endl;
		
		std::sort(bids.begin(), bids.end(), [](const OrderBookEntry& a, const OrderBookEntry& b) {
			return a.getPrice() > b.getPrice();
		});
		std::sort(asks.begin(), asks.end(), [](const OrderBookEntry& a, const OrderBookEntry& b) {
			return a.getPrice() < b.getPrice();
		});

		size_t bidIdx = 0, askIdx = 0;
		while (bidIdx < bids.size() && askIdx < asks.size() && bids[bidIdx].getPrice() >= asks[askIdx].getPrice()) {
			double tradePrice = asks[askIdx].getPrice();
			double tradeVolume = std::min(bids[bidIdx].getAmount(), asks[askIdx].getAmount());

			totalPriceVolume += tradePrice * tradeVolume;
			totalVolume += tradeVolume;

			double newBidAmt = bids[bidIdx].getAmount() - tradeVolume;
			double newAskAmt = asks[askIdx].getAmount() - tradeVolume;
			bids[bidIdx].setAmount(newBidAmt);
			asks[askIdx].setAmount(newAskAmt);

			if (bids[bidIdx].getAmount() <= 0.0) ++bidIdx;
			if (asks[askIdx].getAmount() <= 0.0) ++askIdx;
		}
	}

	if (totalVolume == 0.0) return 0.0;
	return totalPriceVolume / totalVolume;
}

void OrderBook::insertOrder(const OrderBookEntry& order) {
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> sales;
	std::vector<OrderBookEntry> asks = getOrders(OrderType::ask, product, timestamp);
	std::vector<OrderBookEntry> bids = getOrders(OrderType::bid, product, timestamp);
	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc); // sort asks lowest first
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc); // sort bids highest first

	for (OrderBookEntry& ask : asks) 
	{
		if (ask.getAmount() <= 0) continue; // skip asks with no amount left
		
		for (OrderBookEntry& bid : bids) 
		{
			if (bid.getAmount() <= 0) continue; // skip bids with no amount left
			
			if (bid.getPrice() >= ask.getPrice()) 
			{ // we have a match
				OrderBookEntry sale{timestamp, product, OrderType::asksale, ask.getPrice(), 0};
				if (bid.getUsername() == "simuser") 
				{
					sale.setUsername("simuser");
					sale.setOrderType(OrderType::bidsale);
				}
				if (ask.getUsername() == "simuser") 
				{
					sale.setUsername("simuser");
					sale.setOrderType(OrderType::asksale);
				}
				
				// Calculate the matched amount
				double matchedAmount = std::min(ask.getAmount(), bid.getAmount());
				sale.setAmount(matchedAmount);
				sales.push_back(sale);
				
				// Update remaining amounts
				ask.setAmount(ask.getAmount() - matchedAmount);
				bid.setAmount(bid.getAmount() - matchedAmount);
				
				// If ask is fully filled, move to next ask
				if (ask.getAmount() <= 0) {
					break;
				}
			}
		}
	}
	return sales;
}