#include "FIFO_Strategy.h"

#include <iostream>
#include <iomanip>

void FIFO_Strategy::addTrade(Trade& newTrade) {
	std::deque<Trade>& tradeQueue = this->trades[newTrade.symbol];
	/*
	 * Check if there are opposite trades to match against
	 * Opposite trades refers to neighboring trade pairs with different type, which is either Buy-Sell or Sell-Buy.
	 * Check its front since it is FIFO.
	 */	
	bool matchingPairs = (!tradeQueue.empty()) && tradeQueue.front().type != newTrade.type;
	
	if (matchingPairs) matchTrades(tradeQueue, newTrade);	
    	
	// If the new trade still has quantity left after trying to match, add it to the deque
    	if (newTrade.quantity > 0) {
		tradeQueue.push_back(newTrade);
	}
}

void FIFO_Strategy::matchTrades(std::deque<Trade>& tradeQueue, Trade& newTrade) {
    	double totalProfit = 0.0;

    	while (!tradeQueue.empty() && newTrade.quantity > 0) {
        	Trade& existingTrade = tradeQueue.front();

            	int matchQuantity = std::min(existingTrade.quantity, newTrade.quantity);

		double profit = matchQuantity * (newTrade.price - existingTrade.price);
            	if (newTrade.type == 'B') {
                	profit *= -1; // Flip the sign if the new Trade is a buy order.
            	}

		// Adding up profits and updating quantities.
		totalProfit += profit;
            	existingTrade.quantity -= matchQuantity;
            	newTrade.quantity -= matchQuantity;

		//Check if the new trade order is fulfilled by existed orders in the deque.
            	if (existingTrade.quantity == 0) tradeQueue.pop_front();
    	}

        std::cout << newTrade.time << "," << newTrade.symbol << "," << std::fixed << std::setprecision(2) << totalProfit << std::endl ;
}
