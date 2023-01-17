#ifndef  ENCODINGPASSWORD_USER_SERVICE_H
#define ENCODINGPASSWORD_USER_SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "user-information.h"
#include "Constant-comands.h"
#include <iomanip>
using namespace std;


vector<UserInfo> users;
bool isLogged = false;
UserInfo loggedUser;



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
	loggedUser = nullptr;
}


double stringToDouble(string str)
{
	double result = 0.0;
	int index = 0;
	for (int i = 0; i < str.size();i++)
	{
		if (str[i] == '.' || str[i] == ',')
		{
			index = i;
			break;
		}
		if (str[i] == '\0')
		{
			index = i;
			break;
		}

		result *= 10;
		result += (double)(str[i] - '0');
	}
	int power = 1;
	for (int i = index + 1; i < str.size(); i++)
	{

		if (str[i] == '\0')
		{
			break;
		}
		result += (double)((str[i] - '0') / pow(10, power));
		power++;
	}
	return result;
}

bool validateUsername(string name)
{
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] < ' ' && name[i] > '~')
		{
			return false;
		}
		if (name[i] >= '0' && name[i] <= '9')
		{
			return false;
		}
	}
	return true;
}

bool validatePassword(string password)
{
	int j = 0;
	while (password[j] != '\0')
	{
		j++;
	}
	if (j < 5)
	{
		return false;
	}
	int smallLetter = 0;
	int bigLetter = 0;
	int symbol = 0;
	int length = 0;
	for (int i = 0; i < password.size(); i++)
	{
		char temp = password[i];
		if (password[i] >= 'a' && password[i] <= 'z')
		{
			smallLetter++;
		}
		else if (password[i] >= 'A' && password[i] <= 'Z')
		{
			bigLetter++;
		}
		else if ((password[i] >= '0' && password[i] <= '9'))
		{
		}
		else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' ||
			password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*')
		{
			symbol++;
		}
		else
		{
			return false;
		}
	}
	return smallLetter > 0 && bigLetter > 0 && symbol > 0;
}

bool existsByUsername(string username) {
	for (int i =0; i< users.size(); ++i) {
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

UserInfo* getUser(string name) {
	for(int i =0; i<user.size();++i) {
		if(users[i].username == username) {
			return &users[i];
		}
	}
	return nullptr;
}
			

bool login(string username, string password) {
	UserInfo* user = getUser(username);
	if(user != nullptr && user->password == hashPassword(password)) {
		loggedUser = user;
		return true;
	}
	return false;
}

void logout() {
	loggedUser = nullptr;
}

string create(string username, string password)
{
	if (!validateUsername(username)) {
		return "Invalid username.";
	}
	if (!validatePassword(password)) {
		return "Invalid password.";
	}
	if (existsByUsername(username)) {
		return "User with the same name already exists.";
	}

	unsigned hashedPassword = hashPassword(password);
	string hash_pass = intToString(hashedPassword);

	UserInfo user = { username, hashPassword(password), 0 };
	users.push_back(user);

	isLogged = true;
	loggedUser = &users.back();
	
	return "You have just registered successfully!";
}

bool checkPassword(string password) {
	return hashPassword(password) == loggedUser->password;
	//loggedUser->password == (*loggedUser).password
}

bool cancelAccount(string password) {
	if(checkPassword(password) == loggedUser->balance == 0) {
		for(int i = 0; i < users.size(); ++i) {
			if(users[i].username == loggedUser->username) {
				users.erase(users.begin() + i);
				logout();
				return true;
			}
		}
	}
	return false;
}

bool deposit(double amount) {
	if (amount < 0 || amount > 10000) {
		return false;
	}	
	loggedUser->balance += floor(amount * 100) / 100;// from 1.234 -- to --> 1.23
	return true;
}

bool withdraw(double amount) {
	if (amount < 0 || amount > 10000 || loggedUser->balance < amount) {
		return false;
	}
	loggedUser->balance -= floor(amount * 100) / 100;
	return true;
}

bool transfer(string username, double amount)
{
	if (amount < 0 || amount > 10000 || loggedUser->balance < amount)
	{
		return false;
	}
	double newAmount = floor(amount * 100) / 100;
	UserInfo* foundUser = getUser(username);
	if(foundUser != nullptr) {
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

	for(int i = 0; i < users.size(); ++i;) {
		writeToFile << users[i].username << ":" << users[i].password << ":" << users[i].balance << endl;
	}

	writeToFile.close();
	return true;
}

void pause() {
	cin.sync();
	cout << "... press enter to continue ...";
	cin.get();
}
#endif // ! ENCODINGPASSWORD_USER_SERVICE_H
