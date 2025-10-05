// Transaction.cpp

#include "Transaction.h"

// Constructor
Transaction::Transaction(string ts, double q, double p, bool b, string t)
{
    ticker_symbol = ts;
    quantity = q;
    price = p;
    buy = b;
    timestamp = t;
}

// Accessors
string Transaction::get_tickerSymbol() const { return ticker_symbol; }
double Transaction::get_quantity() const { return quantity; }
double Transaction::get_price() const { return price; }
bool Transaction::is_buy() const { return buy; }
string Transaction::get_timestamp() const { return timestamp; }

// Mutators
void Transaction::set_tickerSymbol(string ts) { ticker_symbol = ts; }
void Transaction::set_quantity(double q) { quantity = q; }
void Transaction::set_price(double p) { price = p; }
void Transaction::set_buy(bool b) { buy = b; }
void Transaction::set_timestamp(string t) { timestamp = t; }