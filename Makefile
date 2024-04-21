CXX = g++
CXXFLAGS = -Wall -g --std=c++17

TARGET = pnl_calc
OBJS = pnl_calc.o TradeProcessor.o FIFO_Strategy.o LIFO_Strategy.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

pnl_calc.o: pnl_calc.cpp
	$(CXX) $(CXXFLAGS) -c pnl_calc.cpp

TradeProcessor.o: TradeProcessor.cpp
	$(CXX) $(CXXFLAGS) -c TradeProcessor.cpp

FIFO_Strategy.o: FIFO_Strategy.cpp
	$(CXX) $(CXXFLAGS) -c FIFO_Strategy.cpp

LIFO_Strategy.o: LIFO_Strategy.cpp
	$(CXX) $(CXXFLAGS) -c LIFO_Strategy.cpp

.PHONY: clean
clean:
	rm -f *.o $(TARGET)

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test1.csv FIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test2.csv FIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test3.csv FIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test1.csv LIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test2.csv LIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test3.csv LIFO > /dev/null


.PHONY: all
all: clean $(TARGET)
