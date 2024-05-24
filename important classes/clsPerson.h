#pragma once

#include <iostream>
#include <string>

#include "../InterfaceCommunication.h"

using namespace std;

class clsPerson : public InterfaceCommunication
{
private:
  string _FirstName;
  string _LastName;
  string _Email;
  string _Phone;

public:
  clsPerson(string FirstName, string LastName, string Email, string Phone)
  {
    _FirstName = FirstName;
    _LastName = LastName;
    _Email = Email;
    _Phone = Phone;
  }

  // property set
  void SetFirstName(string FirstName)
  {
    _FirstName = FirstName;
  }
  // property get
  string GetFirstName()
  {
    return _FirstName;
  }
  // property set
  void SetLastName(string LastName)
  {
    _LastName = LastName;
  }
  // property get
  string GetLastName()
  {
    return _LastName;
  }
  // property set
  void SetEmail(string Email)
  {
    _Email = Email;
  }
  // property get
  string GetEmail()
  {
    return _Email;
  }
  // property set
  void SetPhone(string Phone)
  {
    _Phone = Phone;
  }
  // property get
  string GetPhone()
  {
    return _Phone;
  }
  string FullName()
  {
    return _FirstName + " " + _LastName;
  }

  void SendEmail(string Title, string Body)
  {
  }

  void SendFax(string Title, string Body)
  {
  }

  void SendSMS(string Title, string Body)
  {
  }
};
