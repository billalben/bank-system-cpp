#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../libraries/clsInputValidate.h"
#include "../manage users screen/clsUsersListScreen.h"
#include "../manage users screen/clsAddNewUserScreen.h"
#include "../manage users screen/clsDeleteUserScreen.h"
#include "../manage users screen/clsUpdateUserScreen.h"
#include "../manage users screen/clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
  enum enManageUsersMenuOptions
  {
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
  };

  static short ReadManageUsersMenuOption()
  {
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
    return Choice;
  }

  static void _GoBackToManageUsersMenu()
  {
    char Choice = 'y';
    cout << "\n\nPress key 'y' to go back to Manage Users menu... ";
    cin >> Choice;
    Choice = tolower(Choice);

    while (Choice != 'y')
    {
      cout << setw(37) << left << ""
           << "\nPress key 'y' to go back to Manage Users menu... ";
      cin >> Choice;
    }
    ShowManageUsersMenu();
  }

  static void _ShowListUsersScreen()
  {
    // cout << "\nList Users Screen Will Be Here.\n";
    clsListUsersScreen::ShowUsersList();
  }

  static void _ShowAddNewUserScreen()
  {
    // cout << "\nAdd New User Screen Will Be Here.\n";
    clsAddNewUserScreen::ShowAddNewUserScreen();
  }

  static void _ShowDeleteUserScreen()
  {
    // cout << "\nDelete User Screen Will Be Here.\n";
    clsDeleteUserScreen::ShowDeleteUserScreen();
  }

  static void _ShowUpdateUserScreen()
  {
    // cout << "\nUpdate User Screen Will Be Here.\n";
    clsUpdateUserScreen::ShowUpdateUserScreen();
  }

  static void _ShowFindUserScreen()
  {
    // cout << "\nFind User Screen Will Be Here.\n";
    clsFindUserScreen::ShowFindUserScreen();
  }

  static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
  {
    switch (ManageUsersMenuOption)
    {
    case enManageUsersMenuOptions::eListUsers:
    {
      system("clear");
      _ShowListUsersScreen();
      _GoBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eAddNewUser:
    {
      system("clear");
      _ShowAddNewUserScreen();
      _GoBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eDeleteUser:
    {
      system("clear");
      _ShowDeleteUserScreen();
      _GoBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eUpdateUser:
    {
      system("clear");
      _ShowUpdateUserScreen();
      _GoBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eFindUser:
    {
      system("clear");

      _ShowFindUserScreen();
      _GoBackToManageUsersMenu();
      break;
    }

    case enManageUsersMenuOptions::eMainMenu:
    {
      // do nothing here the main screen will handle it :-) ;
    }
    }
  }

public:
  static void ShowManageUsersMenu()
  {
    system("clear");
    _DrawScreenHeader("\t Manage Users Screen");

    cout << "===========================================\n";
    cout << "\t  Manage Users Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";

    _PerformManageUsersMenuOption((enManageUsersMenuOptions)ReadManageUsersMenuOption());
  }
};
