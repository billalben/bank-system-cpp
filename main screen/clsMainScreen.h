#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../libraries/clsInputValidate.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
  enum enMainMenuOptions
  {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenu = 6,
    eManageUsers = 7,
    eExit = 8
  };

  static short _ReadMainMenuOption()
  {
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = clsInputValidate::ReadNumberBetween<short>(1, 8, "Enter Number between 1 to 8? ");
    return Choice;
  }

  static void _GoBackToMainMenu()
  {
    char Choice = 'y';
    cout << "\n\nPress key 'y' to go back to main menu...";
    cin >> Choice;

    while (Choice != 'y')
    {
      cout << setw(37) << left << ""
           << "\nPress key 'y' to go back to main menu...";
      cin >> Choice;
    }

    ShowMainMenu();
  }

  static void _ShowAllClientsScreen()
  {
    cout << "\nClient List Screen Will be here...\n";
  }

  static void _ShowAddNewClientsScreen()
  {
    cout << "\nAdd New Client Screen Will be here...\n";
  }

  static void _ShowDeleteClientScreen()
  {
    cout << "\nDelete Client Screen Will be here...\n";
  }

  static void _ShowUpdateClientScreen()
  {
    cout << "\nUpdate Client Screen Will be here...\n";
  }

  static void _ShowFindClientScreen()
  {
    cout << "\nFind Client Screen Will be here...\n";
  }

  static void _ShowTransactionsMenu()
  {
    cout << "\nTransactions Menu Will be here...\n";
  }

  static void _ShowManageUsersMenu()
  {
    cout << "\nUsers Menu Will be here...\n";
  }

  static void _ShowEndScreen()
  {
    cout << "\nEnd Screen Will be here...\n";
  }

  static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
  {
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eListClients:
    {
      system("clear");
      _ShowAllClientsScreen();
      _GoBackToMainMenu();
      break;
    }
    case enMainMenuOptions::eAddNewClient:
      system("clear");
      _ShowAddNewClientsScreen();
      _GoBackToMainMenu();
      break;

    case enMainMenuOptions::eDeleteClient:
      system("clear");
      _ShowDeleteClientScreen();
      _GoBackToMainMenu();
      break;

    case enMainMenuOptions::eUpdateClient:
      system("clear");
      _ShowUpdateClientScreen();
      _GoBackToMainMenu();
      break;

    case enMainMenuOptions::eFindClient:
      system("clear");
      _ShowFindClientScreen();
      _GoBackToMainMenu();
      break;

    case enMainMenuOptions::eShowTransactionsMenu:
      system("clear");
      _ShowTransactionsMenu();
      break;

    case enMainMenuOptions::eManageUsers:
      system("clear");
      _ShowManageUsersMenu();
      break;

    case enMainMenuOptions::eExit:
      system("clear");
      _ShowEndScreen();
      // Login();

      break;
    }
  }

public:
  static void ShowMainMenu()
  {
    system("clear");
    _DrawScreenHeader("\t\tMain Screen");

    cout << "===========================================\n";
    cout << "\t\tMain Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    _PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
  }
};
