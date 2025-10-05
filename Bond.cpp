// Bond.cpp

#include "Bond.h"

// Constructor
Bond::Bond(string ts, string n, double cp, int sq, string md, double coup)
    : FinancialInstrument(ts, n, cp, sq)
{
    maturity_date = md;
    coupon = coup;
}

// Accessors
string Bond::get_maturityDate() { return maturity_date; }
double Bond::get_coupon() { return coupon; }

// Mutators
void Bond::set_maturityDate(string md) { maturity_date = md; }
void Bond::set_coupon(double coup) { coupon = coup; }

// Pure virtual method from base class
double Bond::price()
{
    return get_currentPrice();
}