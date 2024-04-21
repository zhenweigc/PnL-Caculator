#include "pnl_calc.h"

optional<Trade> checkLine(const string& s) {
	istringstream iss(s);
        string token;
        vector<string> tokens;

        while (getline(iss, token, ',')) {
		tokens.push_back(token);
        }

        // Check if the number of fields is correct
        if (tokens.size() != 5) {
            	cerr << "Error: Malformed line with incorrect number of fields: " << s << endl;
            	return nullopt;
      	}

        int timestamp;
        string symbol;
        char type;
        double price;
        int quantity;
	optional<Trade> t = nullopt;

        try {
		timestamp = stoi(tokens[0]);
            	symbol = tokens[1];
            	type = tokens[2][0]; 
		// Either B or S
            	if (type != 'B' and type != 'S') return nullopt;
		
		price = stod(tokens[3]);
            	quantity = stoi(tokens[4]);

		//Ignore records with unreasonable trade amount/price
		if (price < 0 or quantity <= 0) return nullopt;
        } catch (const invalid_argument& e) {
		cerr << "Error: Invalid number format in line: " << s << endl;
		return nullopt;
        } catch (const out_of_range& e) {
		cerr << "Error: Number out of range in line: " << s << endl;
		return nullopt;
	}
	
	t = Trade(timestamp, symbol, type, price, quantity);
	return t;
}

int processCsv(const filesystem::path& filePath, bool method) {
	ifstream file(filePath);
	
	// Check if the file stream is successfully opened
    	if (!file.is_open()) {
		cerr << "Failed to open the file: " << filePath << endl;
		return 1;
	}
	
	string line;
	
	// Skip the header line
	getline(file, line);
	
	//Setting up strategy
	std::unique_ptr<MatchStrategy<std::deque<Trade>>> strategy;
	if (method) {
		strategy = std::make_unique<FIFO_Strategy>();
	} else {
		strategy = std::make_unique<LIFO_Strategy>();
	}
	TradeProcessor<std::deque<Trade>> tp(std::move(strategy));
	
	cout << "TIMESTAMP,SYMBOL,PNL" << endl;

    	while (getline(file, line)) {
		//cout << "Processing line: " << line << endl;	
		auto t = checkLine(line);

		//Continue if line malformed.
		if (!t) continue;

		tp.addTrade(*t);
		//cout << "good to go" << endl;
	}
	
	file.close();
    	return 0;
}



int main (int argc, char * argv[]) {
	
	/*
	 * basic sanity check on input arg num
	 */
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << "<file path> <fifo/lifo>" << endl;
		return 1;
	}

	filesystem::path fp = argv[1]; 
	string method = argv[2];
		
	/*
	 * checking if file pointed by the path exist or not.
	 */
	if ((!filesystem::exists(fp)) or (!filesystem::is_regular_file(fp)) or (fp.extension() != ".csv") ) {
		cerr << "Given path to the file does not exist, is not a file, or is not a CSV." << endl;
		return 1;
	}
	
	/*
	 * check if the method input is valid.
	 * Not case sensitive.
	 */
	if (method.length() != 4) {
		cerr << "Invalid accounting method. Choose 'fifo' or 'lifo'." << endl;
		return 1;
	}
	transform(method.begin(), method.end(), method.begin(), ::toupper);

	if (method != "FIFO" and method != "LIFO") {
		cerr << "Invalid accounting method. Choose 'fifo' or 'lifo'." << endl;
		return 1;
	}	
	
	/*
	 * End of basic checkings, start to parse through CSV.
	 */
		

	return processCsv(fp, method == "FIFO");
}
