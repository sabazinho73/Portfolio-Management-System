// FinancialInstrument.cpp

#include "FinancialInstrument.h"

// Constructor
FinancialInstrument::FinancialInstrument(string ts, string n, double cp, int sq)
{
    ticker_symbol = ts;
    name = n;
    current_price = cp;
    shares_quantity = sq;
}

// Define accessors
string FinancialInstrument::get_tickerSymbol() { return ticker_symbol; }
string FinancialInstrument::get_name() { return name; }
double FinancialInstrument::get_currentPrice() { return current_price; }
int FinancialInstrument::get_sharesQuantity() { return shares_quantity; }

// Define mutators
void FinancialInstrument::set_tickerSymbol(string ts) { ticker_symbol = ts; }
void FinancialInstrument::set_name(string n) { name = n; }
void FinancialInstrument::set_currentPrice(double cp) { current_price = cp; }
void FinancialInstrument::set_sharesQuantity(int sq) { shares_quantity = sq; }

// Define virtual destructor
FinancialInstrument::~FinancialInstrument() {}