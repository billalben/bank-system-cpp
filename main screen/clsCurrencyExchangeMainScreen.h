#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../libraries/clsInputValidate.h"
#include "../currency exchange/clsCurrenciesListScreen.h"
#include "../currency exchange/clsFindCurrencyScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{

private:
  enum enCurrenciesMainMenuOptions
  {
    eListCurrencies = 1,
    eFindCurrency = 2,
    eUpdateCurrencyRate = 3,
    eCurrencyCalculator = 4,
    eMainMenu = 5
  };

  static short ReadCurrenciesMainMenuOptions()
  {
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
    return Choice;
  }

  static void _GoBackToCurrenciesMenu()
  {
    char Choice = 'y';
    cout << "\n\nPress key 'y' to go back to main menu...";
    cin >> Choice;
    while (Choice != 'y')
    {
      cout << setw(37) << left << "" << "\nPress key 'y' to go back to main menu...";
      cin >> Choice;
    }
    ShowCurrenciesMenu();
  }

  static void _ShowCurrenciesListScreen()
  {
    // cout << "\nCurrencies List Screen Will Be Here.\n";
    clsCurrenciesListScreen::ShowCurrenciesListScreen();
  }

  static void _ShowFindCurrencyScreen()
  {
    // cout << "\nFind Currency Screen Will Be Here.\n";
    clsFindCurrencyScreen::ShowFindCurrencyScreen();
  }

  static void _ShowUpdateCurrencyRateScreen()
  {
    cout << "\nUpdate Currency Rate Screen Will Be Here.\n";
  }

  static void _ShowCurrencyCalculatorScreen()
  {
    cout << "\nCurrency Calculator Screen Will Be Here.\n";
  }

  static void _PerformCurrenciesMainMenuOptions(enCurrenciesMainMenuOptions CurrenciesMainMenuOptions)
  {
    switch (CurrenciesMainMenuOptions)
    {
    case enCurrenciesMainMenuOptions::eListCurrencies:
    {
      system("clear");
      _ShowCurrenciesListScreen();
      _GoBackToCurrenciesMenu();
      break;
    }

    case enCurrenciesMainMenuOptions::eFindCurrency:
    {
      system("clear");
      _ShowFindCurrencyScreen();
      _GoBackToCurrenciesMenu();
      break;
    }

    case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
    {
      system("clear");
      _ShowUpdateCurrencyRateScreen();
      _GoBackToCurrenciesMenu();
      break;
    }

    case enCurrenciesMainMenuOptions::eCurrencyCalculator:
    {
      system("clear");
      _ShowCurrencyCalculatorScreen();
      _GoBackToCurrenciesMenu();
      break;
    }

    case enCurrenciesMainMenuOptions::eMainMenu:
    {
      // do nothing here the main screen will handle it :-) ;
    }
    }
  }

public:
  static void ShowCurrenciesMenu()
  {
    system("clear");
    _DrawScreenHeader("    Currency Exchange Main Screen");

    cout << "===========================================\n";
    cout << "\t  Currency Exchange Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] List Currencies.\n";
    cout << "\t[2] Find Currency.\n";
    cout << "\t[3] Update Rate.\n";
    cout << "\t[4] Currency Calculator.\n";
    cout << "\t[5] Main Menu.\n";
    cout << "===========================================\n";

    _PerformCurrenciesMainMenuOptions((enCurrenciesMainMenuOptions)ReadCurrenciesMainMenuOptions());
  }
};
