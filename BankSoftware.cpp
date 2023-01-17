#include <iostream>
#include <string>
#include "user-service.h"
#include "Constant-comands.h"

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
	cout << QUIT_COMMAND << "- quit" << endl;
}

int main() {
	loadUsers();

	string command = "";
	
	 while (true) {
        
        if (loggedUser != nullptr) {
            cout << "You have " << loggedUser->balance << " BGN. " << "Choose one of the following options : " << endl;
            cout << "====================================================" << endl;
            LoggedMenu();
            cout << "====================================================" << endl;
            getline(cin, command);

            if (command == CANCEL_COMMAND) {
                string password;
                cout << "Please enter your password to cancel your account: ";
                cin >> password;
                cout << "====================================================" << endl;
                cin.ignore();
                if (!cancelAccount(password)) {
                    cout << "Please check if your account is with balance 0, else please check your password." << endl;
                    
                }
                else {
                    cout << "Your account is successfully canceled, have a nice day!" << endl;
                }
                pause();
                system("cls");
            }

            else if (command == DEPOSIT_COMMAND) {
                string amount;
                cout << "Please enter how much money you want to deposit: ";
                cin >> amount;
                cout << "====================================================" << endl;
                cin.ignore();
                double amountInDouble = stringToDouble(amount);
                if (!deposit(amountInDouble)) {
                        cout << "Invalid amount of money, it must be between 0-10000 BGN." << endl;
                        pause();
                }
                system("cls");
            }
            
            else if (command == WITHDRAW_COMMAND)
            {
                
                string amount;
                cout << "Please enter how much money you want to withdraw: ";
                cin >> amount;
                cout << "====================================================" << endl;
                double amountInDouble = stringToDouble(amount);
                cin.ignore();
                if (!withdraw(amountInDouble)) {
                    cout << "Invalid amount of money, it must be between 0-10000 BGN and not bigger than your account balance." << endl;
                    pause();
                }   
                system("cls");
            }

            else if (command == TRANSFER_COMMAND)
            {
                string amount;
                string destName = "";
                cout << "Please enter how much money you want to transfer: ";
                cin >> amount;
                cout << "====================================================" << endl;
                double amountInDouble = stringToDouble(amount);
                cin.ignore();
                cout << "Please enter the username to which you want to transfer the money: ";
                getline(cin, destName);
                cout << "====================================================" << endl;
                if (!transfer(destName, amountInDouble)) {
                    cout << "Unfortunately, there is a problem: the amount of money you want to transfer is not between 0-10000 BGN," <<
                        "or an account with this username not exists." << endl;
                }
                pause();
                system("cls");
            }

            else if (command == LOGOUT_COMMAND) {
                logout();
                cout << "You have just logout successfully, have a nice day!" << endl;
                pause();
                system("cls");
            }

            else if (command == QUIT_COMMAND) {
                break;
            }

            else {
                cout << "Not existing command!" << endl;
                pause();
                system("cls");
            }
        }
        
        else {
            cout << "====================GUEST MENU====================" << endl;
            cout << "Enter one of the following options in the menu: " << endl;
            GuestMenu();
            cout << "====================================================" << endl;
            getline(cin, command);

            if (command == LOGIN_COMMAND) {
                string username;
                cout << "Please enter your username: ";
                getline(cin, username);
                cout << "====================================================" << endl;
                string password;
                cout << "Please enter your password: ";
                cin >> password;
                cout << "====================================================" << endl;
                cin.ignore();
                if (!login(username, password)) {
                    cout << "Invalid username or password." << endl;
                    pause();
                }
                system("cls");
            }

            else if (command == REGISTER_COMMAND) {
                string username, password;
                cout << "Please enter your userName(only using latin letters and symbols): ";
                getline(cin, username);
                cout << "====================================================" << endl;
                cout << "Enter yout password(only latin letters, symbols-!@#$%^&* and numbers, it must be at least 5 symbols): ";
                cin >> password;
                cout << "====================================================" << endl;
                cin.ignore();
                cout << create(username, password) << endl;
                pause();
                system("cls");
            }

            else if (command == QUIT_COMMAND) {
                break;
            }

            else {
                cout << "Not existing command!" << endl;
                pause();
                system("cls");
            }
        }
    }

    saveState();

	return 0;
}


