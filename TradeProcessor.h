#ifndef TRADE_PROC_H
#define TRADE_PROC_H

#include <memory>
#include <iostream>
#include <mutex>

#include "MatchStrategy.h"

/**
 * A singleton processor class that handles trades using a specified matching strategy.
 */
template<typename Container>
class TradeProcessor {
private:
	static std::unique_ptr<TradeProcessor<Container>> instance;
    	static std::mutex mutex;
	std::unique_ptr<MatchStrategy<Container>> strategy;

	explicit TradeProcessor(std::unique_ptr<MatchStrategy<Container>> strategy);
	
public:	
	/**
     	* Retrieves the singleton instance of the TradeProcessor with a given strategy.
     	* If the processor is not already initialized, it initializes with the provided strategy.
     	* @param input_strategy The strategy to use for processing trades.
     	* @return Pointer to the singleton TradeProcessor.
     	*/
	static TradeProcessor<Container>* getInstance(std::unique_ptr<MatchStrategy<Container>> input_strategy);

	/**
     	* Adds a new trade to be processed according to the configured strategy.
     	* @param newTrade The trade to add.
     	*/
	void addTrade(Trade& newTrade);

	//Disable copying and assignment
	TradeProcessor(const TradeProcessor&) = delete;
    	TradeProcessor& operator=(const TradeProcessor&) = delete;

};

#endif
