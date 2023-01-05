#ifndef  ENCODINGPASSWORD_USER_SERVICE_H
#define ENCODINGPASSWORD_USER_SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "user-information.h"
#include "global-constants.h"
#include <cmath>
#include <unordered_map>

using namespace std;


vector<UserInfo> users;
bool isLogged = false;
UserInfo loggedUser;


//
////void loadUsers()
////{
////	//TODO: load all the users from the file and add them to the users vector
////}
//
//void initUser(User& user, string name, stirng password, string balance)
//{
//	strcpy(user.name, name);
//	strcpy(user.password);
//	strcpy(user.balance);
//}
//
//void writeUserToFile(ofstream& outFile, const User& user)
//{
//	outFile << user.name << ":" << user.password << ":" << user.balance << endl;
//}
//
//User readUser(string line)
//{
//	User toReturn;
//	int size = strlen(line);
//	string buff;
//	int field = 1;
//	for (size_t i = 0, j =0; i <= size ; i++)
//	{
//		if (line[i] == ':' || line[i] == '\n') {
//			buff[j] == '\0';
//
//			switch (field)
//			{
//			case 1: strcpy(toReturn.name, buff); break;
//			case 2: strcpy(toReturn.password, buff);break;
//			}
//			field++;
//			j = 0;
//		}
//		else
//		{
//			buff[j] = line[i];
//			j++;
//		}
//	}
//	strcpy(toReturn.balance, buff);
//	return toReturn;
//}
//
//bool validateUsername(const string& username)//check again!!! and what about space?
//{
//	if (username.find_first_of("0123456789") != string::npos)
//	{
//		return false;
//	}
//	return true;
//}
//
//bool validatePassword(string password)
//{
//	const int PASS_LENGTH = 5;
//	if (password.size() < PASS_LENGTH)
//	{
//		return false;
//	}
//
//	for (int i = 0; i < password.size(); i++)
//	{
//		if ((string[i] < 'A' && string[i]>'Z') && (string[i] < 'a' && string[i]>'z')
//			&& (string[i] < '0' && string[i]>'9') && string[i] != '!' && string[i] != '@' && string[i] != '#'
//			&& string[i] != '%' && string[i] != '^' && string[i] != '&' && string[i] != '*')
//		{
//			return false;
//		}
//	}
//	return true;
//}

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
		UserInfo user;
		int i = 0;
		while (current[i] != ':')
		{
			user.userName.push_back(current[i]);
			++i;
		}
		++i; //going after first :
		while (current[i] != ':')
		{
			user.password.push_back(current[i]);
			++i;
		}
		++i; //going after second :

		string curBalance;
		while (i < current.size()) {//check if '\0' is better
			curBalance.push_back(current[i]);
			++i;
		}

		user.balance = stod(curBalance);
		users.push_back(user);
	}
}

bool validateUsername(string name)
{
	int index = 0;
	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] >= '0' || name[i] <= '9') {
			return false;
		}
		else
		{
			return true;
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
	if (smallLetter > 0 && bigLetter > 0 && symbol > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool existsByUsername(string username) {
	for (UserInfo& user : users) {
		if (user.userName == username) {
			return true;
		}
	}

	return false;
}

string intToString(int n)
{
	string str = to_string(n);
	return str;
}

unsigned hashPassword(string password)
{
	hash<string> hasher;
	string hashed_pass = password;
	size_t hash = hasher(hashed_pass);
	return hash;
}

void login(string username, string password) {
	unsigned hashedPassword = hashPassword(password);
	string hash_pass = intToString(hashedPassword);
	for (UserInfo& user : users) {
		if (user.userName == username && user.password == hash_pass) {
			isLogged = true;
			loggedUser = user;
		}
	}
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
		return "User with the same email already exists.";
	}

	unsigned hashedPassword = hashPassword(password);
	string hash_pass = intToString(hashedPassword);

	UserInfo user = { username, hash_pass, 0 };
	users.push_back(user);

	isLogged = true;
	loggedUser = user;
	
	return "REGISTERED_SUCCESSFULLY_MESSAGE";
}

void logout() {
	loggedUser = { "", "", 0 };
	isLogged = false;
}

void deposit(double amount)
{
	int index = 0;
	double newAmount = floor(amount * 100) / 100;// za da zakruglim 1.234-->1.23
	if (amount < 0)
	{
		cout << "INVALID AMOUNT OF MONEY!" << endl;
	}
	else
	{
		loggedUser.balance += newAmount;
	}
}

void withdraw(double amount)
{
	if (amount < 0 || amount > 10000)
	{
		cout << "INVALID AMOUNT!" << endl;
	}
	double newAmount = floor(amount * 100) / 100;

	if (amount > 0 && amount <= loggedUser.balance)
	{
		loggedUser.balance -= newAmount;
	}
}

void transfer(string username, double amount)
{
	if (amount < 0 || amount > 10000 || (loggedUser.balance < amount))
	{
		cout << "INVALID AMOUNT" << endl;
	}
	int newAmount = floor(amount * 100 + 0.5) / 100;

}
#endif // ! ENCODINGPASSWORD_USER_SERVICE_H
