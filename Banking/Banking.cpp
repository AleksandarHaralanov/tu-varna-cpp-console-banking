#include<iostream>
#include <fstream>
#include <bitset>

using namespace std;

struct Bank {
    char name[20];
    int BGN = 0, EUR = 0, USD = 0;
    int accountNumber;
    int day{}, month{}, year{};
};

void addDepositor(Bank* depositors, int& depositorCount);
void addMultipleDepositors(Bank* depositors, int& depositorCount);
void showBGNDepositors(Bank* depositors, int& depositorCount);
void showMaxEURDepositor(Bank* depositors, int& depositorCount);
void withdrawFunds(Bank* depositors, int& depositorCount);
void saveToBinary(Bank* depositors, int& depositorCount);
int loadFromBinary(Bank* depositors);
void sortDepositors(Bank* depositors, int& depositorCount);

static void createDepositor(Bank* depositors, int& depositorCount, Bank newDepositor) {
    depositors[depositorCount] = newDepositor;
    depositorCount++;
}

int main() {
    Bank depositors[50];
    int depositorCount = loadFromBinary(depositors);
    int choice;

    do {
        cout << "----------------------------------------" << endl;
        cout << "                MAIN MENU" << endl;
        cout << "----------------------------------------" << endl;
        cout << "| 1. Add Depositor                       |" << endl;
        cout << "| 2. Add multiple depositors             |" << endl;
        cout << "| 3. Show all depositors with value BGN  |" << endl;
        cout << "| 4. Show depositor with max deposit EUR |" << endl;
        cout << "| 5. Withdraw                            |" << endl;
        cout << "| 6. Sort profiles                       |" << endl;
        cout << "| 7. Save binary to file                 |" << endl;
        cout << "| 8. Exit                                |" << endl;
        cout << "----------------------------------------" << endl;

        cout << endl << "YOUR CHOICE IS: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addDepositor(depositors, depositorCount);
            break;
        case 2:
            addMultipleDepositors(depositors, depositorCount);
            break;
        case 3:
            showBGNDepositors(depositors, depositorCount);
            break;
        case 4:
            showMaxEURDepositor(depositors, depositorCount);
            break;
        case 5:
            withdrawFunds(depositors, depositorCount);
            break;
        case 6:
            sortDepositors(depositors, depositorCount);
            break;
        case 7:
            saveToBinary(depositors, depositorCount);
            break;
        case 8:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice, please select an option from 1 to 8." << endl;
            break;
        }
    } while (choice != 8);
}

