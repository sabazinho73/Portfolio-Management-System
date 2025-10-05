// Stock.h

#pragma once

#include <iostream>
#include "FinancialInstrument.h"
using namespace std;

// Stock class derived from FinancialInstrument
class Stock : public FinancialInstrument
{
private:
    string sector;
    double dividend;

public:
    // Constructor
    Stock(string ts, string n, double cp, int sq, string sec, double divi);

    // Accessors
    string get_sector();
    double get_dividend();

    // Mutators
    void set_sector(string sec);
    void set_dividend(double divi);

    // Pure virtual method from base class
    double price();
};