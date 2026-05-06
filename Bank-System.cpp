#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "format.h"
#include "client.h"
#include "user.h"
#include "transactions.h"
#include "input.h"

using namespace std;
using namespace format;
using namespace client;
using namespace user;
using namespace input;
using namespace transactions;

void login();
void handleMainMenu();
void handleTransactionsMenu();
void handleUsersMenu();

enum enMainMenuOption
{
    Show_Client = 1,
    Add_Client = 2,
    Delete_Client = 3,
    Update_Client = 4,
    Find_Client = 5,
    Transaction = 6,
    Users = 7,
    Logout = 8
};

enum enTransactionsMenuOption
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalance = 3,
    ExitTransactionsMenu = 4
};

enum enUsersMenuOption
{
    Show_User = 1,
    Add_User = 2,
    Delete_User = 3,
    Update_User = 4,
    Find_User = 5,
    ExitUsersMenu = 6
};

User currentUser;

void displayLoginMenu()
{
    clearScreen();
    printHeader("| Login |");
}
void displayPermissionsDeniedMenu()
{
    clearScreen();
    printHeader("| Permissions Denied |");
    cout << "\nYou don't have permissions to do this :(" << endl;
    cout << "Please contact your admin...\n"
         << endl;
    cout << "\a";
}
void displayMainMenu()
{
    clearScreen();
    printHeader(" | Bank Management |");
    cout << "|" << "    [1] Show Clients List" << formatString(14, "|", RIGHT) << endl;
    cout << "|" << "    [2] Add New Client" << formatString(17, "|", RIGHT) << endl;
    cout << "|" << "    [3] Delete Client" << formatString(18, "|", RIGHT) << endl;
    cout << "|" << "    [4] Update Client Data" << formatString(13, "|", RIGHT) << endl;
    cout << "|" << "    [5] Find Client" << formatString(20, "|", RIGHT) << endl;
    cout << "|" << "    [6] Transactions" << formatString(19, "|", RIGHT) << endl;
    cout << "|" << "    [7] Manage Users" << formatString(19, "|", RIGHT) << endl;
    cout << "|" << "    [8] Logout" << formatString(25, "|", RIGHT) << endl;
    printFooter("| Made By 3HD ", RIGHT);
}
void displayTransactionsMenu()
{
    clearScreen();
    printHeader("| Transactions |");
    cout << "|" << "    [1] Deposit" << formatString(24, "|", RIGHT) << endl;
    cout << "|" << "    [2] Withdraw" << formatString(23, "|", RIGHT) << endl;
    cout << "|" << "    [3] Total Balance" << formatString(18, "|", RIGHT) << endl;
    cout << "|" << "    [4] Exit" << formatString(27, "|", RIGHT) << endl;
    cout << characters('-', 40) << endl;
}
void displayUsersMenu()
{
    clearScreen();
    printHeader(" | Users |");
    cout << "|" << "    [1] Show Users List" << formatString(16, "|", RIGHT) << endl;
    cout << "|" << "    [2] Add New User" << formatString(19, "|", RIGHT) << endl;
    cout << "|" << "    [3] Delete User" << formatString(20, "|", RIGHT) << endl;
    cout << "|" << "    [4] Update User Data" << formatString(15, "|", RIGHT) << endl;
    cout << "|" << "    [5] Find User" << formatString(22, "|", RIGHT) << endl;
    cout << "|" << "    [6] Exit" << formatString(27, "|", RIGHT) << endl;
    cout << characters('-', 40) << endl;
}

