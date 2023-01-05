#pragma once

#ifdef ENCODINGPASSWORD_GLOBAL_CONSTANTS_H
#define ENCODINGPASSWORD_GLOBAL_CONSTANTS_H

#include <string>;

const string LOGIN = "L";//first enter a name, then enter a password
const string REGISTER = "R";//first enter a freestyle name,only with latins alphabet,
//then enter a password >= 5 symbols(!@#$%^&*,alphabet) at least 1 lower , 1 upper, 1 symbol; hashed type
const string QUIT = "Q";//quit the program and rewrite "users.txt" file with the changes
const string CANCEL_ACCOUNT = "C";//enter password;if it's correct and the balanse = 0 --> delete account and return to the local menu
const string DEPOSIT = "D";//deposit a sum > 0 with max 2 digit after '.' if there are more we are getting the 'celine'
const string LOGOUT = "L";//return to the local menu
const string TRANSFER = "T";//transfer money from 1 account to 2 account if 2 exist and 1 has enough money like the max overdraft is 10 000 BGN 
const string WITHDRAW = "W";//decrease current sum with the num from administrator like max overdraft is 10 000 BGN

const string SUCCESFULLY_REGISTERED_MESSAGE = "Successfully registered";

#endif // ENCODINGPASSWORD_GLOBAL_CONSTANTS_H

