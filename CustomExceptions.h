// CustomExceptions.h

#pragma once

#include <exception>
#include <string>
using namespace std;

// Throw this exception if an invalid symbol is entered
class InvalidSymbolException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Error: Invalid symbol. This symbol is not found in portfolio.";
    }
};

// Throw if the owner tries to buy more than they have in their available cash
class InsufficientFundsException : public exception
{
private:
    double shortfall;

public:
    // Constructor stores how much money is missing
    InsufficientFundsException(double needed)
    {
        shortfall = needed;
    }

    const char *what() const noexcept override
    {
        return "Error: Insufficient funds for this transaction.";
    }

    double getShortfall() const
    {
        return shortfall;
    }
};