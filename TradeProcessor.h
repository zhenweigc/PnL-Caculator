#ifndef TRADE_PROC_H
#define TRADE_PROC_H

#include <memory>
#include <iostream>
#include <mutex>

#include "MatchStrategy.h"

template<typename Container>
class TradeProcessor {
private:
	static std::unique_ptr<TradeProcessor<Container>> instance;
    	static std::mutex mutex;
	std::unique_ptr<MatchStrategy<Container>> strategy;

	explicit TradeProcessor(std::unique_ptr<MatchStrategy<Container>> strategy);
	
public:	

	static TradeProcessor<Container>* getInstance(std::unique_ptr<MatchStrategy<Container>> input_strategy);

	void addTrade(Trade& newTrade);
	TradeProcessor(const TradeProcessor&) = delete;
    	TradeProcessor& operator=(const TradeProcessor&) = delete;



};

#endif