// Perform Users Menu Option;
void performUsersMenuOption(enUsersMenuOption choice)
{
    switch (choice)
    {
    case enUsersMenuOption::Show_User:
        clearScreen();
        showUsersList();
        pauseScreen("Press ENTER key to back to users menu...");
        handleUsersMenu();
        break;
    case enUsersMenuOption::Add_User:
        clearScreen();
        addUser();
        pauseScreen("Press ENTER key to back to users menu...");
        handleUsersMenu();
        break;
    case enUsersMenuOption::Delete_User:
        clearScreen();
        removeUser();
        pauseScreen("Press ENTER key to back to users menu...");
        handleUsersMenu();
        break;
    case enUsersMenuOption::Update_User:
        clearScreen();
        updateUser();
        pauseScreen("Press ENTER key to back to users menu...");
        handleUsersMenu();
        break;
    case enUsersMenuOption::Find_User:
        clearScreen();
        searchForUser();
        pauseScreen("Press ENTER key to back to users menu...");
        handleUsersMenu();
        break;
    case enUsersMenuOption::ExitUsersMenu:
        break;
    default:
        cout << "Error!" << endl;
        break;
    }
}
// Show Users Menu.
void handleUsersMenu()
{
    displayUsersMenu();
    enUsersMenuOption choice = enUsersMenuOption(readNumberInRange("Choose any service [1 -> 6] : ", 1, 6));
    performUsersMenuOption(choice);
}

// Perform Transactions Menu Option;
void performTransactionsMenuOption(enTransactionsMenuOption choice)
{
    switch (choice)
    {
    case enTransactionsMenuOption::Deposit:
        clearScreen();
        deposit();
        pauseScreen("Press ENTER key to back to transactions menu...");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::Withdraw:
        clearScreen();
        withdraw();
        pauseScreen("Press ENTER key to back to transactions menu...");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::TotalBalance:
        clearScreen();
        displayTotalBalance();
        pauseScreen("Press ENTER key to back to transactions menu...");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::ExitTransactionsMenu:
        break;
    default:
        cout << "Error!" << endl;
    }
}
// Show Transactions Menu.
void handleTransactionsMenu()
{
    displayTransactionsMenu();
    enTransactionsMenuOption choice = enTransactionsMenuOption(readNumberInRange("Choose any transaction [1 -> 4] : ", 1, 4));
    performTransactionsMenuOption(choice);
}

// Perform Main Menu Option.
void performMainMenuOption(enMainMenuOption choice)
{
    switch (choice)
    {
    case enMainMenuOption::Show_Client:
        if (hasPermission(currentUser.permission, enPermissions::ShowClientList))
        {
            clearScreen();
            showClientsList();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Add_Client:
        if (hasPermission(currentUser.permission, enPermissions::AddClient))
        {
            clearScreen();
            addClient();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Delete_Client:
        if (hasPermission(currentUser.permission, enPermissions::DeleteClient))
        {
            clearScreen();
            removeClient();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Update_Client:
        if (hasPermission(currentUser.permission, enPermissions::UpdateClient))
        {
            clearScreen();
            updateClient();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Find_Client:
        if (hasPermission(currentUser.permission, enPermissions::FindClient))
        {
            clearScreen();
            searchForClient();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Transaction:
        if (hasPermission(currentUser.permission, enPermissions::Transactions))
        {
            handleTransactionsMenu();
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Users:
        if (hasPermission(currentUser.permission, enPermissions::ManageUsers))
        {
            handleUsersMenu();
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            pauseScreen("Press ENTER key to back to main menu...");
            handleMainMenu();
        }
        break;
    case enMainMenuOption::Logout:
        login();
        break;
    default:
        cout << "Error!" << endl;
        break;
    }
}
// Show Main Menu.
void handleMainMenu()
{
    displayMainMenu();
    enMainMenuOption choice = enMainMenuOption(readNumberInRange("Choose any service [1 -> 8] : ", 1, 8));
    performMainMenuOption(choice);
}

// Find User In File.
bool isUserFound(User userInfo)
{
    vector<User> vUsers = loadUsersDataFromFile();
    for (User user : vUsers)
    {
        if (userInfo.username == user.username && userInfo.password == user.password)
        {
            currentUser = user;
            return true;
        }
    }
    return false;
}
// Read Login Info.
User readLoginInfo()
{
    User user;
    user.username = readString("Enter user name : ");
    user.password = readString("Enter password : ");
    return user;
}
// Login Menu
void login()
{
    displayLoginMenu();
    bool isFound = false;
    do
    {
        User user = readLoginInfo();
        if (isUserFound(user))
        {
            isFound = true;
            handleMainMenu();
        }
        else
        {
            displayLoginMenu();
            cout << "Invaled username/password :(" << endl;
        }
    } while (isFound == false);
}

// Start App.
int main()
{
    login();
    return 0;
}