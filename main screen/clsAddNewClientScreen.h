#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../important classes/clsBankClient.h"
#include "../libraries/clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
  static void _ReadClientInfo(clsBankClient &Client)
  {
    cout << "\nEnter FirstName: ";
    Client.SetFirstName(clsInputValidate::ReadString());

    cout << "\nEnter LastName: ";
    Client.SetLastName(clsInputValidate::ReadString());

    cout << "\nEnter Email: ";
    Client.SetEmail(clsInputValidate::ReadString());

    cout << "\nEnter Phone: ";
    Client.SetPhone(clsInputValidate::ReadString());

    cout << "\nEnter PinCode: ";
    Client.SetPinCode(clsInputValidate::ReadString());

    cout << "\nEnter Account Balance: ";
    Client.SetAccountBalance(clsInputValidate::ReadNumber<float>());
  }

  static void _PrintClient(clsBankClient Client)
  {
    cout << "\nClient Card:";
    cout << "\n___________________";
    cout << "\nFirstName   : " << Client.GetFirstName();
    cout << "\nLastName    : " << Client.GetLastName();
    cout << "\nFull Name   : " << Client.FullName();
    cout << "\nEmail       : " << Client.GetEmail();
    cout << "\nPhone       : " << Client.GetPhone();
    cout << "\nAcc. Number : " << Client.AccountNumber();
    cout << "\nPassword    : " << Client.GetPinCode();
    cout << "\nBalance     : " << Client.GetAccountBalance();
    cout << "\n___________________\n";
  }

public:
  static void ShowAddNewClientScreen()
  {
    if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
      return; // this will exit the function and it will not continue

    _DrawScreenHeader("\t  Add New Client Screen");

    string AccountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber))
    {
      cout << "\nAccount Number Is Already Used, Choose another one: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

    _ReadClientInfo(NewClient);

    clsBankClient::enSaveResults SaveResult;

    SaveResult = NewClient.Save();

    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
    {
      cout << "\nAccount Added Successfully :-)\n";
      _PrintClient(NewClient);
      break;
    }

    case clsBankClient::enSaveResults::svFailEmptyObject:
    {
      cout << "\nError account was not saved because it's Empty";
      break;
    }

    case clsBankClient::enSaveResults::svFailAccountNumberExists:
    {
      cout << "\nError account was not saved because account number is used!\n";
      break;
    }
    }
  }
};
