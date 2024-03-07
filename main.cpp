#include <iostream>
#include "./important classes/clsBankClient.h"
#include "./libraries/clsInputValidate.h"

void DeleteClient()
{
  string AccountNumber;
  cout << "\nPlease Account Number: ";
  AccountNumber = clsInputValidate::ReadString();

  while (!clsBankClient::IsClientExist(AccountNumber))
  {
    cout << "\nAccount Number is not found, choose another one: ";
    AccountNumber = clsInputValidate::ReadString();
  }

  clsBankClient Client1 = clsBankClient::Find(AccountNumber);
  Client1.Print();

  cout << "\nAre you sure you want to delete this client y/n? ";

  char Answer = 'n';
  cin >> Answer;

  if (Answer == 'Y' || Answer == 'y')
  {
    if (Client1.Delete())
    {
      cout << "\nClient Deleted Successfully )-\n";
      Client1.Print();
    }
    else
    {
      cout << "\nError Client was not deleted\n";
    }
  }
}

int main()
{
  DeleteClient();
}
