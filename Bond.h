// Bond.h

#pragma once

#include <iostream>
#include "FinancialInstrument.h"
using namespace std;

// Bond class derived from FinancialInstrument
class Bond : public FinancialInstrument
{
private:
    string maturity_date;
    double coupon; // Interest rate

public:
    // Constructor
    Bond(string ts, string n, double cp, int sq, string md, double coup);

    // Accessors
    string get_maturityDate();
    double get_coupon();

    // Mutators
    void set_maturityDate(string md);
    void set_coupon(double coup);

    // Pure virtual method from base class
    double price();
};