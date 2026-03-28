#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "format.h"

using namespace std;
using namespace format;

void handleMainMenu();
void handleTransactionsMenu();

//Const Variables.
struct Client {
    string accountNumber = "";
    string pinCode = "";
    string fullName = "";
    string phoneNumber = "";
    double balance = 0;
};

enum enMainMenuOption {
    Show = 1,
    Add = 2,
    Delete = 3,
    Update = 4,
    Find = 5,
    Transaction = 6,
    ExitMainMenu = 7
};

enum enTransactionsMenuOption {
    Deposit = 1,
    Withdraw = 2,
    TotalBalance = 3,
    ExitTransactionsMenu = 4
};

//Make Clients Data File Be In The Project Folder.
const string fileName = "clients.txt";

//Print Menu Form.
void printHeader(string header, enAlign align = CENTER) {
    cout << characters('-', 40) << endl;
    cout << "|" << formatString(38, header, align) << "|" << endl;
    cout << characters('-', 40) << endl;
}
void printFooter(string footer, enAlign align = CENTER) {
    cout << characters('-', 40) << endl;
    cout << "|" << formatString(38, footer, align) << "|" << endl;
    cout << characters('-', 40) << endl;
}
void displayMainMenu() {
    system("cls");
    printHeader(" | Bank Management |");
    cout << "|" << "    [1] Show Clients List" << formatString(14, "|", RIGHT) << endl;
    cout << "|" << "    [2] Add New Client" << formatString(17, "|", RIGHT) << endl;
    cout << "|" << "    [3] Delete Client" << formatString(18, "|", RIGHT) << endl;
    cout << "|" << "    [4] Update Client Data" << formatString(13, "|", RIGHT) << endl;
    cout << "|" << "    [5] Find Client" << formatString(20, "|", RIGHT) << endl;
    cout << "|" << "    [6] Transactions" << formatString(19, "|", RIGHT) << endl;
    cout << "|" << "    [7] Exit" << formatString(27, "|", RIGHT) << endl;
    printFooter("| Made By 3HD ", RIGHT);
}
void displayTransactionsMenu() {
    system("cls");
    printHeader("| Transactions |");
    cout << "|" << "    [1] Deposit" << formatString(24, "|", RIGHT) << endl;
    cout << "|" << "    [2] Withdraw" << formatString(23, "|", RIGHT) << endl;
    cout << "|" << "    [3] Total Balance" << formatString(18, "|", RIGHT) << endl;
    cout << "|" << "    [4] Main Menu" << formatString(22, "|", RIGHT) << endl;
    cout << characters('-', 40) << endl;
}

//Split Line That Has Client Data To Vector Of String.
vector < string > splitString(string sentence, string delimiter) {
    vector < string > words;
    short position;
    string word = "";
    while ((position = sentence.find(delimiter)) != std::string::npos) {
        word = sentence.substr(0, position);
        if (word != "") {
            words.push_back(word);
        }
        sentence.erase(0, position + delimiter.length());
    }
    if (sentence != "") {
        words.push_back(sentence);
    }
    return words;
}
//Counvert Line That Has Client Data To Record.
Client convertLineToRecord(string& line) {
    Client clientRecord;
    vector < string > vClientData = splitString(line, "#//#");
    clientRecord.accountNumber = vClientData[0];
    clientRecord.pinCode = vClientData[1];
    clientRecord.fullName = vClientData[2];
    clientRecord.phoneNumber = vClientData[3];
    clientRecord.balance = stod(vClientData[4]);
    return clientRecord;
}
//Load Client Data From File To Recoed.
vector < Client > loadClientsDataFromFile() {
    vector < Client > vClients;
    fstream file;
    file.open(fileName, ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vClients.push_back(convertLineToRecord(line));
        }
    }
    file.close();
    return vClients;
}

//Load Clients Data From File To Vector.
vector < Client > vClients = loadClientsDataFromFile();

