/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022 / 2023
*
*@author Viktoria Koleva
*@idnumber 5MI0600139 * @compiler VC
*
*<file with main function>
*
*/

#include<iostream>
#include<string>
#include <vector>
#include <iomanip>
#include "Constant-comands.h"
#include "user-information.h"
#include "user-service.h"

using namespace std;

void GuestMenu() {
    cout << LOGIN_COMMAND << " - login" << endl;
    cout << REGISTER_COMMAND << " - register" << endl;
    cout << QUIT_COMMAND << " - quit" << endl;
}

void LoggedMenu() {
    cout << CANCEL_COMMAND << " - cancel account" << endl;
    cout << DEPOSIT_COMMAND << " - deposit" << endl;
    cout << LOGIN_COMMAND << " - logout" << endl;
    cout << TRANSFER_COMMAND << " - transfer" << endl;
    cout << WITHDRAW_COMMAND << " - withdraw" << endl;
    cout << QUIT_COMMAND << " - quit" << endl;
}

int main() {

    vector<UserInfo> users;
    UserInfo* loggedUser = nullptr;

    loadUsers();
    
    string command = "";
    while (true) {
        
        if (loggedUser != nullptr) {
            cout << LOGGED_MENU_OPENNING << endl;
            cout << "You have " << loggedUser->balance << " BGN. " << "Choose one of the following options : " << endl;
            cout << EQUAL_SYMBOL << endl;
            LoggedMenu();
            cout << EQUAL_SYMBOL << endl;
            getline(cin, command);

            if (command == CANCEL_COMMAND) {
                string password;
                cout << USERNAME_TO_CANCEL;
                cin >> password;
                cout << EQUAL_SYMBOL << endl;
                cin.ignore();
                if (!cancelAccount(password,loggedUser)) {
                    cout << ERROR_TO_CANCEL << endl;
                    
                }
                else {
                    loggedUser = nullptr;
                    cout << SUCCESS_MESSAGE_CANCEL << endl;
                }
                pause();
                system("cls");
                saveState();
            }

            else if (command == DEPOSIT_COMMAND) {
                string amount;
                cout << DEPOSIT_AMOUNT;
                cin >> amount;
                cout << EQUAL_SYMBOL << endl;
                cin.ignore();
                if (!(checkAmount(amount))) {
                    cout << INVALID_VALUE << endl;
                    pause();
                }
                else {
                    double amountInDouble = stringToDouble(amount);
                    if (!deposit(amountInDouble, loggedUser)) {
                        cout << TOO_MUCH_AMOUNT_OF_MONEY << endl;
                        pause();
                    }
                }
                system("cls");
                saveState();
            }
            
            else if (command == WITHDRAW_COMMAND) {
                
                string amount;
                cout << WITHDRAW_AMOUNT;
                cin >> amount;
                cout << EQUAL_SYMBOL << endl;
                cin.ignore();
                if (!(checkAmount(amount))) {
                    cout << INVALID_VALUE << endl;
                    pause();
                }
                else {
                    double amountInDouble = stringToDouble(amount);
                    if (!withdraw(amountInDouble, loggedUser)) {
                        cout << TOO_MUCH_AMOUNT_OF_MONEY << endl;
                        pause();
                    }
                }
                system("cls");
                saveState();
            }

            else if (command == TRANSFER_COMMAND) {
                string amount;
                string destName = "";
                cout << TRANSFER_AMOUNT;
                cin >> amount;
                cout << EQUAL_SYMBOL << endl;
                cin.ignore();
                if (!(checkAmount(amount))) {
                    cout << INVALID_VALUE << endl;
                    pause();
                }
                else {
                    double amountInDouble = stringToDouble(amount);
                    cout << SEARCHING_USERNAME;
                    getline(cin, destName);
                    cout << EQUAL_SYMBOL << endl;
                    if (!transfer(destName, amountInDouble, loggedUser)) {
                        cout << ERROR_BEGINNING << endl;
                        cout << POSSIBLE_ERROR_ONE << endl;
                        cout<< POSSIBLE_ERROR_TWO << endl;
                    }
                    else {
                        cout << SUCCESS_TRANSFER << endl;
                    }
                    pause();
                }
                system("cls");
                saveState();
            }

            else if (command == LOGOUT_COMMAND) {
                logout(loggedUser);
                cout << SUCCES_LOGOUT_MESSAGE << endl;
                pause();
                system("cls");
                saveState();
            }

            else if (command == QUIT_COMMAND) {
                break;
            }

            else {
                cout << NOT_EXISTING_COMMAND << endl;
                pause();
                system("cls");
            }
        }
        
        else {
            cout << GUEST_MENU_OPENNING << endl;
            cout << GUEST_MENU_COMMANDS << endl;
            GuestMenu();
            cout << EQUAL_SYMBOL << endl;
            getline(cin, command);

            if (command == LOGIN_COMMAND) {
                string username;
                cout << ADD_USERNAME_TO_LOGIN;
                getline(cin, username);
                cout << EQUAL_SYMBOL << endl;
                string password;
                cout << ADD_PASSWORD_TO_LOGIN;
                cin >> password;
                cout << EQUAL_SYMBOL << endl;
                cin.ignore();
                if (!login(username, password,loggedUser)) {
                    cout << ERROR_TO_LOGIN << endl;
                    loggedUser = nullptr;
                    pause();
                }
                system("cls");
                saveState();
            }

            else if (command == REGISTER_COMMAND) {
                string username, password;
                cout << CREATE_USERNAME;
                getline(cin, username);
                cout << EQUAL_SYMBOL << endl;
                cout << CREATE_PASSWORD << endl;
                cout << STAR_SYMBOLS << endl;
                cout << RULE_ONE << endl;
                cout << STAR_SYMBOLS << endl;
                cout << RULE_TWO << endl;
                cout << STAR_SYMBOLS << endl;
                cout << RULE_THREE << endl;
                cout << STAR_SYMBOLS << endl;
                cout << RULE_FOUR << endl;
                cout << STAR_SYMBOLS << endl;
                cout << ENTER_PASS;
                cin >> password;
                cout << STAR_SYMBOLS << endl;
                cin.ignore();
                cout << create(username, password, loggedUser) << endl;
                pause();
                system("cls");
                saveState();
            }

            else if (command == QUIT_COMMAND) {
                break;
            }

            else {
                cout << NOT_EXISTING_COMMAND << endl;
                pause();
                system("cls");
            }
        }
    }

    saveState();

    return 0;
}
