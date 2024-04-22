# PnL-Caculator
## Overview
The PnL (Profit and Loss) Calculator is a tool designed to analyze trades and calculate the realized profit or loss using FIFO (First In, First Out) or LIFO (Last In, First Out) accounting methods. It processes a given CSV file containing trade data and outputs the results.

## Assumptions
- The input CSV file is formatted with the following columns: TIMESTAMP, SYMBOL, BUY_OR_SELL, PRICE, QUANTITY.
- Trades are listed in non-decreasing order by timestamp.
- For each symbol, the total quantity bought equals the total quantity sold by the end of the day.

### Environment
- C++17 compiler (e.g., g++)
- Make (for building the project using the provided Makefile)
- Linux and Valgrind(if the user would like to run the valgrind checking option)

## Design Patterns
- **Singleton Pattern**: Ensures a single instance of the trade processor throughout the application.
- **Strategy Pattern**: Allows the use and implememtation of different trade matching strategies easily.

### Compiling and Running the Program
1. Navigate to the project directory.
2. Run "make" to compile the program.
3. Run ./pnl_calculator <csv_file_address> <method> to run the program
4. Run "make clean" to clean object files and the executable.

### Miscellaneous
- Four test files are provided in the TestCases folder.
