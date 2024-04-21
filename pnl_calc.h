#ifndef PNL_CALC_H
#define PNL_CALC_H

#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <optional>

#include "trade_proc.h"

using namespace std;

optional<Trade> checkLine(const string& s); 
int processCsv(const filesystem::path& filePath, bool method); 
#endif
