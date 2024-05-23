#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../libraries/clsInputValidate.h"

#include "../transactions screen/clsDepositScreen.h"
#include "../transactions screen/clsWithdrawScreen.h"
#include "../transactions screen/clsTotalBalancesScreen.h"
#include "../transactions screen/clsTransferScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:
  enum enTransactionsMenuOptions
  {
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eTransfer = 4,
    eShowMainMenu = 5
  };

  static short ReadTransactionsMenuOption()
  {
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
    return Choice;
  }

  static void _ShowDepositScreen()
  {
    // cout << "\n Deposit Screen will be here.\n";
    clsDepositScreen::ShowDepositScreen();
  }

  static void _ShowWithdrawScreen()
  {
    // cout << "\n Withdraw Screen will be here.\n";
    clsWithdrawScreen::ShowWithdrawScreen();
  }

  static void _ShowTotalBalancesScreen()
  {
    // cout << "\n Balances Screen will be here.\n";
    clsTotalBalancesScreen::ShowTotalBalances();
  }

  static void _ShowTransferScreen()
  {
    // cout << "\n Transfer Screen will be here.\n";
    clsTransferScreen::ShowTransferScreen();
  }

  static void _GoBackToTransactionsMenu()
  {
    char Choice = 'y';
    cout << "\n\nPress key 'y' to go back to Transactions menu...";
    cin >> Choice;
    while (Choice != 'y')
    {
      cout << "\nPress key 'y' to go back to Transactions menu...";
      cin >> Choice;
    }
    ShowTransactionsMenu();
  }

  static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
  {
    switch (TransactionsMenuOption)
    {
    case enTransactionsMenuOptions::eDeposit:
    {
      system("clear");
      _ShowDepositScreen();
      _GoBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eWithdraw:
    {
      system("clear");
      _ShowWithdrawScreen();
      _GoBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eShowTotalBalance:
    {
      system("clear");
      _ShowTotalBalancesScreen();
      _GoBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eTransfer:
    {
      system("clear");
      _ShowTransferScreen();
      _GoBackToTransactionsMenu();
      break;
    }

    case enTransactionsMenuOptions::eShowMainMenu:
    {
      // do nothing here the main screen will handle it :-) ;
    }

    default:
      break;
    }
  }

public:
  static void ShowTransactionsMenu()
  {
    if (!CheckAccessRights(clsUser::enPermissions::pTransaction))
    {
      return; // this will exit the function and it will not continue
    }

    system("clear");
    _DrawScreenHeader("\t  Transactions Screen");

    cout << "===========================================\n";
    cout << "\t\t  Transactions Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Transfer.\n";
    cout << "\t[5] Main Menu.\n";
    cout << "===========================================\n";

    _PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
  }
};
