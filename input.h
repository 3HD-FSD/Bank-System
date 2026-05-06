#pragma once
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace input
{
    //*************************************************************
    // Input Functions.
    //*************************************************************
    // Read Positive Number.
    double readPositiveNumber(string message)
    {
        double number;
        cout << message;
        cin >> number;
        while (cin.fail() || number < 0)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, enter a valid number : ";
            cin >> number;
        }
        return number;
    }
    // Read Number In Range.
    int readNumberInRange(string message, int from, int to)
    {
        int number;
        cout << message;
        cin >> number;
        while (cin.fail() || number < from || number > to)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, enter a valid number from " << from << " to " << to << " : ";
            cin >> number;
        }
        return number;
    }
    // Read String.
    string readString(string message)
    {
        string str;
        cout << message;
        getline(cin >> ws, str);
        return str;
    }
    // Read Char.
    char readChar(string message)
    {
        char character;
        cout << message;
        cin >> character;
        while (cin.fail() || (toupper(character) != 'Y' && toupper(character) != 'N'))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, enter a valid character : ";
            cin >> character;
        }
        return character;
    }
    //*************************************************************
}