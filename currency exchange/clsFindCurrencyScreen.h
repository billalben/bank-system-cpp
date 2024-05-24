#pragma once

#include <iostream>

#include "../clsScreen.h"
#include "../important classes/clsCurrency.h"
#include "../libraries/clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{

private:
  static void _PrintCurrency(clsCurrency Currency)
  {
    cout << "\nCurrency Card:\n";
    cout << "_____________________________\n";
    cout << "\nCountry    : " << Currency.Country();
    cout << "\nCode       : " << Currency.CurrencyCode();
    cout << "\nName       : " << Currency.CurrencyName();
    cout << "\nRate(1$) = : " << Currency.Rate();
    cout << "\n_____________________________\n";
  }

  static void _ShowResults(clsCurrency Currency)
  {
    if (!Currency.IsEmpty())
    {
      cout << "\nCurrency Found :-)\n";
      _PrintCurrency(Currency);
    }
    else
    {
      cout << "\nCurrency Was not Found :-(\n";
    }
  }

public:
  static void ShowFindCurrencyScreen()
  {
    _DrawScreenHeader("\t  Find Currency Screen");

    short Answer = 1;
    cout << "\nFind By: [1] Code or [2] Country ? ";
    cin >> Answer;

    if (Answer == 1)
    {
      string CurrencyCode;
      cout << "\nPlease Enter CurrencyCode: ";
      CurrencyCode = clsInputValidate::ReadString();
      clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
      _ShowResults(Currency);
    }
    else
    {
      string Country;
      cout << "\nPlease Enter Country Name: ";
      Country = clsInputValidate::ReadString();
      clsCurrency Currency = clsCurrency::FindByCountry(Country);
      _ShowResults(Currency);
    }
  }
};
