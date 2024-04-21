#include <deque>
#include "TradeProcessor.h"

template<typename Container>
TradeProcessor<Container>::TradeProcessor(std::unique_ptr<MatchStrategy<Container>> input_Strategy)
	: strategy(std::move(input_Strategy)) {}

template<typename Container>
void TradeProcessor<Container>::addTrade(Trade& newTrade) {
	if (strategy) {
		strategy->addTrade(newTrade);
	} else {
        	std::cerr << "TradeProcessor: Strategy not set!" << std::endl;
    	}
}

template class TradeProcessor<std::deque<Trade>>;
