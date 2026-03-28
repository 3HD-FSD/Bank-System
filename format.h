#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

namespace format {

    //*************************************************************
    //Input Functions.
    //*************************************************************
    double readPositiveNumber(string message) {
        double number;
        cout << message;
        cin >> number;
        while (cin.fail() || number < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Invalid input, enter a valid number : ";
            cin >> number;
        }
        return number;
    }

    int readNumberInRange(string message, int from, int to) {
        int number;
        cout << message;
        cin >> number;
        while (cin.fail() || number < from || number > to) {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Invalid input, enter a valid number from " << from << " to " << to << " : ";
            cin >> number;
        }
        return number;
    }

    string readString(string message) {
        string str;
        cout << message;
        getline(cin >> ws, str);
        return str;
    }
    
    char readChar(string message) {
        char character;
        cout << message;
        cin >> character;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            cout << "Invalid input, enter a valid character : ";
            cin >> character;
        }
        return character;
    }
    //*************************************************************
    //Formating Functions.
    //*************************************************************
    enum enAlign { LEFT, CENTER, RIGHT };

    string tabs(short numberOfTabs) {
        return string(numberOfTabs, '\t');
    }

    string lines(short numberOfLines) {
        return string(numberOfLines, '\n');
    }

    string characters(char character, short numberOfCharacters) {
        return string(numberOfCharacters, character);
    }

    string formatString(short width, string str, enAlign align = LEFT, char fillChar = ' ') {
        if (str.length() >= static_cast<size_t>(width)) {
            return str;
        }
        short space = width - str.length();
        string result;
        switch (align) {
        case LEFT:
            result = str + string(space, fillChar);
            break;
        case RIGHT:
            result = string(space, fillChar) + str;
            break;
        case CENTER: {
            short left = space / 2;
            short right = space - left;
            result = string(left, fillChar) + str + string(right, fillChar);
            break;
        }
        }
        return result;
    }
    //*************************************************************
}
