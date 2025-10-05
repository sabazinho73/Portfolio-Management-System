# Portfolio Management System

A C++ application for managing financial portfolios with stocks and bonds.

## Features

- Create and manage investment portfolios
- Support for stocks and bonds
- Load market data from CSV files
- Execute buy/sell transactions
- Track portfolio value over multiple days
- Price updates from historical market data

## Files Structure

- **FinancialInstrument**: Base class for financial instruments
- **Stock/Bond**: Specific instrument types inheriting from FinancialInstrument
- **Portfolio**: Manages holdings, transactions, and cash
- **Transaction**: Records buy/sell operations
- **DataManager**: Loads market data from CSV files
- **CustomExceptions**: Error handling
- **InputValidator**: Input validation utilities

## Sample Data

Includes S&P 500 stock data and corporate bond data for testing:

- `S&P500Close.12May2025.txt` - Stock prices Day 1
- `S&P500Close.13May2025.txt` - Stock prices Day 2
- `S&P500Close.14May2025.txt` - Stock prices Day 3
- `Corporate.Aaa.AAA.19May2025.txt` - Bond data

## How to Run

```bash
g++ -o main *.cpp
./main
```

## Example Usage

The program demonstrates:

1. Creating a portfolio with initial cash
2. Loading stocks and bonds from data files
3. Executing sample transactions (AAPL, MSFT stocks + bonds)
4. Updating prices with new market data
5. Calculating portfolio value changes over time

---

_CSC 211 Final Project_
