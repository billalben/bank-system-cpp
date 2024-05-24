#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include "../clsScreen.h"
#include "../important classes/clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:
  static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
  {

    cout << "| " << setw(23) << left << TransferLogRecord.DateTime;
    cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
    cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
    cout << "| " << setw(8) << left << TransferLogRecord.Amount;
    cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
    cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
    cout << "| " << setw(8) << left << TransferLogRecord.UserName;
  }

public:
  static void ShowTransferLogScreen()
  {

    vector<clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransfersLogList();

    string Title = "\tTransfer Log List Screen";
    string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

    _DrawScreenHeader(Title, SubTitle);

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(23) << "Date/Time";
    cout << "| " << left << setw(8) << "s.Acct";
    cout << "| " << left << setw(8) << "d.Acct";
    cout << "| " << left << setw(8) << "Amount";
    cout << "| " << left << setw(10) << "s.Balance";
    cout << "| " << left << setw(10) << "d.Balance";
    cout << "| " << left << setw(8) << "User";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vTransferLogRecord.size() == 0)
      cout << "\t\t\t\tNo Transfers Available In the System!";
    else

      for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
      {
        PrintTransferLogRecordLine(Record);
        cout << endl;
      }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
  }
};
