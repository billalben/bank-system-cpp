#include <iostream>
#include "./important classes/clsBankClient.h"
#include "./libraries/clsInputValidate.h"
#include "./libraries/clsUtil.h"

void PrintClientRecordBalanceLine(clsBankClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber();
  cout << "| " << setw(20) << left << Client.FullName();
  cout << "| " << setw(12) << left << Client.GetAccountBalance();
}

void ShowTotalBalances()
{
  vector<clsBankClient> vClients = clsBankClient::GetClientList();

  cout << "\n\tClient List (" << vClients.size() << ") Client(s).\n";
  cout << "\n---------------------------------------------------\n";

  cout << "| " << left << setw(15) << "Account Number";
  cout << "| " << left << setw(20) << "Client Name";
  cout << "| " << left << setw(12) << "Balance";

  cout << "\n---------------------------------------------------\n";

  double TotalBalances = clsBankClient::GetTotalBalances();

  if (vClients.size() == 0)
    cout << "\t\t\tNo Client Available in the system";
  else
  {
    for (clsBankClient Client : vClients)
    {
      PrintClientRecordBalanceLine(Client);
      cout << endl;
    }
  }

  cout << "\n---------------------------------------------------\n";

  cout << "Total Balances: " << TotalBalances << endl;
  cout << clsUtil::NumberToText(TotalBalances) << endl;
}

int main()
{
  ShowTotalBalances();
}
