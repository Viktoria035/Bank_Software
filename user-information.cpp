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
*<file with user-information default values and initialization>
*
*/
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
