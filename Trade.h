#ifndef TRADE_H
#define TRADE_H

#include<string>

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

#endif
