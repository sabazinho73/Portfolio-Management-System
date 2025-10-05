// DataManager.cpp

#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "InputValidator.h"
#include "CustomExceptions.h"
using namespace std;

// Load the stocks into a vector of stocks
vector<Stock *> DataManager::loadStocksFromCSV(string filename)
{
    vector<Stock *> stocks;
    ifstream file(filename);
    string line;

    // Check if file opened successfully
    if (!file.is_open())
    {
        cout << "Error: Could not open file: " << filename << endl;
        return stocks;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string no, symbol, name, marketCap, priceStr;

        // Read and sanitize symbol
        getline(ss, no, ',');
        getline(ss, symbol, ',');
        symbol = InputValidator::sanitizeSymbol(symbol);

        // If the symbol is empty, it's invalid
        if (symbol.empty())
        {
            cout << "Symbol is empty in line: " << line << endl;
            continue;
        }

        // Read the remaining fields
        getline(ss, name, ',');
        getline(ss, marketCap, ',');
        getline(ss, priceStr, ',');

        try
        {
            double price = stod(priceStr);

            // Skip if price is invalid
            if (!InputValidator::isValidPrice(price))
            {
                cout << "Invalid price for symbol " << symbol << ": " << price << endl;
                continue;
            }

            // Create stock object with default values
            Stock *stock = new Stock(symbol, name, price, 0, "Unknown", 0);
            stocks.push_back(stock);
        }
        catch (...)
        {
            cout << "Failed to parse line: " << line << endl;
            continue;
        }
    }

    file.close();
    return stocks;
}

// Load the bonds into a vector of bonds.
vector<Bond *> DataManager::loadBondsFromCSV(string filename)
{
    vector<Bond *> bonds;
    ifstream file(filename);
    string line;

    try
    {
        while (getline(file, line))
        {
            // Skip header or empty lines
            if (line.empty() || line.find("CUSIP") != string::npos)
            {
                continue;
            }

            stringstream ss(line);
            string no, symbol, name, couponStr, maturity, priceStr;

            // Read and sanitize symbol
            getline(ss, no, ',');
            getline(ss, symbol, ',');
            symbol = InputValidator::sanitizeSymbol(symbol);

            if (symbol.empty())
            {
                cout << "Empty symbol in line: " << line << endl;
                throw InvalidSymbolException();
            }

            // Read remaining fields
            getline(ss, name, ',');
            getline(ss, couponStr, ',');
            getline(ss, maturity, ',');
            getline(ss, priceStr, ',');

            try
            {
                double price = stod(priceStr) * 10;
                if (!InputValidator::isValidPrice(price))
                {
                    cout << "Invalid price for symbol " << symbol << ": " << price << endl;
                    throw InvalidSymbolException();
                }

                double coupon = stod(couponStr);

                // Create bond object with default quantity
                Bond *bond = new Bond(symbol, name, price, 0, maturity, coupon);
                bonds.push_back(bond);
            }
            catch (...)
            {
                cout << "Failed to parse bond line: " << line << endl;
                continue;
            }
        }
    }
    catch (const InvalidSymbolException &e)
    {
        cout << "Caught InvalidSymbolException while loading bond: " << e.what() << endl;
    }

    file.close();
    return bonds;
}