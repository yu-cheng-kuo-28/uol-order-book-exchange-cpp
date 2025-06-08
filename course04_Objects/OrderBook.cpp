#include "OrderBook.h"
#include "CSVReader.h"
#include <map>

/** Default constructor */
OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);

    if (orders.empty()) {
        std::cerr << "Error: Could not load any orders from CSV!" << std::endl;
    }
}

/** Get a list of known products in the order book */
std::vector<std::string> OrderBook::getKnowProducts() const {
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
          if(e.getTimestamp() == timestamp && e.getType() == type && e.getProduct() == product)
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

double OrderBook::getLowestPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].getPrice();
    for (OrderBookEntry& e : orders) {
        if (e.getPrice() < min) {
            min = e.getPrice();
        }
    }
    return min;
}