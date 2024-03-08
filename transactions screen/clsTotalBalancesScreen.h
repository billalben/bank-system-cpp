#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../important classes/clsBankClient.h"
#include "../libraries/clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{

private:
  static void PrintClientRecordBalanceLine(clsBankClient Client)
  {
    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.GetAccountBalance();
  }

public:
  static void ShowTotalBalances()
  {

    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    string Title = "\t  Balances List Screen";
    string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

    _DrawScreenHeader(Title, SubTitle);

    cout << "\n_______________________________________________________";
    cout << "________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "________________\n"
         << endl;

    double TotalBalances = clsBankClient::GetTotalBalances();

    if (vClients.size() == 0)
      cout << "No Clients Available In the System!";
    else

      for (clsBankClient Client : vClients)
      {
        PrintClientRecordBalanceLine(Client);
        cout << endl;
      }

    cout << "\n_______________________________________________________";
    cout << "________________\n"
         << endl;

    cout << "\tTotal Balances = " << TotalBalances << endl;
    cout << "\t( " << clsUtil::NumberToText(TotalBalances) << ")";
  }
};
