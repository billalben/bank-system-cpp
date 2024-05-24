#pragma once

#include <iostream>

#include "../clsScreen.h"
#include "../Global.h"
#include "../important classes/clsPerson.h"
#include "../important classes/clsBankClient.h"
#include "../libraries/clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:
  static void _PrintClient(clsBankClient Client)
  {
    cout << "\nClient Card:";
    cout << "\n___________________\n";
    cout << "\nFull Name   : " << Client.FullName();
    cout << "\nAcc. Number : " << Client.AccountNumber();
    cout << "\nBalance     : " << Client.GetAccountBalance();
    cout << "\n___________________\n";
  }

  static string _ReadAccountNumber()
  {
    string AccountNumber;
    cout << "\nPlease Enter Account Number to Transfer From: ";
    AccountNumber = clsInputValidate::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
      cout << "\nAccount number is not found, choose another one: ";
      AccountNumber = clsInputValidate::ReadString();
    }
    return AccountNumber;
  }

  static float ReadAmount(clsBankClient SourceClient)
  {
    float Amount;

    cout << "\nEnter Transfer Amount? ";

    Amount = clsInputValidate::ReadNumber<float>();

    while (Amount > SourceClient.GetAccountBalance())
    {
      cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
      Amount = clsInputValidate::ReadNumber<double>();
    }
    return Amount;
  }

public:
  static void ShowTransferScreen()
  {
    _DrawScreenHeader("\tTransfer Screen");

    clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

    _PrintClient(SourceClient);

    clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

    _PrintClient(DestinationClient);

    float Amount = ReadAmount(SourceClient);

    cout << "\nAre you sure you want to perform this operation? y/n? ";
    char Answer = 'n';
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
    {
      if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.GetUserName()))
      {
        cout << "\nTransfer done successfully\n";
      }
      else
      {
        cout << "\nTransfer Fail\n";
      }
    }

    _PrintClient(SourceClient);
    _PrintClient(DestinationClient);
  }
};