void addDepositor(Bank* depositors, int& depositorCount) {
    Bank newDepositor;
    int depositAmount;
    int choice, deposit = 0;

    cout << endl << "Enter name: ";
    cin.ignore();
    cin >> newDepositor.name;
    cout << endl << "Create account number: ";
    cin >> newDepositor.accountNumber;

    if (newDepositor.accountNumber < 1) {
        cout << "|--------------------------------------|" << endl;
        cout << "| Your account number can't be under 1 |" << endl;
        cout << "|--------------------------------------|" << endl;
        return;
    }

    for (int i = 0; i < depositorCount; i++) {
        if (newDepositor.accountNumber == depositors[i].accountNumber) {
            cout << "This account number already exists, please enter a different number." << endl;
            return;
        }
    }

    cout << "Enter day: ";
    cin >> newDepositor.day;
    cout << "Enter month (in numbers): ";
    cin >> newDepositor.month;
    cout << "Enter year: ";
    cin >> newDepositor.year;

    do {
        cout << endl << "1. New Depositor" << endl;
        cout << "2. Go back to main menu" << endl;
        cout << "Choose option: ";
        cin >> choice;

        if (choice < 1 || choice > 2) {
            cout << "|----------------------|" << endl;
            cout << "| Please select 1 or 2 |" << endl;
            cout << "|----------------------|" << endl;
        }
        else if (choice == 2) {
            return;
        }
    } while (choice < 1 || choice > 2);

    do {
        cout << "1. Deposit" << endl;
        cout << "Choose option: ";
        cin >> choice;

        if (choice != 1) {
            cout << "|---------------------------------|" << endl;
            cout << "| Please select the first option! |" << endl;
            cout << "|---------------------------------|" << endl;
        }
    } while (choice != 1);

    cout << "How many deposits do you want to make? ";
    cin >> depositAmount;

    for (int i = 0; i < depositAmount; i++) {
        if (depositAmount < 1) {
            cout << "|-----------------------------------------|" << endl;
            cout << "| Minimum deposit for your account is 1   |" << endl;
            cout << "| Please try again                        |" << endl;
            cout << "|-----------------------------------------|" << endl;
            return;
        }
        if (depositAmount > 3) {
            cout << "|-----------------------------------------|" << endl;
            cout << "| Maximum deposits for your account is 3  |" << endl;
            cout << "| Please try again                        |" << endl;
            cout << "|-----------------------------------------|" << endl;
            return;
        }

        do {
            cout << "Values:" << endl;
            cout << "1. BGN" << endl;
            cout << "2. USD" << endl;
            cout << "3. EUR" << endl;
            cout << "Choose your value: ";
            cin >> choice;

            if (choice < 1 || choice > 3) {
                cout << "|---------------------------------|" << endl;
                cout << "| Please enter number from 1 to 3 |" << endl;
                cout << "|---------------------------------|" << endl;
            }

            if (choice == 1) {
                int bg1 = 0, bg2 = 0, bg3 = 0;
                if (depositAmount == 3) {
                    cout << "How much do you want to deposit: ";
                    cin >> bg3;
                }
                else {
                    cout << "How much do you want to deposit (Minimum is 500 BGN): ";
                    if (depositAmount == 1) cin >> bg1;
                    if (depositAmount == 2) cin >> bg1 >> bg2;
                    if (bg1 < 500) {
                        cout << "|-------------------------------------------------------|" << endl;
                        cout << "| Minimum deposit is 500 BGN for deposits under 3 times |" << endl;
                        cout << "|-------------------------------------------------------|" << endl << endl;
                        return;
                    }
                }
                newDepositor.BGN += bg1 + bg2 + bg3;
            }

            if (choice == 2) {
                int usd1 = 0, usd2 = 0, usd3 = 0;
                if (depositAmount == 3) {
                    cout << "How much do you want to deposit: ";
                    cin >> usd3;
                }
                else {
                    cout << "How much do you want to deposit (Minimum is 500 USD): ";
                    if (depositAmount == 1) cin >> usd1;
                    if (depositAmount == 2) cin >> usd1 >> usd2;
                    if (usd1 < 500) {
                        cout << "|-------------------------------------------------------|" << endl;
                        cout << "| Minimum deposit is 500 USD for deposits under 3 times |" << endl;
                        cout << "|-------------------------------------------------------|" << endl << endl;
                        return;
                    }
                }
                newDepositor.USD += usd1 + usd2 + usd3;
            }

            if (choice == 3) {
                int eur1 = 0, eur2 = 0, eur3 = 0;
                if (depositAmount == 3) {
                    cout << "How much do you want to deposit: ";
                    cin >> eur3;
                }
                else {
                    cout << "How much do you want to deposit (Minimum is 500 EUR): ";
                    if (depositAmount == 1) cin >> eur1;
                    if (depositAmount == 2) cin >> eur1 >> eur2;
                    if (eur1 < 500) {
                        cout << "|-------------------------------------------------------|" << endl;
                        cout << "| Minimum deposit is 500 EUR for deposits under 3 times |" << endl;
                        cout << "|-------------------------------------------------------|" << endl << endl;
                        return;
                    }
                }
                newDepositor.EUR += eur1 + eur2 + eur3;
            }

        } while (choice < 1 || choice > 3);
    }

    createDepositor(depositors, depositorCount, newDepositor);
    cout << "Depositor added successfully!" << endl;
}

void addMultipleDepositors(Bank* depositors, int& depositorCount) {
    int numDepositors;
    cout << "How many depositors do you want to add? ";
    cin >> numDepositors;

    for (int i = 0; i < numDepositors; i++) {
        addDepositor(depositors, depositorCount);
    }
}

void showBGNDepositors(Bank* depositors, int& depositorCount) {
    if (depositorCount < 1) {
        cout << "|-------------------------------------------------------------|" << endl;
        cout << "| There are no depositors added yet!                          |" << endl;
        cout << "| You can add some by choosing option 1 or 2 in the main menu.|" << endl;
        cout << "|-------------------------------------------------------------|" << endl;
    }
    else {
        cout << "|------------------------------------------|" << endl;
        cout << "| These are all depositors with value BGN  |" << endl;
        cout << "|------------------------------------------|" << endl;

        for (int i = 0; i < depositorCount; i++) {
            if (depositors[i].BGN > 0) {
                cout << "NAME: " << depositors[i].name << endl;
                cout << "MONEY DEPOSIT: " << depositors[i].BGN << " BGN" << endl;
            }
        }
    }
}

void showMaxEURDepositor(Bank* depositors, int& depositorCount) {
    if (depositorCount < 1) {
        cout << "|-------------------------------------------------------------|" << endl;
        cout << "| There are no depositors added yet!                          |" << endl;
        cout << "| You can add some by choosing option 1 or 2 in the main menu.|" << endl;
        cout << "|-------------------------------------------------------------|" << endl;
    }
    else {
        int maxEUR = 0;
        for (int i = 0; i < depositorCount; i++) {
            if (depositors[i].EUR > maxEUR) {
                maxEUR = depositors[i].EUR;
            }
        }

        for (int i = 0; i < depositorCount; i++) {
            if (depositors[i].EUR == maxEUR) {
                cout << "Depositor ( " << depositors[i].name << " ) with ACCOUNT number ( " << depositors[i].accountNumber << " ) has the biggest deposit of ( " << maxEUR << " ) EUR." << endl;
            }
        }
    }
}

