// Final Project CSC 211 - Saba Gergedava

#include "Bond.h"
#include "CustomExceptions.h"
#include "DataManager.h"
#include "FinancialInstrument.h"
#include "InputValidator.h"
#include "Portfolio.h"
#include "Stock.h"
#include "Transaction.h"
#include <iostream>
using namespace std;

int main() {

  try {
    cout << "----Creating portfolio for owner----" << endl;

    // Create portfolio for an owner
    Portfolio myPortfolio("Spongebob", 10000.0);
    cout << "Portfolio created for: Spongebob with $10,000 cash.\n";

    // Load all the stocks and bonds from Day1.
    cout << "\n----Loading Stocks and Bonds from Day 1----" << endl;
    DataManager dm;

    // Read stock data from file.
    vector<Stock *> stocksDay1 =
        dm.loadStocksFromCSV("S&P500Close.12May2025.txt");
    // Read bond data from file.
    vector<Bond *> bonds =
        dm.loadBondsFromCSV("Corporate.Aaa.AAA.19May2025.txt");

    // Display how many instruments were loaded
    cout << "Loaded " << stocksDay1.size() << " stocks from Day 1." << endl;
    cout << "Loaded " << bonds.size() << " bonds." << endl;

    // Add all Day 1 stocks and bonds to portfolio before making transactions
    for (Stock *s : stocksDay1) {
      myPortfolio.addInstrument(s);
    }

    for (Bond *b : bonds) {
      myPortfolio.addInstrument(b);
    }

    // Buy a mix of stocks and bonds to use most of the cash.
    cout << "\n----Buying Stocks and Bonds----" << endl;

    // Loop through Day 1 stocks and create buy transactions for specific stocks
    for (Stock *stock : stocksDay1) {
      string sym = stock->get_tickerSymbol();
      double price = stock->get_currentPrice();

      if (sym == "AAPL") {
        Transaction t1(sym, 5, price, true, "2025-05-12");
        myPortfolio.addTransaction(t1);
      }

      if (sym == "MSFT") {
        Transaction t2(sym, 4, price, true, "2025-05-12");
        myPortfolio.addTransaction(t2);
      }
    }

    // Buy 1 bond from bonds list
    if (!bonds.empty()) {
      string bondSymbol = bonds[0]->get_tickerSymbol();
      double bondPrice = bonds[0]->get_currentPrice();
      Transaction t3(bondSymbol, 1, bondPrice, true, "2025-05-12");
      myPortfolio.addTransaction(t3);
    }

    cout << "Transactions completed." << endl;

    // Compute the value of the holdings
    cout << "\n----Value of Holdings----" << endl;
    cout << "Value of Holdings: $" << myPortfolio.getCurrentValue() << endl;

    // Load all the stocks/bonds from Day2.
    cout << "\n----Load all the stocks/bonds from Day2----" << endl;
    vector<Stock *> stocksDay2 =
        dm.loadStocksFromCSV("S&P500Close.13May2025.txt");
    vector<Bond *> bondsDay2 =
        dm.loadBondsFromCSV("Corporate.Aaa.AAA.19May2025.txt");

    cout << "Loaded " << stocksDay2.size() << " stocks from Day 2." << endl;
    cout << "Loaded " << bondsDay2.size() << " bonds." << endl;

    // Update the prices of stocks in the portfolio using Day 2 data
    for (Stock *updatedStock : stocksDay2) {
      string symbol = updatedStock->get_tickerSymbol();
      if (myPortfolio.hasInstrument(symbol)) {
        myPortfolio.updatePrice(symbol, updatedStock->get_currentPrice());
      }
    }

    for (Bond *updatedBond : bondsDay2) {
      string symbol = updatedBond->get_tickerSymbol();
      if (myPortfolio.hasInstrument(symbol)) {
        myPortfolio.updatePrice(symbol, updatedBond->get_currentPrice());
      }
    }

    // Compute the gains/loss for holdings.
    cout << "\n----Gains/loss for holdings----" << endl;
    cout << "Total Gain/Loss: $" << myPortfolio.getTotalGainLoss() << endl;

    // Sell at least one stock and one bond, then buy at least one of each
    cout << "\n----Sell and Buy Transactions----" << endl;
    try {
      // Sell 2 AAPL
      Transaction sellAAPL("AAPL", 2, 212.00, false,
                           "2025-05-13"); // Use Day 2 price
      myPortfolio.addTransaction(sellAAPL);
      cout << "Sold 2 shares of AAPL.\n";

      // Sell 1 bond
      if (!bondsDay2.empty()) {
        string bondSymbol = bondsDay2[0]->get_tickerSymbol();
        double bondPrice = bondsDay2[0]->get_currentPrice();
        Transaction sellBond(bondSymbol, 1, bondPrice, false, "2025-05-13");
        myPortfolio.addTransaction(sellBond);
        cout << "Sold 1 bond: " << bondSymbol << "\n";
      }

      // Buy 2 NFLX
      for (Stock *s : stocksDay2) {
        if (s->get_tickerSymbol() == "NFLX") {
          Transaction buyNFLX("NFLX", 2, s->get_currentPrice(), true,
                              "2025-05-13");
          myPortfolio.addTransaction(buyNFLX);
          cout << "Bought 2 shares of NFLX.\n";
          break;
        }
      }

      // Buy 1 new bond
      if (bondsDay2.size() > 1) {
        string newBondSymbol = bondsDay2[1]->get_tickerSymbol();
        double newBondPrice = bondsDay2[1]->get_currentPrice();
        Transaction buyBond(newBondSymbol, 1, newBondPrice, true, "2025-05-13");
        myPortfolio.addTransaction(buyBond);
        cout << "Bought 1 bond: " << newBondSymbol << "\n";
      }

      // Catch any unexpected errors during the transaction process
    } catch (const exception &e) {
      cout << "Error during sell/buy transactions: " << e.what() << endl;
    }

    // Load all the stocks/bonds from Day3.
    cout << "\n----Load all the stocks/bonds from Day3----" << endl;

    // Read Day 3 data from files
    vector<Stock *> stocksDay3 =
        dm.loadStocksFromCSV("S&P500Close.14May2025.txt");
    vector<Bond *> bondsDay3 =
        dm.loadBondsFromCSV("Corporate.Aaa.AAA.19May2025.txt");

    cout << "Loaded " << stocksDay3.size() << " stocks from Day 3." << endl;
    cout << "Loaded " << bondsDay3.size() << " bonds." << endl;

    // Update the prices in portfolio using Day 3 data
    for (Stock *updatedStock : stocksDay3) {
      string symbol = updatedStock->get_tickerSymbol();
      if (myPortfolio.hasInstrument(symbol)) {
        myPortfolio.updatePrice(symbol, updatedStock->get_currentPrice());
      }
    }

    for (Bond *updatedBond : bondsDay3) {
      string symbol = updatedBond->get_tickerSymbol();
      if (myPortfolio.hasInstrument(symbol)) {
        myPortfolio.updatePrice(symbol, updatedBond->get_currentPrice());
      }
    }

    // Compute the value of the holdings.
    cout << "\n----Value of Holdings After Day 3----" << endl;
    cout << "Value of Holdings: $" << myPortfolio.getCurrentValue() << endl;

    // Compute the gains/loss for holdings.
    cout << "\n----Gains/Loss for Holdings After Day 3----" << endl;
    cout << "Total Gain/Loss: $" << myPortfolio.getTotalGainLoss() << endl;

    // BONUS: Find the stock with the highest gain in dollars and report the
    // gain just for that stock.
    cout << "\n----BONUS: Stock with Highest Dollar Gain----" << endl;

    string bestStockSymbol;
    double maxGain = -1;

    // Loop through Day 3 stock data to compute gains
    for (const auto &pair : stocksDay3) {
      string symbol = pair->get_tickerSymbol();

      // Skip stocks not currently held in the portfolio
      if (!myPortfolio.hasInstrument(symbol))
        continue;

      double currentPrice = pair->get_currentPrice();
      double totalGain = 0;

      for (const Transaction &tr : myPortfolio.getTransactionHistory(symbol)) {
        if (tr.is_buy()) {
          totalGain += (currentPrice - tr.get_price()) * tr.get_quantity();
        }
      }

      // Track the stock with the highest dollar gain
      if (totalGain > maxGain) {
        maxGain = totalGain;
        bestStockSymbol = symbol;
      }
    }

    // Output result
    if (!bestStockSymbol.empty()) {
      cout << "Stock with highest dollar gain: " << bestStockSymbol << endl;
      cout << "Dollar gain: $" << maxGain << endl;
    } else {
      cout << "No stock gains found." << endl;
    }

    // BONUS: Find the stock with the biggest loss in dollars and report the
    // loss just for that stock.
    cout << "\n----BONUS: Stock with Highest Dollar Loss----" << endl;

    string worstStockSymbol;
    double maxLoss = 0;

    // Loop through all stock data to compare prices
    for (const auto &pair : stocksDay3) {
      string symbol = pair->get_tickerSymbol();

      if (!myPortfolio.hasInstrument(symbol))
        continue;

      double currentPrice = pair->get_currentPrice();
      double totalLoss = 0;

      // Calculate total loss across all buy transactions for this stock
      for (const Transaction &tr : myPortfolio.getTransactionHistory(symbol)) {
        if (tr.is_buy()) {
          totalLoss += (currentPrice - tr.get_price()) * tr.get_quantity();
        }
      }

      // Track the stock with the worst loss so far
      if (totalLoss < maxLoss) {
        maxLoss = totalLoss;
        worstStockSymbol = symbol;
      }
    }

    // Output result
    if (!worstStockSymbol.empty()) {
      cout << "Stock with highest dollar loss: " << worstStockSymbol << endl;
      cout << "Dollar loss: $" << abs(maxLoss) << endl;
    } else {
      cout << "No stock losses found." << endl;
    }

    // Throw an exception test
    cout << "\n----Exception Test----" << endl;

    // Create a transaction with an invalid symbol
    // This should trigger an InvalidSymbolException due to sanitization failure
    try {
      Transaction bad("!!!", 10, 100.0, true, "2025-05-14");
      myPortfolio.addTransaction(bad);
    } catch (const InvalidSymbolException &e) {
      cout << "Caught expected exception: " << e.what() << endl;
    }
  }

  // General catch blocks
  catch (const out_of_range &e) {
    cout << "Caught out_of_range: " << e.what() << endl;
  } catch (const exception &e) {
    cout << "Caught exception: " << e.what() << endl;
  } catch (...) {
    cout << "Caught unknown exception." << endl;
  }

  return 0;
}