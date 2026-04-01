#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype> 
#include <vector> 
#include "format.h"

using namespace std;
using namespace format;

namespace user {
    //*************************************************************
    //User Functions.
    //*************************************************************
    //User Members.
    struct User {
        string username = "";
        string password = "";
        short permission;
    };
    enum enPermissions {
        AllPermissions = -1,
        ShowClientList = 1,
        AddClient = 2,
        DeleteClient = 4,
        UpdateClient = 8,
        FindClient = 16,
        Transactions = 32,
        ManageUsers = 64
    };
    //Make Clients Data File Be In The Project Folder.
    const string fileName_USERS = "users.txt";
    //Counvert Line That Has User Data To Record.
    User convertLineToRecord_USER(string& line) {
        User userRecord;
        vector < string > vUserData = format::splitString(line, ",");
        userRecord.username = vUserData[0];
        userRecord.password = vUserData[1];
        userRecord.permission = stoi(vUserData[2]);
        return userRecord;
    }
    //Load Users Data From File To Recoed.
    vector < User > loadUsersDataFromFile() {
        vector < User > vUsers;
        fstream file;
        file.open(fileName_USERS, ios::in);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line != "") {
                    vUsers.push_back(convertLineToRecord_USER(line));
                }
            }
        }
        file.close();
        return vUsers;
    }
    //Load Users Data From File To Vector.
    vector < User > vUsers = loadUsersDataFromFile();
    //Counvert User Recorded Data To Line.
    string convertRecordToLine(User userRecord, string separator) {
        string userDataInLine = "";
        userDataInLine += userRecord.username + separator;
        userDataInLine += userRecord.password + separator;
        userDataInLine += to_string(userRecord.permission);
        return userDataInLine;
    }
    //Save Users Data From Vector To File After Counvert Them To Lines.
    void saveUsersDataFromVectorToFile() {
        fstream file;
        file.open(fileName_USERS, ios::out);
        if (file.is_open()) {
            for (User& userRecord : vUsers) {
                file << convertRecordToLine(userRecord, ",") << endl;
            }
        }
        file.close();
    }
    //Add New Client Data To File.
    void addUserDataToFile(User& user) {
        fstream file;
        file.open(fileName_USERS, ios::out | ios::app);
        if (file.is_open()) {
            file << convertRecordToLine(user, ",") << endl;
        }
        file.close();
    }
    //*************************************************************
    //Validation Functions.
    //*************************************************************
    //Check Username If Is Valid.
    bool isValidUsername(string& username) {
        if (username.size() < 4) {
            return false;
        }
        return true;
    }
    //Check Password If Is Valid.
    bool isValidPassword(string& password) {
        if (password.size() < 8) {
            return false;
        }
        return true;
    }
    //If User Has Permissions.
    bool hasPermission(short userPermissions, short permissionToCheck) {
        return ((userPermissions & permissionToCheck) == permissionToCheck);
    }
    //*************************************************************
    //Input Functions.
    //*************************************************************
    //Read Username And Check It If Valid.
    string readUsername() {
        string username;
        bool isExisted;
        cout << "Enter username : ";
        do {
            isExisted = false;
            getline(cin >> ws, username);
            if (isValidUsername(username)) {
                for (User& user : vUsers) {
                    if (user.username == username) {
                        cout << "\nUser with (" << username << ") already exists, enter another one : ";
                        isExisted = true;
                        break;
                    }
                }
            }
            else {
                cout << "\nInvalid username, enter a valid username : ";
                isExisted = true;
            }
        } while (isExisted);
        return username;
    }
    //Read Password And Check It If Valid.
    string readPassword() {
        string password;
        cout << "Enter password : ";
        getline(cin >> ws, password);
        while (!isValidUsername(password)) {
            cout << "\nInvalid password, enter a valid password : ";
            getline(cin >> ws, password);
        }
        return password;
    }
    //Read Permission And Check It If Valid.
    short readPermissions() {
        char fullAccess = readChar("\nDo you want to give user full access ? Y / N ? ");
        if (toupper(fullAccess) == 'Y') {
            return enPermissions::AllPermissions;
        }
        else {
            short permissions = 0;
            char choice;
            cout << "\nDo you want to give user access to :" << endl;
            choice = readChar("\nShow client list ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::ShowClientList;
            }
            choice = readChar("\nAdd new client ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::AddClient;
            }
            choice = readChar("\nDelete client ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::DeleteClient;
            }
            choice = readChar("\nUpdate client ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::UpdateClient;
            }
            choice = readChar("\nFind client ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::FindClient;
            }
            choice = readChar("\nMake transaction ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::Transactions;
            }
            choice = readChar("\nManage users ? Y / N ? ");
            if (toupper(choice) == 'Y') {
                permissions = permissions | enPermissions::ManageUsers;
            }
            return permissions;
        }
    }
    //*************************************************************
    //Client Functions.
    //*************************************************************
    //Print User Data.
    void displayUserData(User& user) {
        cout << "|" << formatString(30, user.username, CENTER);
        cout << "|" << formatString(30, user.password, CENTER);
        cout << "|" << formatString(16, to_string(user.permission), CENTER) << "|";
    }
    //[1] Show Users List.
    void showUsersList() {
        cout << characters('-', 91) << endl;
        cout << "|" << formatString(89, "| Users List (" + to_string(vUsers.size()) + ") User(s) |", CENTER) << "|" << endl;
        cout << characters('-', 91) << endl;
        cout << "|" << formatString(10, "Number", CENTER);
        cout << "|" << formatString(30, "Username", CENTER);
        cout << "|" << formatString(30, "Password", CENTER);
        cout << "|" << formatString(16, "Permission", CENTER) << "|";
        cout << "\n" << characters('-', 91) << endl;
        if (vUsers.size() == 0) {
            cout << "|" << formatString(89, "No users available in the Bank", CENTER) << "|" << endl;
        }
        else {
            int count = 0;
            for (User& user : vUsers) {
                cout << "|" << formatString(10, to_string(++count), CENTER);
                displayUserData(user);
                cout << "\n";
            }
        }
        cout << characters('-', 91) << endl << endl;
    }

    //Read New User Data.
    User readNewUserData() {
        User user;
        user.username = readUsername();
        user.password = readPassword();
        user.permission = readPermissions();
        return user;
    }
    //[2] Add User To Users List.
    void addUser() {
        printHeader("Add New User");
        cout << endl;
        User user = readNewUserData();
        vUsers.push_back(user);
        cout << "\nUser added successfully.\n" << endl;
        addUserDataToFile(user);
    }

    //Check USer If Is Found Or Not.
    bool isUserFound(string username, User& user) {
        for (User& userData : vUsers) {
            if (userData.username == username) {
                user = userData;
                return true;
            }
        }
        return false;
    }

    //Delete User Data.
    void deleteUserData(string usernameToDelete) {
        vector <User>::iterator it;
        for (int i = 0; i < vUsers.size(); ++i) {
            if (vUsers[i].username == usernameToDelete) {
                vUsers.erase(vUsers.begin() + i);
                break;
            }
        }
    }
    //Show User Data.
    void showUserData(User& user) {
        cout << "\n" << characters('-', 18) << endl;
        cout << "| User Data      |" << endl;
        cout << characters('-', 48) << endl;
        cout << "| Username       | " << formatString(27, user.username) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| Password       | " << formatString(27, user.password) << " | " << endl;
        cout << characters('-', 48) << endl;
        cout << "| Permission     | " << formatString(27, to_string(user.permission)) << " | " << endl;
        cout << characters('-', 48) << endl;
    }
    //[3] Delete User From Users List.
    void removeUser() {
        printHeader("Delete User");
        User user;
        string usernameToDelete = readString("\nEnter username : ");
        if (usernameToDelete == "Admin") {
            cout << "\nYou can't delete the admin :(\n" << endl;
        }
        else {
            if (isUserFound(usernameToDelete, user)) {
                showUserData(user);
                char choice = readChar("\nAre you sure you want to delete this user? Y / N ? ");
                if (toupper(choice) == 'Y') {
                    deleteUserData(usernameToDelete);
                    cout << "\nUser deleted successfully." << endl;
                    saveUsersDataFromVectorToFile();
                }
                cout << endl;
            }
            else {
                cout << "\nUser with username (" << usernameToDelete << ") is not found :(\n" << endl;
            }
        }
    }

    //Read New Client Data To Update Them.
    User changeUserData(string username) {
        User newUserData;
        newUserData.username = username;
        newUserData.password = readPassword();
        newUserData.permission = readPermissions();
        return newUserData;
    }
    //Update User Data.
    void updateUserData(string usernameToUpdate) {
        User newUserData = changeUserData(usernameToUpdate);
        for (User& userData : vUsers) {
            if (userData.username == usernameToUpdate) {
                userData = newUserData;
                break;
            }
        }
    }
    //[4] Update User Data.
    void updateUser() {
        printHeader("Update User Data");
        User user;
        string usernameToUpdate = readString("\nEnter username : ");
        if (usernameToUpdate == "Admin") {
            cout << "\nYou can't update the admin :(\n" << endl;
        }
        else {
            if (isUserFound(usernameToUpdate, user)) {
                showUserData(user);
                char choice = readChar("\nAre you sure you want to update this user data? Y / N ? ");
                if (toupper(choice) == 'Y') {
                    updateUserData(usernameToUpdate);
                    cout << "\nUser data updated successfully." << endl;
                    saveUsersDataFromVectorToFile();
                }
                cout << endl;
            }
            else {
                cout << "\nUser with username (" << usernameToUpdate << ") is not found :(\n" << endl;
            }
        }
    }

    //Find User.
    void searchForUser() {
        printHeader("Find User");
        User user;
        string usernameToFind = readString("\nEnter username : ");
        if (isUserFound(usernameToFind, user)) {
            showUserData(user);
            cout << endl;
        }
        else {
            cout << "\nUser with username (" << usernameToFind << ") is not found :(\n" << endl;
        }
    }
    //*************************************************************
}