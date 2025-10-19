#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include "OperationMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;

OperationMain::OperationMain() {

}

void OperationMain::init() {
	int userOption;

	currentTime = orderBook.getEarliestTime();

	wallet.insertCurrency("BTC", 10.0);

	while (true) {
		printMenu();
		userOption = getUserOption();
		processUserOption(userOption);
	}
}

vector<string> tokenize(const string& csvLine, char sep) {
	if (csvLine.empty()) {
		return {};
	}

	vector<string> tokens;
	size_t start = 0;

	while (true) {
		size_t end = csvLine.find(sep, start);
		if (end == string::npos) {
			tokens.push_back(csvLine.substr(start));
			break;
		} else {
			tokens.push_back(csvLine.substr(start, end - start));
			start = end + 1;
		}
	}

	return tokens;
}

// 	double sumPrice = 0.0;
// 	double minPrice = numeric_limits<double>::max();
// 	double maxPrice = numeric_limits<double>::lowest();
// 	int bidCount = 0;
// 	int askCount = 0;

// 	for (const auto &entry : orders) {
// 	    double currentPrice = entry.getPrice();
// 	    sumPrice += currentPrice;
// 	    if (currentPrice < minPrice) minPrice = currentPrice;
// 	    if (currentPrice > maxPrice) maxPrice = currentPrice;

// 	    OrderType type = entry.getType();
// 	    if (type == OrderType::bid) ++bidCount;
// 	    else if (type == OrderType::ask) ++askCount;
// 	}

// 	cout << "Order Book size: " << orders.size() << " entries" << endl;
// 	cout << " - Number of Bids: " << bidCount << "\n";
// 	cout << " - Number of Asks: " << askCount << "\n";

// 	double avgPrice = (orders.empty() ? 0.0 : sumPrice / orders.size());

// 	cout << "\nBasic Stats over all entries:\n";
// 	cout << " - Average Price: " << avgPrice << "\n";
// 	cout << " - Minimum Price: " << minPrice << "\n";
// 	cout << " - Maximum Price: " << maxPrice << "\n";
// }

void OperationMain::printMarketStats() 
{
    for (const std::string& p : orderBook.getKnownProducts()) 
    {
        std::cout << "''''''''''''''''''''''" <<std::endl;
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderType::ask, p, currentTime);
        std::cout << "Asks seen: " << asks.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(asks) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(asks) << std::endl;

        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderType::bid, p, currentTime);
        std::cout << "Bids seen: " << bids.size() << std::endl;
        std::cout << "Max bid: " << OrderBook::getHighPrice(bids) << std::endl;
        std::cout << "Min bid: " << OrderBook::getLowPrice(bids) << std::endl;
        std::cout << "''''''''''''''''''''''" <<std::endl;
    }
    std::cout << std::endl;
}



// void OperationMain::getNextTimeFrame() {
// 	std::cout << "Getting next time frame..." << std::endl;
// 	std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
// 	for (OrderBookEntry& sale : sales) {
// 		std::cout << "Sale: " << sale.getPrice() << " " << sale.getAmount() << std::endl;
// 	}
// 	currentTime = orderBook.getNextTime(currentTime);
// }

void OperationMain::getNextTimeFrame() 
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            // Only display and process sales with non-zero amounts
            if (sale.getAmount() > 0) {
                std::cout << "Sale price: " << sale.getPrice() << ", amount: " << sale.getAmount() << std::endl;
                if (sale.getUsername() == "simuser")
                {
                    // update the wallet
                    wallet.processSale(sale);
                }
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << std::endl;
}



void OperationMain::printMenu() {
	cout << "\n=========================" << endl;
	cout << "1: Print help" << endl;
	cout << "2: Print current exchange states" << endl;
	cout << "3: Place an ask" << endl;
	cout << "4: Place a bid" << endl;
	cout << "5: Print wallet" << endl;
	cout << "6: Get next time frame" << endl;
	cout << "7: Print VWAP" << endl;
	cout << "q: Exit\n" << endl;
	cout << "=========================" << endl;
	cout << "Current time: " << currentTime << endl;
	printf("\n");
}

int OperationMain::getUserOption() {
	std::string input;
	cout << "Type in 1 - 7 or q: ";
	cin >> input;

	if (input == "q" || input == "Q") {
		return 20;
	}

	try {
		int option = std::stoi(input);
		return option;
	} catch (const std::exception& e) { // catch (...)
		return -1;
	}
}

