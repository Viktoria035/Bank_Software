#include "user-information.h"

UserInfo::UserInfo() {
	//default values struct
	this->balance = 0;
	this->password = 0;
	this->username = "\0";
}

UserInfo::UserInfo(std::string username, int password, double balance) { // initialinzing User Information
	this->balance = balance;
	this->password = password;
	this->username = username;
}