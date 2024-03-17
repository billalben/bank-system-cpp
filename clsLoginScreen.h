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
  static bool _Login()
  {
    bool LoginFail = false;
    short FailedLoginCount = 0;

    string Username, Password;
    do
    {
      if (LoginFail)
      {
        FailedLoginCount++;
        cout << "\nInvalid Username/Password!\n";
        cout << "You have " << (3 - FailedLoginCount) << " trials to login.\n\n";

        if (FailedLoginCount == 3)
        {
          cout << "\nYou are locked after 3 failed trials.\n";
          return false;
        }
      }

      cout << "\nEnter Username? ";
      cin >> Username;

      cout << "Enter Password? ";
      cin >> Password;

      CurrentUser = clsUser::Find(Username, Password);

      LoginFail = CurrentUser.IsEmpty();

    } while (LoginFail);

    clsMainScreen::ShowMainMenu();
    return true;
  }

public:
  static bool ShowLoginScreen()
  {
    system("clear");
    _DrawScreenHeader("\t  Login Screen");
    return _Login();
  }
};
