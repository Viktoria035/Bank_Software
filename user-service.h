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
*<file with user-service functions declaration>
*
*/
#pragma once
#include <string>
#include <vector>

struct UserInfo;
int numbersAfterComa(string str);
double stringToDouble(string str);
bool checkAmount(string amount);
void loadUsers();
bool validateUsername(string name);
bool validatePassword(string password);
bool existsByUsername(string username);
int hashPassword(string password);
UserInfo* getUser(string username);
bool login(string username, string password, UserInfo* &user);
void logout(UserInfo* &user);
string create(string username, string password, UserInfo* &loggedUser);
bool checkPassword(string password, UserInfo* &loggedUser);
bool cancelAccount(string password, UserInfo* &loggedUser);
bool deposit(double amount, UserInfo* &loggedUser);
bool withdraw(double amount, UserInfo* &loggedUser);
bool transfer(string username, double amount, UserInfo* &loggedUser);
bool saveState();
void pause();
