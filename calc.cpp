#ifndef CPP_CALC
#define CPP_CALC
#include <string>
#include <stdio.h>
#include <iostream>
using std::endl;
using std::cout;
using std::string;

string fromDecToHex(int number, const unsigned int &base)
{
    const char *DIGITS = "0123456789abcdefghijklmnopqrstuvwxyz";
    bool FlagInverse = false;
    string reversString, stringInBase;

    if (base < 2 || base > 36)
    {
        cout << "Error: base must be from 2 to 36." << endl;
        return "-1";
    }
    if (number < 0)
    {
        FlagInverse = true;
        number *= -1;
    }

    stringInBase += DIGITS[number % base];
    number = number / base;
    while (number)
    {
        stringInBase += DIGITS[number % base];
        number = number / base;
    }

    if (FlagInverse == true)
        reversString = "-";

    for (int i = stringInBase.length() - 1; i >= 0; i--)
        reversString += stringInBase[i];

    return reversString;
}
#endif
