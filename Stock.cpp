// Stock.cpp

#include "Stock.h"

// Constructor definition
Stock::Stock(string ts, string n, double cp, int sq, string sec, double divi)
    : FinancialInstrument(ts, n, cp, sq)
{
    sector = sec;
    dividend = divi;
}

// Accessors
string Stock::get_sector() { return sector; }
double Stock::get_dividend() { return dividend; }

// Mutators
void Stock::set_sector(string sec) { sector = sec; }
void Stock::set_dividend(double divi) { dividend = divi; }

// Pure virtual method from base class
double Stock::price()
{
    return get_currentPrice();
}