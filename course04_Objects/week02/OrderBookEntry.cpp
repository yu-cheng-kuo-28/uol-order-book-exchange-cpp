#include <string>

#include "OrderBookEntry.h"
using namespace std;


string orderTypeToString(OrderType ot) {
    switch (ot) {
        case OrderType::bid: 
            return "bid";
        case OrderType::ask:   
            return "ask";
    }
    return "unknown";
}

OrderType stringToOrderType(const string &str) {
    if (str == "bid") 
        return OrderType::bid;
    if (str == "ask") 
        return OrderType::ask;
    cerr << "Warning: Unknown order type \"" << str 
            << "\". Defaulting to 'bid'." << endl;
    return OrderType::bid;
}

OrderType OrderBookEntry::stringToOrderType(std::string s) {
  if (s == "bid") return OrderType::bid;
  else if (s == "ask")  return OrderType::ask;
  else return OrderType::unknown;
}

OrderBookEntry::OrderBookEntry(const string& ts,
                               const string& prod,
                               const OrderType& typeStr,
                               const double& p, 
                               const double& amt) : timestamp(ts),
                                             product(prod),
                                             type(typeStr),
                                             price(p),
                                             amount(amt) {
}