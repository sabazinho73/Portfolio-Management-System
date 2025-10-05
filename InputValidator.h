// BONUS: InputValidator.h

#pragma once

#include <string>
#include <algorithm>
using namespace std;

// InputValidator class for input sanitization
class InputValidator
{
public:
    // Static method to clean and standardize ticker symbols
    static string sanitizeSymbol(string symbol)
    {
        // Remove non-alphanumeric characters
        symbol.erase(
            remove_if(symbol.begin(), symbol.end(),
                      [](char c)
                      { return !isalnum(c); }),
            symbol.end());

        // Convert to uppercase
        transform(symbol.begin(), symbol.end(), symbol.begin(),
                  [](unsigned char c)
                  { return toupper(c); });

        return symbol;
    }

    // Check if a price is valid
    static bool isValidPrice(double price)
    {
        return price >= 0 && price <= 10000;
    }

    // Check if bond purchase is between $0 and $10,000
    static bool isValidBondPurchase(int quantity, double price)
    {
        double total = quantity * 1000 * price;
        return total <= 10000 && total >= 0;
    }
};