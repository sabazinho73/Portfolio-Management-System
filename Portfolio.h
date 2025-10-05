// Portfolio.h

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Transaction.h"
#include "FinancialInstrument.h"
using namespace std;

// Portfolio class
class Portfolio
{
private:
    string owner;
    double cash;
    map<string, vector<Transaction>> transactions;
    map<string, FinancialInstrument *> holdings;

public:
    // Constructor
    Portfolio(string o, double c);

    // Add a financial instrument to holdings
    void addInstrument(FinancialInstrument *fi);

    // Function to update holdings
    void addTransaction(const Transaction &tr);

    // Function to calculate current total value of holdings
    double getCurrentValue();

    // Function to calculate total gain and loss
    double getTotalGainLoss();

    // Function to check if the portfolio contains a specific instrument
    bool hasInstrument(const string &symbol) const;

    // Function to update the current price of an instrument in holdings
    void updatePrice(const string &symbol, double newPrice);

    // Function to get the transaction history for a specific symbol
    vector<Transaction> getTransactionHistory(const string &symbol) const;
};