#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"
#include "clsString.h"

using namespace std;

class clsInputValidate
{
public:
  static bool IsNumberBetween(short Number, short From, short To)
  {
    return (Number >= From && Number <= To);
  }
  static bool IsNumberBetween(int Number, int From, int To)
  {
    return (Number >= From && Number <= To);
  }
  static bool IsNumberBetween(float Number, float From, float To)
  {
    return (Number >= From && Number <= To);
  }
  static bool IsNumberBetween(double Number, double From, double To)
  {
    return (Number >= From && Number <= To);
  }

  static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
  {
    // Date >= From && Date <= To
    if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From) && clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
      return true;

    // Date >= To && Date <= From
    if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To) && clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
      return false;

    return false;
  }

  static int ReadIntNumber(string ErrorMessage = "Invalid number, Enter again:\n")
  {
    int Number;

    while (!(cin >> Number))
    {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << ErrorMessage << endl;
    }
    return Number;
  }

  static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
  {
    int Number = ReadIntNumber();
    while (!IsNumberBetween(Number, From, To))
    {
      cout << ErrorMessage;
      Number = ReadIntNumber();
    }
    return Number;
  }

  static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
  {
    double Number;
    while (!(cin >> Number))
    {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << ErrorMessage;
    }
    return Number;
  }

  static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
  {
    double Number = ReadDblNumber();
    while (!IsNumberBetween(Number, From, To))
    {
      cout << ErrorMessage;
      Number = ReadDblNumber();
    }
    return Number;
  }

  static bool IsValidDate(clsDate Date)
  {
    return clsDate::IsValidDate(Date);
  }
};
