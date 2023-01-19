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
*<file with user-service function>
*
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "user-information.h"
#include "Constant-comands.h"
#include "user-service.h"
#include <iomanip>
using namespace std;

struct  UserInfo;
vector<UserInfo> users;


//double stringToDouble(string str) {
//	double result = 0.0;
//	int index = 0;
//	for (int i = 0; i < str.size();i++) {
//		if (str[i] == '.' || str[i] == ',') {
//			index = i;
//			break;
//		}
//		if (str[i] == '\0') {
//			index = i;
//			break;
//		}
//
//		result *= 10;
//		result += (double)(str[i] - '0');
//	}
//	int power = 1;
//	for (int i = index + 1; i < str.size(); i++) {
//
//		if (str[i] == '\0') {
//			break;
//		}
//		result += (double)((str[i] - '0') / pow(10, power));
//		power++;
//	}
//	return result;
//}

int numbersAfterComa(string str) {
	int i = 0;
	if (str[0] == '-') {
		i++;
	}
	bool coma = false;
	int counter = 0;
	for (int j = i;str[j] != '\0';j++) {
		if (coma) {
			counter++;
		}
		if (str[j] == ',' || str[j] == '.') {
			coma = true;
		}
	}

	return  counter;
}
double stringToDouble(string str)
{
	double number = 0.0;
	int minus = 1;
	int i = 0;
	if (str[0] == '-') {
		minus = -1;
		i++;
	}
	for (int j = i;str[j] != '\0';j++) {
		if (str[j] == '.' || str[j] == ',') {
			continue;
		}
		number = number * 10 + (str[j] - '0') * 10 * minus;
	}
	int digitsAfterComa = numbersAfterComa(str);
	digitsAfterComa++;

	while (digitsAfterComa > 0) {
		number /= 10;
		digitsAfterComa--;
	}

	return number;
}

void loadUsers()
{
	std::ifstream file("users.txt");

	if (!file.is_open()) {
		cerr << "Error: unable to open file for reading" << endl;
		return;
	}

	string current;
	while (!file.eof())
	{
		getline(file, current);
		if (current.size() == 0) {
			break;
		}
		UserInfo user;
		int i = 0;
		while (current[i] != ':')
		{
			user.username.push_back(current[i]);
			++i;
		}
		++i; //going after first :
		string curPass;
		while (current[i] != ':')
		{
			curPass.push_back(current[i]);
			++i;
		}
		user.password = stoi(curPass);

		++i; //going after second :

		string curBalance;
		while (i < current.size()) {//check if '\0' is better
			curBalance.push_back(current[i]);
			++i;
		}

		user.balance = stringToDouble(curBalance);
		users.push_back(user);
	}
	
}

bool validateUsername(string name)
{
	for (int i = 0; i < name.size(); i++) {
		if (name[i] < ' ' && name[i] > '~') {
			return false;
		}
		if (name[i] >= '0' && name[i] <= '9') {
			return false;
		}
	}
	return true;
}

bool validatePassword(string password)
{
	int j = 0;
	while (password[j] != '\0') {
		j++;
	}
	if (j < 5) {
		return false;
	}
	int smallLetter = 0;
	int bigLetter = 0;
	int symbol = 0;
	int length = 0;
	for (int i = 0; i < password.size(); i++) {
		char temp = password[i];
		if (password[i] >= 'a' && password[i] <= 'z') {
			smallLetter++;
		}
		else if (password[i] >= 'A' && password[i] <= 'Z') {
			bigLetter++;
		}
		else if ((password[i] >= '0' && password[i] <= '9')) {
		}
		else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' ||
			password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*') {
			symbol++;
		}
		else {
			return false;
		}
	}

	return smallLetter > 0 && bigLetter > 0 && symbol > 0;
}

bool existsByUsername(string username) {
	for (int i = 0; i < users.size(); ++i) {
		if (users[i].username == username) {
			return true;
		}
	}
	return false;
}

int hashPassword(string password) {
	hash<string> hasher;
	return hasher(password);
}

UserInfo* getUser(string username) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].username == username) {
			return &users[i];
		}
	}
	return nullptr;
}

bool login(string username, string password,UserInfo* &user) {

	user = getUser(username);
	if (user != nullptr && user->password == hashPassword(password)) {
	
		return true;
	}
	return false;
}

void logout(UserInfo* &loggedUser) {
	loggedUser = nullptr;
}

//Always called when loggedUser is nullptr
string create(string username, string password, UserInfo* &loggedUser) {
	if (!validateUsername(username)) {
		return INVALID_USERNAME;
	}
	if (!validatePassword(password)) {
		return INVALID_PASSWORD;
	}
	if (existsByUsername(username)) {
		return EXISTING_USERNAME_ALREADY;
	}

	UserInfo user(username, hashPassword(password), 0);//the same as -> UserInfo user = { username, hashPassword(password), 0 };
	users.push_back(user);

	loggedUser = &users.back();// Returns direct reference to the last element of the vector container.

	return REGISTERED_SUCCESSFULLY_MESSAGE;
}

bool checkPassword(string password, UserInfo* &loggedUser) {//pointer to something and reference that change the value of the pointer 
	return hashPassword(password) == loggedUser->password;
	//loggedUser->password  <=>   (*loggedUser).password
}

bool cancelAccount(string password, UserInfo* &loggedUser) {
	if (checkPassword(password,loggedUser) && loggedUser->balance == 0) {
		for (int i = 0; i < users.size(); ++i) {
			if (users[i].username == loggedUser->username) {
				users.erase(users.begin() + i);
				logout(loggedUser);
				return true;
			}
		}
	}
	return false;
}

bool deposit(double amount, UserInfo* &loggedUser) {

	if (amount < 0 || amount > 10000) {
		return false;
	}
	//double newAmount = floor(amount * 100) / 100;// from 1.234 - to-> 1.23
	loggedUser->balance += floor(amount * 100) / 100;
	return true;
}

bool withdraw(double amount, UserInfo* &loggedUser) {
	double newAmount = floor(amount * 100) / 100;
	if (newAmount < 0 || newAmount > 10000 || loggedUser->balance-newAmount < MIN) {
		return false;
	}
	/*double newAmount = floor(amount * 100) / 100;*/
	loggedUser->balance -= newAmount;
	return true;
}

bool transfer(string username, double amount,UserInfo* &loggedUser) {
	double newAmount = floor(amount * 100) / 100;
	if (newAmount < 0 || newAmount > 10000 || (loggedUser->balance-newAmount < MIN)) {
		return false;
	}
	
	UserInfo* foundUser = getUser(username);
	if (foundUser != nullptr) {
		foundUser->balance += newAmount;
		loggedUser->balance -= newAmount;
		return true;
	}
	return false;
}


bool saveState() {
	ofstream writeToFile("users.txt");

	if (!writeToFile.is_open()) {
		cerr << "Error while opening the file." << endl;
		return false;
	}

	for (int i = 0; i < users.size(); i++) {
		writeToFile << users[i].username << ":" << users[i].password << ":" << users[i].balance << endl;
	}

	writeToFile.close();
	return true;
}

void pause()
{
	cin.sync();
	cout << "... press enter to continue ...";
	cin.get();
}