#pragma once

#include <iostream>
#include "Global.h"
#include "./important classes/clsUser.h"
#include "./libraries/clsDate.h"

using namespace std;

class clsScreen
{
protected:
  static void _DrawScreenHeader(string Title, string SubTitle = "", bool showDateAndUserName = true)
  {
    cout << "___________________________________________";
    cout << "\n\n  " << Title;
    if (SubTitle != "")
      cout << "\n  " << SubTitle;

    cout << "\n___________________________________________\n\n";

    if (showDateAndUserName)
    {
      cout << "User: " << CurrentUser.GetUserName() << endl;
      cout << "Date: " << clsDate::DateToString(clsDate()) << endl << endl;
    }
  }

  static bool CheckAccessRights(clsUser::enPermissions Permission)
  {
    if (!CurrentUser.CheckAccessPermission(Permission))
    {
      cout << "______________________________________";
      cout << "\n\n  Access Denied! Contact your Admin.";
      cout << "\n______________________________________\n\n";
      return false;
    }
    else
      return true;
  }
};
