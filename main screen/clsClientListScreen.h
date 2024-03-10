#pragma once

#include <iostream>
#include <iomanip>

#include "../clsScreen.h"
#include "../important classes/clsBankClient.h"

class clsClientListScreen : protected clsScreen
{

private:
  static void PrintClientRecordLine(clsBankClient Client)
  {

    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(20) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.GetPhone();
    cout << "| " << setw(20) << left << Client.GetEmail();
    cout << "| " << setw(10) << left << Client.GetPinCode();
    cout << "| " << setw(12) << left << Client.GetAccountBalance();
  }

public:
  static void ShowClientsList()
  {
    if (!CheckAccessRights(clsUser::enPermissions::pListClients))
      return; // this will exit the function and it will not continue

    vector<clsBankClient> vClients = clsBankClient::GetClientsList();
    string Title = "\t  Client List Screen";
    string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

    _DrawScreenHeader(Title, SubTitle);

    cout << left << ""
         << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << left << ""
         << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(20) << "Email";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(12) << "Balance";
    cout << left << ""
         << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
      cout << "No Clients Available In the System!";
    else
      for (clsBankClient Client : vClients)
      {
        PrintClientRecordLine(Client);
        cout << endl;
      }

    cout << left << ""
         << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }
};
