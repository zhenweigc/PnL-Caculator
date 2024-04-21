CXX = g++
CXXFLAGS = -Wall -g

TARGET = pnl_calc
OBJS = pnl_calc.o trade_proc.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

pnl_calc.o: pnl_calc.cpp
	$(CXX) $(CXXFLAGS) -c pnl_calc.cpp

trade_proc.o: trade_proc.cpp
	$(CXX) $(CXXFLAGS) -c trade_proc.cpp

.PHONY: clean
clean:
	rm -f *.o $(TARGET)

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test1.csv FIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test2.csv FIFO > /dev/null
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) TestCases/test3.csv FIFO > /dev/null

.PHONY: all
all: clean $(TARGET)


