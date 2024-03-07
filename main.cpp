#include <iostream>
#include "./important classes/clsBankClient.h"
#include "./libraries/clsInputValidate.h"

void ReadClientInfo(clsBankClient &Client)
{
    cout << "\nEnter First Name: ";
    Client.SetFirstName(clsInputValidate::ReadString());

    cout << "\nEnter Last Name: ";
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

void UpdateClient()
{
    string AccountNumber = "";
    cout << "\nPlease enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    Client1.Print();

    cout << "\n\nUpdate Client Info: ";
    cout << "\n\n-----------------------\n";

    ReadClientInfo(Client1);

    clsBankClient::enSaveResults SaveResult;

    SaveResult = Client1.Save();

    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
    {
        cout << "\nAccount Updated Successfully: -)";
        Client1.Print();
        break;
    }

    case clsBankClient::enSaveResults::svFailEmptyObject:
    {
        cout << "\nError Account was not saved because is empty";
        break;
    }
    
    default:
        break;
    }
}

int main()
{
    UpdateClient();
}
