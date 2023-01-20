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
*<file with user-information struct>
*
*/
#pragma once

#include <string>

//struct UserInfo --> type UserInfo
struct UserInfo {
	//properties
	std::string username;
	int password;
	double balance;

	UserInfo(std::string, int, double);

	UserInfo();

};
