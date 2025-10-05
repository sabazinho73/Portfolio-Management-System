// Transaction.h

#pragma once

#include <iostream>
using namespace std;

// Transaction class
class Transaction
{
private:
    string ticker_symbol;
    double quantity;
    double price;
    bool buy;
    string timestamp; // Timestamp of the transaction

public:
    // Constructor
    Transaction(string ts, double q, double p, bool b, string t);

    // Accessors
    string get_tickerSymbol() const;
    double get_quantity() const;
    double get_price() const;
    bool is_buy() const;
    string get_timestamp() const;

    // Mutators
    void set_tickerSymbol(string ts);
    void set_quantity(double q);
    void set_price(double p);
    void set_buy(bool b);
    void set_timestamp(string t);
};