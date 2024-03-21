#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsPerson.h"
#include "../libraries/clsString.h"
#include "../libraries/clsDate.h"

using namespace std;

class clsUser : public clsPerson
{
private:
  enum enMode
  {
    EmptyMode = 0,
    UpdateMode = 1,
    AddNewMode = 2
  };
  enMode _Mode;
  string _UserName;
  string _Password;
  int _Permissions;

  bool _MarkedForDelete = false;

  string _PrepareLogInRecord(string Separator = "#//#")
  {
    string LoginRecord = "";
    LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
    LoginRecord += GetUserName() + Separator;
    LoginRecord += GetPassword() + Separator;
    LoginRecord += to_string(GetPermissions());
    return LoginRecord;
  }

  static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
  {
    vector<string> vUserData;
    vUserData = clsString::Split(Line, Separator);

    return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                   vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
  }

  static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
  {
    string UserRecord = "";
    UserRecord += User.GetFirstName() + Separator;
    UserRecord += User.GetLastName() + Separator;
    UserRecord += User.GetEmail() + Separator;
    UserRecord += User.GetPhone() + Separator;
    UserRecord += User.GetUserName() + Separator;
    UserRecord += User.GetPassword() + Separator;
    UserRecord += to_string(User.GetPermissions());

    return UserRecord;
  }

  static vector<clsUser> _LoadUsersDataFromFile()
  {
    vector<clsUser> vUsers;

    fstream MyFile;
    MyFile.open("Users.txt", ios::in); // read Mode

    if (MyFile.is_open())
    {
      string Line;

      while (getline(MyFile, Line))
      {
        clsUser User = _ConvertLineToUserObject(Line);
        vUsers.push_back(User);
      }
      MyFile.close();
    }
    return vUsers;
  }

  static void _SaveUsersDataToFile(vector<clsUser> vUsers)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
      for (clsUser U : vUsers)
      {
        if (U.MarkedForDeleted() == false)
        {
          // we only write records that are not marked for delete.
          DataLine = _ConvertUserObjectToLine(U);
          MyFile << DataLine << endl;
        }
      }
      MyFile.close();
    }
  }

  void _Update()
  {
    vector<clsUser> _vUsers;
    _vUsers = _LoadUsersDataFromFile();

    for (clsUser &U : _vUsers)
    {
      if (U.GetUserName() == _UserName)
      {
        U = *this;
        break;
      }
    }
    _SaveUsersDataToFile(_vUsers);
  }

  void _AddNew()
  {
    _AddDataLineToFile(_ConvertUserObjectToLine(*this));
  }

  void _AddDataLineToFile(string stDataLine)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::out | ios::app);

    if (MyFile.is_open())
    {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

  static clsUser _GetEmptyUserObject()
  {
    return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
  }

public:
  enum enPermissions
  {
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTransaction = 32,
    pManageUsers = 64
  };

  struct stLoginRegisterRecord
  {
    string DateTime;
    string UserName;
    string Password;
    int Permissions;
  };

  static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
  {
    stLoginRegisterRecord LoginRegisterRecord;

    vector<string> LoginRegisterDataLine = clsString::Split(Line, Separator);
    LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
    LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
    LoginRegisterRecord.Password = LoginRegisterDataLine[2];
    LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

    return LoginRegisterRecord;
  }

  clsUser(enMode Mode, string FirstName, string LastName,
          string Email, string Phone, string UserName, string Password,
          int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
  {
    _Mode = Mode;
    _UserName = UserName;
    _Password = Password;
    _Permissions = Permissions;
  }

  bool IsEmpty()
  {
    return (_Mode == enMode::EmptyMode);
  }

  bool MarkedForDeleted()
  {
    return _MarkedForDelete;
  }

  string GetUserName()
  {
    return _UserName;
  }

  void SetUserName(string UserName)
  {
    _UserName = UserName;
  }
  //__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

  void SetPassword(string Password)
  {
    _Password = Password;
  }

  string GetPassword()
  {
    return _Password;
  }
  //__declspec(property(get = GetPassword, put = SetPassword)) string Password;

  void SetPermissions(int Permissions)
  {
    _Permissions = Permissions;
  }

  int GetPermissions()
  {
    return _Permissions;
  }
  //__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

  static clsUser Find(string UserName)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::in); // read Mode

    if (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsUser User = _ConvertLineToUserObject(Line);
        if (User.GetUserName() == UserName)
        {
          MyFile.close();
          return User;
        }
      }
      MyFile.close();
    }
    return _GetEmptyUserObject();
  }

  static clsUser Find(string UserName, string Password)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::in); // read Mode

    if (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsUser User = _ConvertLineToUserObject(Line);
        if (User.GetUserName() == UserName && User.GetPassword() == Password)
        {
          MyFile.close();
          return User;
        }
      }
      MyFile.close();
    }
    return _GetEmptyUserObject();
  }

  enum enSaveResults
  {
    svFailEmptyObject = 0,
    svSucceeded = 1,
    svFailUserExists = 2
  };

  enSaveResults Save()
  {
    switch (_Mode)
    {
    case enMode::EmptyMode:
    {
      if (IsEmpty())
        return enSaveResults::svFailEmptyObject;
    }

    case enMode::UpdateMode:
    {
      _Update();
      return enSaveResults::svSucceeded;
      break;
    }

    case enMode::AddNewMode:
    {
      // This will add new record to file or database
      if (clsUser::IsUserExist(_UserName))
      {
        return enSaveResults::svFailUserExists;
      }
      else
      {
        _AddNew();
        // We need to set the mode to update after add new
        _Mode = enMode::UpdateMode;
        return enSaveResults::svSucceeded;
      }
      break;
    }
    }
  }

  static bool IsUserExist(string UserName)
  {
    clsUser User = clsUser::Find(UserName);
    return (!User.IsEmpty());
  }

  bool Delete()
  {
    vector<clsUser> _vUsers;
    _vUsers = _LoadUsersDataFromFile();

    for (clsUser &U : _vUsers)
    {
      if (U.GetUserName() == _UserName)
      {
        U._MarkedForDelete = true;
        break;
      }
    }
    _SaveUsersDataToFile(_vUsers);
    *this = _GetEmptyUserObject();
    return true;
  }

  static clsUser GetAddNewUserObject(string UserName)
  {
    return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
  }

  static vector<clsUser> GetUsersList()
  {
    return _LoadUsersDataFromFile();
  }

  bool CheckAccessPermission(enPermissions Permission)
  {
    if (this->GetPermissions() == enPermissions::eAll)
      return true;

    if ((Permission & this->GetPermissions()) == Permission)
      return true;
    else
      return false;
  }

  void RegisterLogIn()
  {
    string stDataLine = _PrepareLogInRecord();

    fstream MyFile;
    MyFile.open("LoginRegister.txt", ios::out | ios::app); // append Mode

    if (MyFile.is_open())
    {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

  static vector<stLoginRegisterRecord> GetLoginRegisterList()
  {
    vector<stLoginRegisterRecord> vLoginRegisterRecord;

    fstream MyFile;
    MyFile.open("LoginRegister.txt", ios::in); // read Mode

    if (MyFile.is_open())
    {
      string Line;
      stLoginRegisterRecord LoginRegisterRecord;

      while (getline(MyFile, Line))
      {
        LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
        vLoginRegisterRecord.push_back(LoginRegisterRecord);
      }

      MyFile.close();
    }

    return vLoginRegisterRecord;
  }
};