//Counvert Client Recorded Data To Line.
string convertRecordToLine(Client clientRecord, string separator) {
    string clientDataInLine = "";
    clientDataInLine += clientRecord.accountNumber + separator;
    clientDataInLine += clientRecord.pinCode + separator;
    clientDataInLine += clientRecord.fullName + separator;
    clientDataInLine += clientRecord.phoneNumber + separator;
    clientDataInLine += to_string(clientRecord.balance);
    return clientDataInLine;
}
//Save Clients Data From Vector To File After Counvert Them To Lines.
void saveDataFromVectorToFile() {
    fstream file;
    file.open(fileName, ios::out);
    if (file.is_open()) {
        for (Client& clientRecord : vClients) {
            file << convertRecordToLine(clientRecord, "#//#") << endl;
        }
    }
    file.close();
}

//Print Client Data.
void displayClientData(Client& client) {
    cout << "|" << formatString(16, client.accountNumber, CENTER);
    cout << "|" << formatString(10, client.pinCode, CENTER);
    cout << "|" << formatString(21, client.fullName, CENTER);
    cout << "|" << formatString(14, client.phoneNumber, CENTER);
    cout << "|" << formatString(15, to_string(client.balance), CENTER) << "|";
}
//[1] Show Clients List.
void showClientsList() {
    cout << characters('-', 91) << endl;
    cout << "|" << formatString(89, "| Client List (" + to_string(vClients.size()) + ") Client(s) |", CENTER) << "|" << endl;
    cout << characters('-', 91) << endl;
    cout << "|" << " Number ";
    cout << "|" << " Account Number ";
    cout << "|" << " PIN Code ";
    cout << "|" << "      Full Name      ";
    cout << "|" << " Phone Number ";
    cout << "|" << "  Balance ($)  " << "|";
    cout << "\n" << characters('-', 91) << endl;
    if (vClients.size() == 0) {
        cout << "|" << formatString(89, "No clients available in the Bank", CENTER) << "|" << endl;
    }
    else {
        int count = 0;
        for (Client& client : vClients) {
            cout << "|" << formatString(8, to_string(++count), CENTER);
            displayClientData(client);
            cout << "\n";
        }
    }
    cout << characters('-', 91) << endl << endl;
}

