#ifndef LIFO_STRATEGY_H
#define LIFO_STRATEGY_H

#include "MatchStrategy.h"

#include <unordered_map>
#include <deque>


/**
 * Implementts the First-in-last-out Strategy.
 * In charge of adding, storing all trades, and computing profits
 */
class LIFO_Strategy : public MatchStrategy<std::deque<Trade>> {

public:
	void addTrade(Trade& newTrade) override;
	void matchTrades(std::deque<Trade>& tradeQueue, Trade& newTrade) override;

private:
	/*
	 * Uses an unordered map to store deques which correspond to stocks
	 * Trades of each stock will be pushed to the unique corresponding deque
	 * Uses deque because deque can also function as a stack
	 */
	std::unordered_map<std::string, std::deque<Trade>> trades;
};
#endif
