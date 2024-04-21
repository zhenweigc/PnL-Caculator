#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include "Trade.h"

template<typename Container>
class MatchStrategy {

public:
	virtual ~MatchStrategy() {}
    	virtual void addTrade(Trade& newTrade) = 0;
    	virtual void matchTrades(Container& trade, Trade& newTrade) = 0;
};
#endif
