// DataManager.h

#pragma once

#include <vector>
#include "Stock.h"
#include "Bond.h"
using namespace std;

// DataManager class to implement file I/O operations for loading and saving data
class DataManager
{
public:
    // Load the stocks into a vector of stocks
    vector<Stock *> loadStocksFromCSV(string filename);

    //  Load the bonds into a vector of bonds.
    vector<Bond *> loadBondsFromCSV(string filename);
};