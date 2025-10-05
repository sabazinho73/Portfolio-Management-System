// Portfolio.cpp

#include "Portfolio.h"
#include <numeric>
#include "CustomExceptions.h"
#include "InputValidator.h"

// Constructor definition
Portfolio::Portfolio(string o, double c)
{
    owner = o;
    cash = c;
}

// Add a financial instrument to holdings
void Portfolio::addInstrument(FinancialInstrument *fi)
{
    holdings[fi->get_tickerSymbol()] = fi;
}

// Function to update holdings
void Portfolio::addTransaction(const Transaction &tr)
{
    // Sanitize the symbol
    string symbol = InputValidator::sanitizeSymbol(tr.get_tickerSymbol());

    // If symbol is still invalid, throw an error
    if (symbol.empty())
    {
        throw InvalidSymbolException();
    }

    double qty = tr.get_quantity();
    double price = tr.get_price();
    bool isBuy = tr.is_buy();

    // Validate price
    if (!InputValidator::isValidPrice(price))
    {
        throw InvalidSymbolException();
    }

    // Record the transaction
    transactions[symbol].push_back(tr);

    // Calculate total cost of transaction
    double total = qty * price;

    if (isBuy)
    {
        // Check if there's enough cash
        if (cash < total)
        {
            double shortfall = total - cash;
            throw InsufficientFundsException(shortfall);
        }

        cash -= total;

        // If already owned, update quantity
        if (holdings.find(symbol) != holdings.end())
        {
            int newQty = holdings[symbol]->get_sharesQuantity() + qty;
            holdings[symbol]->set_sharesQuantity(newQty);
        }
    }
    else
    {
        // Before sell make sure symbol exists in the portfolio
        if (holdings.find(symbol) == holdings.end())
        {
            cout << "Symbol '" << symbol << "' not found in holdings!" << endl;
            cout << "Current holdings symbols:\n";
            for (const auto &pair : holdings)
            {
                cout << " - " << pair.first << endl;
            }
            throw InvalidSymbolException();
        }

        cash += total;
        int newQty = holdings[symbol]->get_sharesQuantity() - qty;
        holdings[symbol]->set_sharesQuantity(newQty);
    }
}

// Function to calculate current total value of holdings using STL accumulate
double Portfolio::getCurrentValue()
{
    return accumulate(
        holdings.begin(), holdings.end(), 0.0,
        [](double sum, const pair<string, FinancialInstrument *> &entry) { // Lambda function to calculate sum of each holding value
            return sum + entry.second->price() * entry.second->get_sharesQuantity();
        });
}

// Function to calculate total gain and loss
double Portfolio::getTotalGainLoss()
{
    double invested = 0.0;
    double currentValue = getCurrentValue();

    // Sum up all buy transaction costs and subtract income from sells
    for (auto &entry : transactions)
    {
        for (Transaction tr : entry.second)
        {
            if (tr.is_buy())
            {
                invested += tr.get_quantity() * tr.get_price();
            }
            else
            {
                invested -= tr.get_quantity() * tr.get_price();
            }
        }
    }

    return currentValue - invested;
}

// Function to check if the portfolio contains a specific instrument
bool Portfolio::hasInstrument(const string &symbol) const
{
    return holdings.find(symbol) != holdings.end();
}

// Function to update the current price of an instrument in holdings
void Portfolio::updatePrice(const string &symbol, double newPrice)
{
    if (holdings.find(symbol) != holdings.end())
    {
        holdings[symbol]->set_currentPrice(newPrice);
    }
}

// Function to get the transaction history for a specific symbol
vector<Transaction> Portfolio::getTransactionHistory(const string &symbol) const
{
    auto it = transactions.find(symbol);
    if (it != transactions.end())
    {
        return it->second;
    }
    return {};
}