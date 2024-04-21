#include <deque>
#include "TradeProcessor.h"


template<typename Container>
std::unique_ptr<TradeProcessor<Container>> TradeProcessor<Container>::instance = nullptr;

template<typename Container>
std::mutex TradeProcessor<Container>::mutex;

template<typename Container>
TradeProcessor<Container>::TradeProcessor(std::unique_ptr<MatchStrategy<Container>> input_strategy)
        : strategy(std::move(input_strategy)) {} 


template<typename Container>
TradeProcessor<Container>* TradeProcessor<Container>::getInstance(std::unique_ptr<MatchStrategy<Container>> input_strategy) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
        instance = std::unique_ptr<TradeProcessor<Container>>(new TradeProcessor(std::move(input_strategy)));
    }
    return instance.get();
}

template<typename Container>
void TradeProcessor<Container>::addTrade(Trade& newTrade) {
	if (strategy) {
		strategy->addTrade(newTrade);
	} else {
        	std::cerr << "TradeProcessor: Strategy not set!" << std::endl;
    	}
}

template class TradeProcessor<std::deque<Trade>>;
