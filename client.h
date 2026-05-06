#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "format.h"
#include "input.h"

using namespace std;
using namespace format;
using namespace input;

namespace client
{
    //*************************************************************
    // Client Data Functions.
    //*************************************************************
    // Client Members.
    struct Client
    {
        string accountNumber = "";
        string pinCode = "";
        string fullName = "";
        string phoneNumber = "";
        double balance = 0;
    };
    // Make Clients Data File Be In The Project Folder.
    const string fileName_CLIENTS = "clients.txt";
    // Counvert Line That Has Client Data To Record.
    Client convertLineToRecord(string &line)
    {
        Client clientRecord;
        vector<string> vClientData = format::splitString(line, ",");
        clientRecord.accountNumber = vClientData[0];
        clientRecord.pinCode = vClientData[1];
        clientRecord.fullName = vClientData[2];
        clientRecord.phoneNumber = vClientData[3];
        clientRecord.balance = stod(vClientData[4]);
        return clientRecord;
    }
    // Load Client Data From File To Recoed.
    vector<Client> loadClientsDataFromFile()
    {
        vector<Client> vClients;
        fstream file;
        file.open(fileName_CLIENTS, ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line != "")
                {
                    vClients.push_back(convertLineToRecord(line));
                }
            }
        }
        file.close();
        return vClients;
    }
    // Counvert Client Recorded Data To Line.
    string convertRecordToLine(Client clientRecord, string separator)
    {
        string clientDataInLine = "";
        clientDataInLine += clientRecord.accountNumber + separator;
        clientDataInLine += clientRecord.pinCode + separator;
        clientDataInLine += clientRecord.fullName + separator;
        clientDataInLine += clientRecord.phoneNumber + separator;
        clientDataInLine += to_string(clientRecord.balance);
        return clientDataInLine;
    }
    // Save Clients Data From Vector To File After Counvert Them To Lines.
    void saveClientDataFromVectorToFile(vector<Client> vClients)
    {
        fstream file;
        file.open(fileName_CLIENTS, ios::out);
        if (file.is_open())
        {
            for (Client &clientRecord : vClients)
            {
                file << convertRecordToLine(clientRecord, ",") << endl;
            }
        }
        file.close();
    }
    // Add New Client Data To File.
    void addClientDataToFile(Client &client)
    {
        fstream file;
        file.open(fileName_CLIENTS, ios::out | ios::app);
        if (file.is_open())
        {
            file << convertRecordToLine(client, ",") << endl;
        }
        file.close();
    }
    //*************************************************************
    // Validation Functions.
    //*************************************************************
    // Check Account Number If Is Available.
    bool isValidAccountNumber(string &accountNumber)
    {
        if (accountNumber.size() == 0)
        {
            return false;
        }
        for (short i = 0; i < accountNumber.size(); i++)
        {
            if (ispunct(accountNumber[i]) || accountNumber[i] == ' ')
            {
                return false;
            }
        }
        return true;
    }
    // Check PIN Code If Is Valid.
    bool isValidPinCode(string &pinCode)
    {
        if (pinCode.size() < 4)
        {
            return false;
        }
        for (short i = 0; i < pinCode.size(); i++)
        {
            if (ispunct(pinCode[i]) || pinCode[i] == ' ')
            {
                return false;
            }
        }
        return true;
    }
    // Check Full Name If Is Valid.
    bool isValidFullName(string &fullName)
    {
        if (fullName.size() < 4)
        {
            return false;
        }
        for (short i = 0; i < fullName.size(); i++)
        {
            if (ispunct(fullName[i]) || isdigit(fullName[i]))
            {
                return false;
            }
        }
        return true;
    }
    // Check Phone Number If Is Valid.
    bool isValidPhoneNumber(string &phoneNumber)
    {
        if (phoneNumber.size() < 10)
        {
            return false;
        }
        if (phoneNumber[0] != '+')
        {
            phoneNumber = '+' + phoneNumber;
        }
        for (short i = 1; i < phoneNumber.size(); i++)
        {
            if (!isdigit(phoneNumber[i]))
            {
                return false;
            }
        }
        return true;
    }
    //*************************************************************
    // Input Functions.
    //*************************************************************
    // Read Account Number And Check It If Existed.
    string readAccountNumber()
    {
        vector<Client> vClients = loadClientsDataFromFile();
        string accountNumber;
        bool isExisted;
        cout << "Enter account number : ";
        do
        {
            isExisted = false;
            getline(cin >> ws, accountNumber);
            if (isValidAccountNumber(accountNumber))
            {
                for (Client &client : vClients)
                {
                    if (client.accountNumber == accountNumber)
                    {
                        cout << "\nClient with (" << accountNumber << ") already exists, enter another one : ";
                        isExisted = true;
                        break;
                    }
                }
            }
            else
            {
                cout << "\nInvalid account number, enter a valid account number : ";
                isExisted = true;
            }
        } while (isExisted);
        return accountNumber;
    }
    // Read PIN Code And Check It If Valid.
    string readPinCode()
    {
        string pinCode;
        cout << "Enter PIN code : ";
        getline(cin >> ws, pinCode);
        while (!isValidPinCode(pinCode))
        {
            cout << "\nInvalid PIN code, enter a valid PIN code : ";
            getline(cin >> ws, pinCode);
        }
        return pinCode;
    }
    // Read Full Name And Check It If Valid.
    string readFullName()
    {
        string fullName;
        cout << "Enter full name : ";
        getline(cin >> ws, fullName);
        while (!isValidFullName(fullName))
        {
            cout << "\nInvalid full name, enter a valid full name : ";
            getline(cin >> ws, fullName);
        }
        return fullName;
    }
    // Read Phone Number And Check It If Valid.
    string readPhoneNumber()
    {
        string phoneNumber;
        cout << "Enter phone number : ";
        getline(cin >> ws, phoneNumber);
        while (!isValidPhoneNumber(phoneNumber))
        {
            cout << "\nInvalid phone number, enter a valid phone number : ";
            getline(cin >> ws, phoneNumber);
        }
        return phoneNumber;
    }
    //*************************************************************
    // Client Functions.
    //*************************************************************
    // Print Client Data.
    void displayClientData(Client &client)
    {
        cout << "|" << formatString(16, client.accountNumber, CENTER);
        cout << "|" << formatString(10, client.pinCode, CENTER);
        cout << "|" << formatString(21, client.fullName, CENTER);
        cout << "|" << formatString(14, client.phoneNumber, CENTER);
        cout << "|" << formatString(15, to_string(client.balance), CENTER) << "|";
    }
    //[1] Show Clients List.
    void showClientsList()
    {
        vector<Client> vClients = loadClientsDataFromFile();
        cout << characters('-', 91) << endl;
        cout << "|" << formatString(89, "| Clients List (" + to_string(vClients.size()) + ") Client(s) |", CENTER) << "|" << endl;
        cout << characters('-', 91) << endl;
        cout << "|" << " Number ";
        cout << "|" << " Account Number ";
        cout << "|" << " PIN Code ";
        cout << "|" << "      Full Name      ";
        cout << "|" << " Phone Number ";
        cout << "|" << "  Balance ($)  " << "|";
        cout << "\n"
             << characters('-', 91) << endl;
        if (vClients.size() == 0)
        {
            cout << "|" << formatString(89, "No clients available in the Bank", CENTER) << "|" << endl;
        }
        else
        {
            int count = 0;
            for (Client &client : vClients)
            {
                cout << "|" << formatString(8, to_string(++count), CENTER);
                displayClientData(client);
                cout << "\n";
            }
        }
        cout << characters('-', 91) << endl
             << endl;
    }

    // Read New Client Data.
    Client readNewClientData()
    {
        Client client;
        client.accountNumber = readAccountNumber();
        client.pinCode = readPinCode();
        client.fullName = readFullName();
        client.phoneNumber = readPhoneNumber();
        client.balance = readPositiveNumber("Enter balance : ");
        return client;
    }
    //[2] Add Client To Clients List.
    void addClient()
    {
        printHeader("Add New Client");
        cout << endl;
        Client client = readNewClientData();
        cout << "\nClient added successfully.\n"
             << endl;
        addClientDataToFile(client);
    }

    // Check Client If Is Found Or Not.
    bool isClientFound(string accountNumber, Client &client)
    {
        vector<Client> vClients = loadClientsDataFromFile();
        for (Client &clientData : vClients)
        {
            if (clientData.accountNumber == accountNumber)
            {
                client = clientData;
                return true;
            }
        }
        return false;
    }

    // Delete Client Data.
    void deleteClientData(string accountNumberToDelete, vector<Client> &vClients)
    {
        vector<Client>::iterator it;
        for (int i = 0; i < vClients.size(); ++i)
        {
            if (vClients[i].accountNumber == accountNumberToDelete)
            {
                vClients.erase(vClients.begin() + i);
                break;
            }
        }
    }
    // Show Client Data.
    void showClientData(Client &client)
    {
        cout << "\n"
             << characters('-', 18) << endl;
        cout << "| Client Data    |" << endl;
        cout << characters('-', 48) << endl;
        cout << "| Account Number | " << formatString(27, client.accountNumber) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| PIN Code       | " << formatString(27, client.pinCode) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| Full Name      | " << formatString(27, client.fullName) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| Phone Number   | " << formatString(27, client.phoneNumber) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| Balance        | " << formatString(27, to_string(client.balance)) << " | " << endl;
        cout << characters('-', 48) << endl;
    }
    //[3] Delete Client From Clients List.
    void removeClient()
    {
        vector<Client> vClients = loadClientsDataFromFile();
        printHeader("Delete Client");
        Client client;
        string accountNumberToDelete = readString("\nEnter account number : ");
        if (isClientFound(accountNumberToDelete, client))
        {
            showClientData(client);
            char choice = readChar("\nAre you sure you want to delete this client? Y / N ? ");
            if (toupper(choice) == 'Y')
            {
                deleteClientData(accountNumberToDelete, vClients);
                cout << "\nClient deleted successfully." << endl;
                saveClientDataFromVectorToFile(vClients);
            }
            cout << endl;
        }
        else
        {
            cout << "\nClient with account number (" << accountNumberToDelete << ") is not found :(\n"
                 << endl;
        }
    }

    // Read New Client Data To Update Them.
    Client changeClientData(string accountNumber)
    {
        Client newClientData;
        newClientData.accountNumber = accountNumber;
        newClientData.pinCode = readPinCode();
        newClientData.fullName = readFullName();
        newClientData.phoneNumber = readPhoneNumber();
        newClientData.balance = readPositiveNumber("Enter balance : ");
        return newClientData;
    }
    // Update Client Data.
    void updateClientData(string accountNumberToUpdate, vector<Client> &vClients)
    {
        Client newClientData = changeClientData(accountNumberToUpdate);
        for (Client &clientData : vClients)
        {
            if (clientData.accountNumber == accountNumberToUpdate)
            {
                clientData = newClientData;
                break;
            }
        }
    }
    //[4] Update Client Data.
    void updateClient()
    {
        printHeader("Update Client Data");
        vector<Client> vClients = loadClientsDataFromFile();
        Client client;
        string accountNumberToUpdate = readString("\nEnter account number : ");
        if (isClientFound(accountNumberToUpdate, client))
        {
            showClientData(client);
            char choice = readChar("\nAre you sure you want to update this client data? Y / N ? ");
            if (toupper(choice) == 'Y')
            {
                updateClientData(accountNumberToUpdate, vClients);
                cout << "\nClient data updated successfully." << endl;
                saveClientDataFromVectorToFile(vClients);
            }
            cout << endl;
        }
        else
        {
            cout << "\nClient with account number (" << accountNumberToUpdate << ") is not found :(\n"
                 << endl;
        }
    }

    // Find Client.
    void searchForClient()
    {
        printHeader("Find Client");
        Client client;
        string accountNumberToFind = readString("\nEnter account number : ");
        if (isClientFound(accountNumberToFind, client))
        {
            showClientData(client);
            cout << endl;
        }
        else
        {
            cout << "\nClient with account number (" << accountNumberToFind << ") is not found :(\n"
                 << endl;
        }
    }
    //*************************************************************
}
