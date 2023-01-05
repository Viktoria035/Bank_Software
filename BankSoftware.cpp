#include <iostream>
#include <string>
#include <fstream>
#include "user-service.h"
#include "global-constants.h"
const std::string FILE_NAME = "users.txt";

void renderGuestMenu() {
	cout << "L" << " - login" << endl;
	cout << "R" << " - register" << endl;
	cout << "Q" << " - quit" << endl;
}

void renderLoggedMenu() {
	cout << "C" << " - cancel account" << endl;
	cout << "D" << " - deposit" << endl;
	cout << "L" << " - logout" << endl;
	cout << "T" << " - transfer" << endl;
	cout << "W" << " - withdraw" << endl;
}

int main() {
	loadUsers();

	string command = "";
	while (command != "Q") {
		if (isLogged) {
			renderLoggedMenu();
		}
		else {
			renderGuestMenu();
		}

		cout << "Enter one of the following commands in the menu" << endl;
		cin >> command;

		if (command == "L") {
			string username, password;
			cin >> username >> password;
			login(username, password);
			if (!isLogged) {
				cout << "Invalid username or password." << endl;
			}
		}
		else if (command == "R") {
			string username, password;
			cin >> username >> password;
			cout << create(username, password);
		}
		//else if (command == CANCEL) {
		//	/*cancelAccount();*/
		//}
	}

	
}


