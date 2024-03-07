#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "clsPerson.h"
#include "../libraries/clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
  enum enMode
  {
    EmptyMode = 0,
    UpdateMode = 1
  };
  enMode _Mode;

  string _AccountNumber;
  string _PinCode;
  float _AccountBalance;

  static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
  {
    vector<string> vClientData;
    vClientData = clsString::Split(Line, Separator);

    return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                          vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
  }

  static clsBankClient _GetEmptyClientObject()
  {
    return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
  }

public:
  clsBankClient(enMode Mode, string FirstName, string LastName,
                string Email, string Phone, string AccountNumber, string PinCode,
                float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
  {
    _Mode = Mode;
    _AccountNumber = AccountNumber;
    _PinCode = PinCode;
    _AccountBalance = AccountBalance;
  }

  bool IsEmpty()
  {
    return (_Mode == enMode::EmptyMode);
  }

  string AccountNumber()
  {
    return _AccountNumber;
  }

  void SetPinCode(string PinCode)
  {
    _PinCode = PinCode;
  }
  string GetPinCode()
  {
    return _PinCode;
  }

  void SetAccountBalance(float AccountBalance)
  {
    _AccountBalance = AccountBalance;
  }
  float GetAccountBalance()
  {
    return _AccountBalance;
  }

  void Print()
  {
    cout << "\nClient Card:";
    cout << "\n-------------------";
    cout << "\nFirst Name     : " << GetFirstName();
    cout << "\nLast Name      : " << GetLastName();
    cout << "\nFull Name      : " << FullName();
    cout << "\nEmail          : " << GetEmail();
    cout << "\nPhone          : " << GetPhone();
    cout << "\nAccount Number : " << _AccountNumber;
    cout << "\nPassword       : " << _PinCode;
    cout << "\nBalance        : " << _AccountBalance;
    cout << "\n-------------------\n";
  }

  static clsBankClient Find(string AccountNumber)
  {
    fstream MyFile;
    MyFile.open("Clients.txt", ios::in); // Read Mode

    while (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsBankClient Client = _ConvertLineToClientObject(Line);
        if (Client.AccountNumber() == AccountNumber)
        {
          MyFile.close();
          return Client;
        }
      }
      MyFile.close();
    }
    return _GetEmptyClientObject();
  }

  static clsBankClient Find(string AccountNumber, string PinCode)
  {
    fstream MyFile;
    MyFile.open("Clients.txt", ios::in); // Read Mode

    while (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsBankClient Client = _ConvertLineToClientObject(Line);
        if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
        {
          MyFile.close();
          return Client;
        }
      }
      MyFile.close();
    }
    return _GetEmptyClientObject();
  }

  static bool IsClientExist(string AccountNumber)
  {
    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    return (!Client1.IsEmpty());
  }
};
