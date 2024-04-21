#include "trade_proc.h"
#include <iostream>
#include <iomanip>

void TradeProcessor::addTrade(Trade& newTrade) {
	std::deque<Trade>& tradeQueue = this->trades[newTrade.symbol];
	/*
	 * Check if there are opposite trades to match against
	 * Opposite trades refers to neighboring trade pairs with different type, which is either Buy-Sell or Sell-Buy.
	 * Recall that we will use a deque is act as a stack or a queue, depending on the situation.
	 * Thus we have to peek differently upon condition.
	 */	
	bool matchingPairs = this->fifo ?
        (!tradeQueue.empty() && tradeQueue.front().type != newTrade.type) :
        (!tradeQueue.empty() && tradeQueue.back().type != newTrade.type);

	if (matchingPairs) matchTrades(tradeQueue, newTrade);	
    	// If the new trade still has quantity left after trying to match, add it to the deque
    	if (newTrade.quantity > 0) {
		tradeQueue.push_back(newTrade);
	}
}

void TradeProcessor::matchTrades(std::deque<Trade>& tradeQueue, Trade& newTrade) {
    	double totalProfit = 0.0;

    	while (!tradeQueue.empty() && newTrade.quantity > 0) {
        	Trade& existingTrade = this->fifo ? tradeQueue.front() : tradeQueue.back();

            	int matchQuantity = std::min(existingTrade.quantity, newTrade.quantity);

		double profit = matchQuantity * (newTrade.price - existingTrade.price);
            	if (newTrade.type == 'B') {
                	profit *= -1; // Flip the sign if the new Trade is a buy order.
            	}

            	/*
		 * Adding up profits and updating quantities.
		 */
		totalProfit += profit;
            	existingTrade.quantity -= matchQuantity;
            	newTrade.quantity -= matchQuantity;

		//std::cout << "Quantity of new Trade is now " << newTrade.quantity << std::endl;
		//std::cout << "Quantity of existing Trade is now " << existingTrade.quantity << std::endl;

		//Check if the new trade order is fulfilled by existed orders in the deque.
            	if (existingTrade.quantity == 0) {
                	this->fifo ? tradeQueue.pop_front() : tradeQueue.pop_back();
			//std::cout << "popped, the size now is " << tradeQueue.size() << std::endl;
            	}

            	// Continue matching if the new trade is not yet fully matched
    	}

        std::cout << newTrade.time << "," << newTrade.symbol << "," << std::fixed << std::setprecision(2) << totalProfit << std::endl ;
}
