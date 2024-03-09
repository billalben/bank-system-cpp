#pragma once

#include <iostream>
#include <iomanip>

#include "clsScreen.h"
#include "Global.h"
#include "./important classes/clsUser.h"
#include "./main screen/clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
  static void _Login()
  {
    bool LoginFail = false;

    string Username, Password;
    do
    {
      if (LoginFail)
        cout << "\nInvalid Username/Password!\n\n";

      cout << "Enter Username? ";
      cin >> Username;

      cout << "Enter Password? ";
      cin >> Password;

      CurrentUser = clsUser::Find(Username, Password);

      LoginFail = CurrentUser.IsEmpty();

    } while (LoginFail);

    clsMainScreen::ShowMainMenu();
  }

public:
  static void ShowLoginScreen()
  {
    system("clear");
    _DrawScreenHeader("\t  Login Screen");
    _Login();
  }
};
