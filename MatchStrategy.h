#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include "Trade.h"


/*
 * Abstract base class implementing the Strategy design pattern.
 * This class template allows for flexibility in the type of container,
 * as different strategies might need different data tpye when processing trades.
 */
template<typename Container>
class MatchStrategy {

public:
	virtual ~MatchStrategy() {}
    	
	/**
     	* Add a trade to the strategy-specific container.
     	*
     	* @param newTrade The trade to add to the strategy.
     	*/
	virtual void addTrade(Trade& newTrade) = 0;

	/**
     	* Match trades based on the strategy's criteria.
     	*
     	* @param trades The container of trades to process.
     	* @param newTrade The new trade to match against existing trades in the container.
     	*/
    	virtual void matchTrades(Container& trade, Trade& newTrade) = 0;
};
#endif
