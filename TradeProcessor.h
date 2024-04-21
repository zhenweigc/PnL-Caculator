#ifndef TRADE_PROC_H
#define TRADE_PROC_H

#include <memory>
#include <iostream>

#include "MatchStrategy.h"

template<typename Container>
class TradeProcessor {
private:
	std::unique_ptr<MatchStrategy<Container>> strategy;

public:	
	explicit TradeProcessor(std::unique_ptr<MatchStrategy<Container>> strategy);
	void addTrade(Trade& newTrade);
};

#endif