void withdrawFunds(Bank* depositors, int& depositorCount) {
    if (depositorCount < 1) {
        cout << "|-------------------------------------------------------------|" << endl;
        cout << "| You haven't deposited yet!                                  |" << endl;
        cout << "| You can deposit by choosing option 1 or 2 in the main menu. |" << endl;
        cout << "|-------------------------------------------------------------|" << endl;
    }
    else {
        int searchAccount;
        cout << "Enter your account number: ";
        cin >> searchAccount;

        for (int i = 0; i < depositorCount; i++) {
            if (searchAccount == depositors[i].accountNumber) {
                int choice, withdrawAmount;

                do {
                    cout << "----------------------------------------------" << endl;
                    cout << "1. Withdraw everything and shut down profile" << endl;
                    cout << "2. Withdraw in BGN" << endl;
                    cout << "3. Withdraw in USD" << endl;
                    cout << "4. Withdraw in EUR" << endl;
                    cout << "Choose option: ";
                    cin >> choice;

                    if (choice < 1 || choice > 4) {
                        cout << "Please select a number between 1 and 4." << endl;
                    }

                    switch (choice) {
                    case 1:
                        depositors[i].BGN = 0;
                        depositors[i].USD = 0;
                        depositors[i].EUR = 0;
                        depositors[i].accountNumber = 0;
                        cout << "Account successfully shut down!" << endl;
                        break;

                    case 2:
                        if (depositors[i].BGN > 0) {
                            cout << "Enter amount to withdraw: ";
                            cin >> withdrawAmount;
                            if (withdrawAmount > depositors[i].BGN) {
                                cout << "You cannot withdraw more than the deposited amount!" << endl;
                            }
                            else {
                                depositors[i].BGN -= withdrawAmount;
                                cout << "Transaction successful. Remaining balance: " << depositors[i].BGN << " BGN" << endl;
                            }
                        }
                        else {
                            cout << "No BGN deposits found." << endl;
                        }
                        break;

                    case 3:
                        if (depositors[i].USD > 0) {
                            cout << "Enter amount to withdraw: ";
                            cin >> withdrawAmount;
                            if (withdrawAmount > depositors[i].USD) {
                                cout << "You cannot withdraw more than the deposited amount!" << endl;
                            }
                            else {
                                depositors[i].USD -= withdrawAmount;
                                cout << "Transaction successful. Remaining balance: " << depositors[i].USD << " USD" << endl;
                            }
                        }
                        else {
                            cout << "No USD deposits found." << endl;
                        }
                        break;

                    case 4:
                        if (depositors[i].EUR > 0) {
                            cout << "Enter amount to withdraw: ";
                            cin >> withdrawAmount;
                            if (withdrawAmount > depositors[i].EUR) {
                                cout << "You cannot withdraw more than the deposited amount!" << endl;
                            }
                            else {
                                depositors[i].EUR -= withdrawAmount;
                                cout << "Transaction successful. Remaining balance: " << depositors[i].EUR << " EUR" << endl;
                            }
                        }
                        else {
                            cout << "No EUR deposits found." << endl;
                        }
                        break;
                    }

                } while (choice < 1 || choice > 4);
            }
        }
    }
}

void saveToBinary(Bank* depositors, int& depositorCount) {
    ofstream outFile("depositors.bin", ios::binary);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    outFile.write((char*)depositors, sizeof(Bank) * depositorCount);
    outFile.close();
    cout << "Depositors data saved successfully!" << endl;
}

int loadFromBinary(Bank* depositors) {
    ifstream inFile("depositors.bin", ios::binary);
    if (!inFile) {
        cout << "No binary file found. Starting with an empty database." << endl;
        return 0;
    }
    inFile.seekg(0, ios::end);
    int fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);
    int depositorCount = fileSize / sizeof(Bank);
    inFile.read((char*)depositors, fileSize);
    inFile.close();
    return depositorCount;
}

void sortDepositors(Bank* depositors, int& depositorCount) {
    for (int i = 0; i < depositorCount; i++) {
        for (int j = i + 1; j < depositorCount; j++) {
            if (depositors[i].year > depositors[j].year ||
                (depositors[i].year == depositors[j].year && depositors[i].month > depositors[j].month) ||
                (depositors[i].year == depositors[j].year && depositors[i].month == depositors[j].month && depositors[i].day > depositors[j].day)) {
                Bank temp = depositors[i];
                depositors[i] = depositors[j];
                depositors[j] = temp;
            }
        }
    }

    cout << "Sorted depositors by creation date." << endl;
}
