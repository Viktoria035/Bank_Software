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
*<file with constant-commands declarations>
*
*/
#pragma once
#include <string>

using namespace std;

const int MIN = -10000;
const double EPSILON = 0.00000000000000001;


const string EQUAL_SYMBOL = "====================================================";
const string STAR_SYMBOLS = "*****************************************************";
const string GUEST_MENU_OPENNING = "====================GUEST MENU====================";
const string LOGGED_MENU_OPENNING = "*********************LOGGED MENU*********************";
const string GUEST_MENU_COMMANDS = "Enter one of the following options in the menu: ";

const string QUIT_COMMAND = "Q";

const string LOGIN_COMMAND = "L";
const string ADD_USERNAME_TO_LOGIN = "Please enter your username: ";
const string ADD_PASSWORD_TO_LOGIN = "Please enter your password: ";
const string ERROR_TO_LOGIN = "Invalid username or password.";

const string REGISTER_COMMAND = "R";
const string CREATE_USERNAME = "Please enter your username (only using latin letters and symbols): ";
const string CREATE_PASSWORD = "Your password will be correct if: ";
const string RULE_ONE = " 1. Only latin letters are used.";
const string RULE_TWO = " 2. Only these symbols are used - \"!@#$%^&*\"";
const string RULE_THREE = " 3. Numbers are allowed.";
const string RULE_FOUR = " 4. The password must be at least 5 symbols(one uppercase,lowercase letter and symbol is required).";
const string ENTER_PASS = "Please enter your password: ";


const string CANCEL_COMMAND = "C";
const string USERNAME_TO_CANCEL = "Please enter your password to cancel your account: ";
const string ERROR_TO_CANCEL = "Please check your account balance if it is 0,otherwise please check your password.";
const string SUCCESS_MESSAGE_CANCEL = "Your account is successfully canceled, have a nice day!";


const string DEPOSIT_COMMAND = "D";
const string DEPOSIT_AMOUNT = "Please enter how much money you want to deposit: ";
const string INVALID_VALUE = "Please enter a valid number.";
const string TOO_MUCH_AMOUNT_OF_MONEY = "Invalid amount of money, it must be between 0-10000 BGN.";

const string LOGOUT_COMMAND = "L";
const string SUCCES_LOGOUT_MESSAGE = "You have just logout successfully, have a nice day!";

const string TRANSFER_COMMAND = "T";
const string TRANSFER_AMOUNT = "Please enter how much money you want to transfer: ";
const string SEARCHING_USERNAME = "Please enter the username of the account to which you want to transfer money: ";
const string ERROR_BEGINNING = "Unfortunately, there is a problem:";
const string POSSIBLE_ERROR_ONE = " 1. The amount of money you want to transfer is not between 0 - 10000 BGN";
const string POSSIBLE_ERROR_TWO = " 2. Account with this username does not exist.";

const string WITHDRAW_COMMAND = "W";
const string WITHDRAW_AMOUNT = "Please enter how much money you want to withdraw: ";

const string SUCCESS_TRANSFER = "Transfer has been success.";
const string INVALID_USERNAME = "Invalid username.";
const string INVALID_PASSWORD = "Invalid password.";
const string EXISTING_USERNAME_ALREADY = "User with this name already exists.";
const string NOT_EXISTING_COMMAND = "Not existing command!";
const string REGISTERED_SUCCESSFULLY_MESSAGE = "Congratulations, you have just registered successfully";
