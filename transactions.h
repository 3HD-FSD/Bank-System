#pragma once
#include <iostream>
#include "client.h"
#include "format.h"
#include "input.h"

using namespace std;
using namespace client;
using namespace format;
using namespace input;

namespace transactions {
    //*************************************************************
    //Trasactions Functions.
    //*************************************************************
    //Add Amount To Balance Withdraw/Deposit.
    void addAmountToBalance(double amount, string accountNumberForDeposit, string transactionStatus, vector<Client> &vClients) {
        for (Client& clientData : vClients) {
            if (clientData.accountNumber == accountNumberForDeposit) {
                clientData.balance += amount;
                cout << transactionStatus << "New balance : " << clientData.balance << "$" << endl;
                break;
            }
        }
    }

    //[1] Deposit Money.
    void deposit() {
        printHeader("| Deposit |");
        Client client;
        string accountNumberForDeposit = readString("\nEnter account number : ");
        if (isClientFound(accountNumberForDeposit, client)) {
            showClientData(client);
            double amount = readPositiveNumber("\nEnter deposit amount : ");
            char choice = readChar("\nAre you sure you want to perform this transaction? Y / N : ");
            if (toupper(choice) == 'Y') {
                vector<Client> vClients = loadClientsDataFromFile();
                addAmountToBalance(amount, accountNumberForDeposit, "\nDeposit successfully, ", vClients);
                saveClientDataFromVectorToFile(vClients);
            }
            cout << endl;
        }
        else {
            cout << "\nClient with account number (" << accountNumberForDeposit << ") is not found!\n" << endl;
        }
    }

    //Read Withdraw Amount And Check It If Exceeds The Balance.
    double readWithdrawAmount(Client& client) {
        double amount;
        do {
            amount = readPositiveNumber("\nEnter withdraw amount : ");
            if (amount <= client.balance) {
                break;
            }
            cout << "\nAmount exceeds the balance, you can withdraw up to " << client.balance << endl;
        } while (amount > client.balance);
        return amount;
    }
    //[2] Withdraw Money.
    void withdraw() {
        printHeader("| withdraw |");
        Client client;
        string accountNumberForwithdraw = readString("\nEnter account number : ");
        if (isClientFound(accountNumberForwithdraw, client)) {
            showClientData(client);
            double amount = readWithdrawAmount(client);
            char choice = readChar("\nAre you sure you want to perform this transaction? Y / N : ");
            if (toupper(choice) == 'Y') {
                vector<Client> vClients = loadClientsDataFromFile();
                addAmountToBalance(-1 * amount, accountNumberForwithdraw, "\nWithdraw successfully, ", vClients);
                saveClientDataFromVectorToFile(vClients);
            }
            cout << endl;
        }
        else {
            cout << "\nClient with account number (" << accountNumberForwithdraw << ") is not found!\n" << endl;
        }
    }

    //Print Clients Balances List.
    void printClientDataAndBalance(Client& client) {
        cout << "|" << formatString(16, client.accountNumber, CENTER);
        cout << "|" << formatString(21, client.fullName, CENTER);
        cout << "|" << formatString(15, to_string(client.balance), CENTER) << "|";
    }
    //[3] Display Total Balance.
    void displayTotalBalance() {
        vector<Client> vClients = loadClientsDataFromFile();
        cout << characters('-', 65) << endl;
        cout << "|" << formatString(63, "| Balance List (" + to_string(vClients.size()) + ") Client(s) |", CENTER) << "|" << endl;
        cout << characters('-', 65) << endl;
        cout << "|" << " Number ";
        cout << "|" << " Account Number ";
        cout << "|" << "      Full Name      ";
        cout << "|" << "  Balance ($)  " << "|" << endl;
        cout << characters('-', 65) << endl;
        if (vClients.size() == 0) {
            cout << "|" << formatString(63, "No clients available in the Bank", CENTER) << "|" << endl;
        }
        else {
            int count = 0;
            double totalBalance = 0;
            for (Client& client : vClients) {
                cout << "|" << formatString(8, to_string(++count), CENTER);
                printClientDataAndBalance(client);
                totalBalance += client.balance;
                cout << "\n";
            }
            cout << characters('-', 65) << endl;
            cout << "|" << formatString(63, "Total Balance = " + to_string(totalBalance) + "$", CENTER) << "|" << endl;
        }
        cout << characters('-', 65) << endl << endl;
    }
    //*************************************************************
}