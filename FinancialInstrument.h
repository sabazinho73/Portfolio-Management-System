// FinancialInstrument.h

#pragma once

#include <iostream>
using namespace std;

class FinancialInstrument
{
private:
    string ticker_symbol;
    string name;
    double current_price;
    int shares_quantity;

public:
    // Constructor
    FinancialInstrument(string ts, string n, double cp, int sq);

    // Accessors
    string get_tickerSymbol();
    string get_name();
    double get_currentPrice();
    int get_sharesQuantity();

    // Mutators
    void set_tickerSymbol(string ts);
    void set_name(string n);
    void set_currentPrice(double cp);
    void set_sharesQuantity(int sq);

    // Pure virtual method to return price
    virtual double price() = 0;

    // Virtual destructor
    virtual ~FinancialInstrument();
};