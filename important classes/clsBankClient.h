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
    UpdateMode = 1,
    AddNewMode = 2
  };
  enMode _Mode;

  string _AccountNumber;
  string _PinCode;
  float _AccountBalance;
  bool _MarkForDelete = false;

  static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
  {
    vector<string> vClientData;
    vClientData = clsString::Split(Line, Separator);

    return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                         vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
  }

  static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
  {
    string stClientRecord = "";
    stClientRecord += Client.GetFirstName() + Separator;
    stClientRecord += Client.GetLastName() + Separator;
    stClientRecord += Client.GetEmail() + Separator;
    stClientRecord += Client.GetPhone() + Separator;
    stClientRecord += Client.AccountNumber() + Separator;
    stClientRecord += Client.GetPinCode() + Separator;
    stClientRecord += to_string(Client.GetAccountBalance());

    return stClientRecord;
  }

  static vector<clsBankClient> _LoadClientsDataFromFile()
  {
    vector<clsBankClient> vClients;

    fstream MyFile;
    MyFile.open("Clients.txt", ios::in); // read mode

    if (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsBankClient Client = _ConvertLineToClientObject(Line);
        vClients.push_back(Client);
      }
      MyFile.close();
    }
    return vClients;
  }

  static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
  {
    fstream MyFile;
    MyFile.open("Clients.txt", ios::out); // overwrite

    string DataLine;
    while (MyFile.is_open())
    {
      for (clsBankClient C : vClients)
      {
        if (C._MarkForDelete == false)
        {
          // we only write records that are not marked for delete.
          DataLine = _ConvertClientObjectToLine(C);
          MyFile << DataLine << endl;
        }
      }
      MyFile.close();
    }
  }

  void _Update()
  {
    vector<clsBankClient> _vClients;
    _vClients = _LoadClientsDataFromFile();

    for (clsBankClient &C : _vClients)
    {
      if (C.AccountNumber() == AccountNumber())
      {
        C = *this;
        break;
      }
    }
    _SaveClientsDataToFile(_vClients);
  }

  void _AddNew()
  {
    _AddDataLineToFile(_ConvertClientObjectToLine(*this));
  }

  void _AddDataLineToFile(string stDataLine)
  {
    fstream MyFile;
    MyFile.open("Clients.txt", ios::out | ios::app);

    if (MyFile.is_open())
    {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

  static clsBankClient _GetEmptyClientObject()
  {
    return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
  }

  string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
                                   string UserName, string Separator = "#//#")
  {
    string TransferLogRecord = "";
    TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
    TransferLogRecord += AccountNumber() + Separator;
    TransferLogRecord += DestinationClient.AccountNumber() + Separator;
    TransferLogRecord += to_string(Amount) + Separator;
    TransferLogRecord += to_string(GetAccountBalance()) + Separator;
    TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Separator;
    TransferLogRecord += UserName;
    return TransferLogRecord;
  }

  void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
  {
    string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

    fstream MyFile;
    MyFile.open("TransferLog.txt", ios::out | ios::app);

    if (MyFile.is_open())
    {
      MyFile << stDataLine << endl;
      MyFile.close();
    }
  }

public:
  struct stTransferLogRecord
  {
    string DateTime;
    string SourceAccountNumber;
    string DestinationAccountNumber;
    float Amount;
    float srcBalanceAfter;
    float destBalanceAfter;
    string UserName;
  };

  static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
  {
    stTransferLogRecord TransferLogRecord;

    vector<string> vTransferLogRecordLine = clsString::Split(Line, Separator);
    TransferLogRecord.DateTime = vTransferLogRecordLine[0];
    TransferLogRecord.SourceAccountNumber = vTransferLogRecordLine[1];
    TransferLogRecord.DestinationAccountNumber = vTransferLogRecordLine[2];
    TransferLogRecord.Amount = stod(vTransferLogRecordLine[3]);
    TransferLogRecord.srcBalanceAfter = stod(vTransferLogRecordLine[4]);
    TransferLogRecord.destBalanceAfter = stod(vTransferLogRecordLine[5]);
    TransferLogRecord.UserName = vTransferLogRecordLine[6];

    return TransferLogRecord;
  }

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

  // no UI related code inside object
  // void Print()
  // {
  //     cout << "\nClient Card:";
  //     cout << "\n----------------------------------";
  //     cout << "\nFirst Name     : " << GetFirstName();
  //     cout << "\nLast Name      : " << GetLastName();
  //     cout << "\nFull Name      : " << FullName();
  //     cout << "\nEmail          : " << GetEmail();
  //     cout << "\nPhone          : " << GetPhone();
  //     cout << "\nAccount Number : " << _AccountNumber;
  //     cout << "\nPassword       : " << _PinCode;
  //     cout << "\nBalance        : " << _AccountBalance;
  //     cout << "\n----------------------------------\n";
  // }

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
    vector<clsBankClient> vClients;

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

  bool Delete()
  {
    vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
    for (clsBankClient &C : _vClients)
    {
      if (C.AccountNumber() == AccountNumber())
      {
        C._MarkForDelete = true;
        break;
      }
    }
    _SaveClientsDataToFile(_vClients);
    *this = _GetEmptyClientObject();
    return true;
  }

  enum enSaveResults
  {
    svFailEmptyObject = 0,
    svSucceeded = 1,
    svFailAccountNumberExists = 2
  };

  enSaveResults Save()
  {
    switch (_Mode)
    {
    case enMode::EmptyMode:
    {
      if (IsEmpty())
      {
        return enSaveResults::svFailEmptyObject;
      }
    }

    case enMode::UpdateMode:
    {
      _Update();
      return enSaveResults::svSucceeded;
    }

    case enMode::AddNewMode:
    {
      // this will add new record to file or database
      if (clsBankClient::IsClientExist(_AccountNumber))
      {
        return enSaveResults::svFailAccountNumberExists;
      }
      else
      {
        _AddNew();

        // we need to set the mode update after add new
        _Mode = enMode::UpdateMode;
        return enSaveResults::svSucceeded;
      }
    }

    default:
      break;
    }
  }

  static clsBankClient GetAddNewClientObject(string AccountNumber)
  {
    return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
  }

  static vector<clsBankClient> GetClientsList()
  {
    return _LoadClientsDataFromFile();
  }

  static double GetTotalBalances()
  {
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();
    double TotalBalances = 0;

    for (clsBankClient Client : vClients)
    {
      TotalBalances += Client.GetAccountBalance();
    }
    return TotalBalances;
  }

  void Deposit(double Amount)
  {
    _AccountBalance += Amount;
    Save();
  }

  bool Withdraw(double Amount)
  {
    if (Amount > _AccountBalance)
      return false;
    else
    {
      _AccountBalance -= Amount;
      Save();
      return true;
    }
  }

  bool Transfer(float Amount, clsBankClient &DestinationClient, string UserName)
  {
    if (Amount > _AccountBalance)
      return false;

    Withdraw(Amount);
    DestinationClient.Deposit(Amount);
    _RegisterTransferLog(Amount, DestinationClient, UserName);
    return true;
  }

  static vector<stTransferLogRecord> GetTransfersLogList()
  {
    vector<stTransferLogRecord> vTransferLogRecord;

    fstream MyFile;
    MyFile.open("TransferLog.txt", ios::in); // read Mode

    if (MyFile.is_open())
    {
      string Line;

      stTransferLogRecord TransferRecord;

      while (getline(MyFile, Line))
      {
        TransferRecord = _ConvertTransferLogLineToRecord(Line);
        vTransferLogRecord.push_back(TransferRecord);
      }
      MyFile.close();
    }
    return vTransferLogRecord;
  }
};