//Check Account Number If Is Available.
bool isValidAccountNumber(string &accountNumber) {
    if (accountNumber.size() == 0) {
        return false;
    }
    for (short i = 0; i < accountNumber.size(); i++) {
        if (ispunct(accountNumber[i]) || accountNumber[i] == ' ') {
            return false;
        }
    }
    return true;
}
//Read Account Number And Check It If Existed.
string readAccountNumber() {
    string accountNumber;
    bool isExisted;
    cout << "Enter account number : ";
    do {
        isExisted = false;
        getline(cin >> ws, accountNumber);
        if (isValidAccountNumber(accountNumber)) {
            for (Client& client : vClients) {
                if (client.accountNumber == accountNumber) {
                    cout << "\nClient with (" << accountNumber << ") already exists, enter another one : ";
                    isExisted = true;
                    break;
                }
            }
        }
        else {
            cout << "\nInvalid account number, enter a valid account number : ";
            isExisted = true;
        }
    } while (isExisted);
    return accountNumber;
}
//Check PIN Code If Is Valid.
bool isValidPinCode(string &pinCode) {
    if (pinCode.size() < 4) {
        return false;
    }
    for (short i = 0; i < pinCode.size(); i++) {
        if (ispunct(pinCode[i]) || pinCode[i] == ' ') {
            return false;
        }
    }
    return true;
}
//Read PIN Code And Check It If Valid.
string readPinCode() {
    string pinCode;
    cout << "Enter PIN code : ";
    getline(cin >> ws, pinCode);
    while (!isValidPinCode(pinCode)) {
        cout << "\nInvalid PIN code, enter a valid PIN code : ";
        getline(cin >> ws, pinCode);
    }
    return pinCode;
}
//Check PIN Code If Is Valid.
bool isValidFullName(string &fullName) {
    if (fullName.size() < 4) {
        return false;
    }
    for (short i = 0; i < fullName.size(); i++) {
        if (ispunct(fullName[i])) {
            return false;
        }
    }
    return true;
}
//Read PIN Code And Check It If Valid.
string readFullName() {
    string fullName;
    cout << "Enter full name : ";
    getline(cin >> ws, fullName);
    while (!isValidFullName(fullName)) {
        cout << "\nInvalid full name, enter a valid full name : ";
        getline(cin >> ws, fullName);
    }
    return fullName;
}
//Check Phone Number If Is Valid.
bool isValidPhoneNumber(string &phoneNumber) {
    if (phoneNumber.size() < 10) {
        return false;
    }
    if (phoneNumber[0] != '+') {
        phoneNumber = '+' + phoneNumber;
    }
    for (short i = 1; i < phoneNumber.size(); i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    return true;
}
//Read Phone Number And Check It If Valid.
string readPhoneNumber() {
    string phoneNumber;
    cout << "Enter phone number : ";
    getline(cin >> ws, phoneNumber);
    while (!isValidPhoneNumber(phoneNumber)) {
        cout << "\nInvalid phone number, enter a valid phone number : ";
        getline(cin >> ws, phoneNumber);
    }
    return phoneNumber;
}

//Add New Client Data To File.
void addClientDataToFile(Client& client) {
    fstream file;
    file.open(fileName, ios::out | ios::app);
    if (file.is_open()) {
        file << convertRecordToLine(client, "#//#") << endl;
    }
    file.close();
}
//Read New Client Data.
Client readNewClientData() {
    Client client;
    client.accountNumber = readAccountNumber();
    client.pinCode = readPinCode();
    client.fullName = readFullName();
    client.phoneNumber = readPhoneNumber();
    client.balance = readPositiveNumber("Enter balance : ");
    return client;
}
//[2] Add Client To Clients List.
void addClient() {
    printHeader("Add New Client");
    cout << endl;
    Client client = readNewClientData();
    vClients.push_back(client);
    cout << "\nClient added successfully.\n" << endl;
    addClientDataToFile(client);
}

//Check Client If Is Found Or Not.
bool isClientFound(string accountNumber, Client& client) {
    for (Client& clientData : vClients) {
        if (clientData.accountNumber == accountNumber) {
            client = clientData;
            return true;
        }
    }
    return false;
}

//Delete Client Data.
void deleteClientData(string accountNumberToDelete) {
    vector <Client>::iterator it;
    for (int i = 0; i < vClients.size(); ++i) {
        if (vClients[i].accountNumber == accountNumberToDelete) {
            vClients.erase(vClients.begin() + i);
            break;
        }
    }
}
//Show Client Data.
void showClientData(Client& client) {
    cout << "\n" << characters('-', 18) << endl;
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
void removeClient() {
    printHeader("Delete Client");
    Client client;
    string accountNumberToDelete = readString("\nEnter account number : ");
    if (isClientFound(accountNumberToDelete, client)) {
        showClientData(client);
        char choice = readChar("\nAre you sure you want to delete this client? Y / N : ");
        if (toupper(choice) == 'Y') {
            deleteClientData(accountNumberToDelete);
            cout << "\nClient deleted successfully." << endl;
            saveDataFromVectorToFile();
        }
        cout << endl;
    }
    else {
        cout << "\nClient with account number (" << accountNumberToDelete << ") is not found!\n" << endl;
    }
}

//Read New Client Data To Update Them.
Client changeClientData(string accountNumber) {
    Client newClientData;
    newClientData.accountNumber = accountNumber;
    newClientData.pinCode = readPinCode();
    newClientData.fullName = readFullName();
    newClientData.phoneNumber = readPhoneNumber();
    newClientData.balance = readPositiveNumber("Enter balance : ");
    return newClientData;
}
//Update Client Data.
void updateClientData(string accountNumberToUpdate) {
    Client newClientData = changeClientData(accountNumberToUpdate);
    for (Client& clientData : vClients) {
        if (clientData.accountNumber == accountNumberToUpdate) {
            clientData = newClientData;
            break;
        }
    }
}
//[4] Update Client Data.
void updateClient() {
    printHeader("Update Client Data");
    Client client;
    string accountNumberToUpdate = readString("\nEnter account number : ");
    if (isClientFound(accountNumberToUpdate, client)) {
        showClientData(client);
        char choice = readChar("\nAre you sure you want to update this client data? Y / N : ");
        if (toupper(choice) == 'Y') {
            updateClientData(accountNumberToUpdate);
            cout << "\nClient data updated successfully." << endl;
            saveDataFromVectorToFile();
        }
        cout << endl;
    }
    else {
        cout << "\nClient with account number (" << accountNumberToUpdate << ") is not found!\n" << endl;
    }
}

//Find Client.
void searchForClient() {
    printHeader("Find Client");
    Client client;
    string accountNumberToFind = readString("\nEnter account number : ");
    if (isClientFound(accountNumberToFind, client)) {
        showClientData(client);
        cout << endl;
    }
    else {
		cout << "\nClient with account number (" << accountNumberToFind << ") is not found!\n" << endl;
    }
}

//Add Amount To Balance Withdraw/Deposit.
void addAmountToBalance(double amount, string accountNumberForDeposit, string transactionStatus) {
    for (Client& clientData : vClients) {
        if (clientData.accountNumber == accountNumberForDeposit) {
            clientData.balance += amount;
            cout << transactionStatus << "New balance : " << clientData.balance << endl;
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
            addAmountToBalance(amount, accountNumberForDeposit, "\nDeposit successfully, ");
            saveDataFromVectorToFile();
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
            addAmountToBalance(-1 * amount, accountNumberForwithdraw, "\nWithdraw successfully, ");
            saveDataFromVectorToFile();
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
    cout << characters('-', 65) << endl;
    cout << "|" << formatString(63, "| Balance List (" + to_string(vClients.size()) + ") Client(s) |", CENTER) << "|" << endl;
    cout << characters('-', 65) << endl;
    cout << "|" << " Number ";
    cout << "|" << " Account Number ";
    cout << "|" << "      Full Name      ";
    cout << "|" << "    Balance    " << "|" << endl;
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
        cout << "|" << formatString(63, "Total Balance = " + to_string(totalBalance), CENTER) << "|" << endl;
    }
    cout << characters('-', 65) << endl << endl;
}

//Perform Transactions Menu Option;
void performTransactionsMenuOption(enTransactionsMenuOption choice) {
    switch (choice) {
    case enTransactionsMenuOption::Deposit:
        system("cls");
        deposit();
        system("pause");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::Withdraw:
        system("cls");
        withdraw();
        system("pause");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::TotalBalance:
        system("cls");
        displayTotalBalance();
        system("pause");
        handleTransactionsMenu();
        break;
    case enTransactionsMenuOption::ExitTransactionsMenu:
        break;
    default:
        cout << "Error!" << endl;
    }
}

//Show Transactions Menu.
void handleTransactionsMenu() {
    displayTransactionsMenu();
    enTransactionsMenuOption choice = enTransactionsMenuOption(readNumberInRange("Choose any transaction [1 -> 4] : ", 1, 4));
    performTransactionsMenuOption(choice);
}

//Perform Main Menu Option.
void performMainMenuOption(enMainMenuOption choice) {
    switch (choice) {
    case enMainMenuOption::Show:
        system("cls");
        showClientsList();
        system("pause");
        handleMainMenu();
        break;
    case enMainMenuOption::Add:
        system("cls");
        addClient();
        system("pause");
        handleMainMenu();
        break;
    case enMainMenuOption::Delete:
        system("cls");
        removeClient();
        system("pause");
        handleMainMenu();
        break;
    case enMainMenuOption::Update:
        system("cls");
        updateClient();
        system("pause");
        handleMainMenu();
        break;
    case enMainMenuOption::Find:
        system("cls");
        searchForClient();
        system("pause");
        handleMainMenu();
        break;
    case enMainMenuOption::Transaction:
        system("cls");
        handleTransactionsMenu();
        handleMainMenu();
        break;
    case enMainMenuOption::ExitMainMenu:
        system("cls");
        printHeader(" | Program End |");
        system("pause");
        system("cls");
        break;
    default:
        cout << "Error!" << endl;
        break;
    }
}

//Show Main Menu.
void handleMainMenu() {
    displayMainMenu();
    enMainMenuOption choice = enMainMenuOption(readNumberInRange("Choose any service [1 -> 7] : ", 1, 7));
    performMainMenuOption(choice);
}

//Start App.
int main() {    
    handleMainMenu();
    return 0;
}



