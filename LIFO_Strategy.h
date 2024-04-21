#ifndef LIFO_STRATEGY_H
#define LIFO_STRATEGY_H

#include "MatchStrategy.h"
#include <unordered_map>
#include <deque>

class LIFO_Strategy : public MatchStrategy<std::deque<Trade>> {

public:
	void addTrade(Trade& newTrade) override;
	void matchTrades(std::deque<Trade>& tradeQueue, Trade& newTrade) override;

private:
	std::unordered_map<std::string, std::deque<Trade>> trades;
};
#endif
