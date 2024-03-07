#include <iostream>
#include "./important classes/clsBankClient.h"
#include "./libraries/clsInputValidate.h"

void PrintClientRecordLine(clsBankClient Client)
{
  cout << "| " << setw(15) << left << Client.AccountNumber();
  cout << "| " << setw(20) << left << Client.FullName();
  cout << "| " << setw(12) << left << Client.GetPhone();
  cout << "| " << setw(20) << left << Client.GetEmail();
  cout << "| " << setw(10) << left << Client.GetPinCode();
  cout << "| " << setw(12) << left << Client.GetAccountBalance();
}

void ShowClientList()
{
  vector<clsBankClient> vClients = clsBankClient::GetClientList();

  cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
  cout << "\n----------------------------------------------------------";
  cout << "-----------------------------------------\n";

  cout << "| " << left << setw(15) << "Account Number";
  cout << "| " << left << setw(20) << "Client Name";
  cout << "| " << left << setw(12) << "Phone";
  cout << "| " << left << setw(20) << "Email";
  cout << "| " << left << setw(10) << "Pin Code";
  cout << "| " << left << setw(12) << "Balance";

  cout << "\n----------------------------------------------------------";
  cout << "-----------------------------------------\n";

  if (vClients.size() == 0)
    cout << "\t\t\tNo Client Available in the system";
  else
  {
    for (clsBankClient Client : vClients)
    {
      PrintClientRecordLine(Client);
      cout << endl;
    }
  }

  cout << "\n----------------------------------------------------------";
  cout << "-----------------------------------------\n";
}

int main()
{
  ShowClientList();
}
