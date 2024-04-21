#ifndef TRADE_PROC_H
#define TRADE_PROC_H

#include <string>
#include <deque>
#include <stack>
#include <unordered_map>


struct Trade {
	//Encode each input record line into a struct.
	int time;
    	std::string symbol;
    	char type;
    	double price;
    	int quantity;
	
	Trade(int t, const std::string& s, char ty, double p, int q):
		time(t), symbol(s), type(ty), price(p), quantity(q) {}
};


class TradeProcessor {
	public:
		TradeProcessor(bool isFifo) : fifo(isFifo) {}
		~TradeProcessor() {}
		void addTrade(Trade& trade);
		void matchTrades(std::deque<Trade>& tradeQueue, Trade& newTrade);

	private:
		std::unordered_map<std::string, std::deque<Trade>> trades;
		bool fifo;  // True for FIFO, false for LIFO
};

#endif
