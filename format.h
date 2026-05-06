#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace format
{
    //*************************************************************
    // Formating Functions.
    //*************************************************************
    enum enAlign
    {
        LEFT,
        CENTER,
        RIGHT
    };

    string tabs(short numberOfTabs)
    {
        return string(numberOfTabs, '\t');
    }

    string lines(short numberOfLines)
    {
        return string(numberOfLines, '\n');
    }

    string characters(char character, short numberOfCharacters)
    {
        return string(numberOfCharacters, character);
    }

    string formatString(short width, string str, enAlign align = LEFT, char fillChar = ' ')
    {
        if (str.length() >= width)
        {
            return str;
        }
        short space = width - str.length();
        string result;
        switch (align)
        {
        case LEFT:
            result = str + string(space, fillChar);
            break;
        case RIGHT:
            result = string(space, fillChar) + str;
            break;
        case CENTER:
        {
            short left = space / 2;
            short right = space - left;
            result = string(left, fillChar) + str + string(right, fillChar);
            break;
        }
        }
        return result;
    }

    vector<string> splitString(string sentence, string delimiter)
    {
        vector<string> words;
        short position;
        string word = "";
        while ((position = sentence.find(delimiter)) != std::string::npos)
        {
            word = sentence.substr(0, position);
            if (word != "")
            {
                words.push_back(word);
            }
            sentence.erase(0, position + delimiter.length());
        }
        if (sentence != "")
        {
            words.push_back(sentence);
        }
        return words;
    }

    void printHeader(string header, enAlign align = CENTER)
    {
        cout << characters('-', 40) << endl;
        cout << "|" << formatString(38, header, align) << "|" << endl;
        cout << characters('-', 40) << endl;
    }

    void printFooter(string footer, enAlign align = CENTER)
    {
        cout << characters('-', 40) << endl;
        cout << "|" << formatString(38, footer, align) << "|" << endl;
        cout << characters('-', 40) << endl;
    }
    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    void pauseScreen(string message) {
        cout << message;
        cin.get();
        cin.ignore();
    }
    //*************************************************************
}