void OperationMain::processUserOption(int userOption) {
	cout << endl;
	switch (userOption) {
		case 1:
			printHelp();
			break;
		case 2:
			printMarketStats();
			break;
		case 3:
			enterAsk();
			break;
		case 4:
			enterBid();
			break;
		case 5:
			walletStatus();
			break;
		case 6:
			getNextTimeFrame();
			break;
		case 7:
			getVWAP();
			break;
		case 20:
			cout << "Exiting program..." << endl;
			exit(0); // Quit the program
			break;
		default:
			cout << "Invalid choice! Please enter a number between 1 and 8." << endl;
			break;
	}
}

void OperationMain::printHelp() {
	cout << "Help -- choose options from the menu" << endl;
	cout << "and follow the on-screen instructions" << endl;
}

void OperationMain::walletStatus() {
	// cout << "Wallet status: 0" << endl;
	// cout << "You are broke man..." << endl;
	cout << "Wallet status:" << wallet.toString() << endl;
}

void OperationMain::getVWAP() {
	double vwapAll_1 = OrderBook::getVWAPMatchedAllTimes("BTC/USDT", orderBook);
	std::cout << "VWAP for BTC/USDT (all time): " << vwapAll_1 << std::endl;

	double vwapAll_2 = OrderBook::getVWAPMatchedAllTimes("DOGE/BTC", orderBook);
	std::cout << "VWAP for DOGE/BTC (all time): " << vwapAll_2 << std::endl;

	double vwapAll_3 = OrderBook::getVWAPMatchedAllTimes("DOGE/USDT", orderBook);
	std::cout << "VWAP for DOGE/USDT (all time): " << vwapAll_3 << std::endl;

	double vwapAll_4 = OrderBook::getVWAPMatchedAllTimes("ETH/BTC", orderBook);
	std::cout << "VWAP for ETH/BTC (all time): " << vwapAll_4 << std::endl;

	double vwapAll_5 = OrderBook::getVWAPMatchedAllTimes("ETH/USDT", orderBook);
	std::cout << "VWAP for ETH/USDT (all time): " << vwapAll_5 << std::endl;
}

void OperationMain::enterAsk() {
	std::cout << "Make an ask - enter the data: product, price, amount (e.g ETH/BTC,100,0.5)" << std::endl;
	std::string input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);

	std::vector<std::string> tokens = tokenize(input, ',');
	if (tokens.size() != 3) {
		std::cout << "[OperationMain::enterAsk] Bad input! " << input << std::endl;
	} else {
		try { 
			OrderBookEntry obe = CSVReader::stringsToOBE(
				currentTime, 
				tokens[0], 
				OrderType::ask, 
				tokens[1], 
				tokens[2]
			);

			obe.setUsername("simuser");

			if (wallet.canFullfillOrder(obe)) {
				std::cout << "Wallet looks great." << std::endl;
				// std::cout << "Wallet before ask: " << wallet.toString() << std::endl;
				orderBook.insertOrder(obe);
			} else {
				std::cout << "Wallet has insufficient funds." << std::endl;
			}
		} catch (const std::exception& e) {
			std::cout << "[OperationMain::enterAsk] Bad input! " << e.what() << std::endl;
			return;
		}
		// std::cout << "You entered a valid ask: " << tokens[0] << ", " 
		// 		  << tokens[1] << ", " << tokens[2] << std::endl;
	}

	std::cout << "You typed: " << input << std::endl;
}

void OperationMain::enterBid() {
	std::cout << "Make a bid - enter the data: product, price, amount (e.g ETH/BTC,100,0.5)" << std::endl;
	std::string input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);

	std::vector<std::string> tokens = tokenize(input, ',');
	if (tokens.size() != 3) {
		std::cout << "[OperationMain::enterBid] Bad input! " << input << std::endl;
	} else {
		try { 
			OrderBookEntry obe = CSVReader::stringsToOBE(
				currentTime, 
				tokens[0], 
				OrderType::bid, 
				tokens[1], 
				tokens[2]
			);

			obe.setUsername("simuser");

			if (wallet.canFullfillOrder(obe)) {
				std::cout << "Wallet looks great." << std::endl;
				// std::cout << "Wallet before bid: " << wallet.toString() << std::endl;
				orderBook.insertOrder(obe);
			} else {
				std::cout << "Wallet has insufficient funds." << std::endl;
			}
		} catch (const std::exception& e) {
			std::cout << "[OperationMain::enterBid] Bad input! " << e.what() << std::endl;
			return;
		}
		// std::cout << "You entered a valid bid: " << tokens[0] << ", " 
		// 		  << tokens[1] << ", " << tokens[2] << std::endl;
	}

	std::cout << "You typed: " << input << std::endl;
}