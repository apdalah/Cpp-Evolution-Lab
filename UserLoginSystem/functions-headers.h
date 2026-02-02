#pragma once

#include <string>

/*
* ==================== User Struct ====================
*/
struct User
{
	int id = 0;
	std::string username;
	std::string password;
	std::string email;
};

/*
* ==================== Screen Functions ====================
*/
void ClearBuff();
void ClearScreen();
void PauseScreen();
void RefreshScreen();
void ShowHeader();
void InitialScreen();
void UserScreen(User& user);

/*
* ==================== Input & Choice ====================
*/
int InitialChoice();
int UserChoice();
void LoginOrRegister(User& user, int initialChoice);

/*
* ==================== Validations ====================
*/
bool IsValidEmail(const std::string& email);
bool IsValidUsername(const std::string& username);
bool IsValidPassword(const std::string& password);
std::string GetValidEmail();
std::string GetValidUsername();
std::string GetValidPassword();

/*
* ==================== Login & Register ====================
*/
void Login(User& user);
void Register(User& user);

/*
* ==================== CRUD ====================
*/
void DisplayUser(const User& user);
bool CreateUser(User& user);
bool UserExists(const User& user);
int GetLastId();
void UpdateUser(User& updatedUser);
void RewriteUser(const User& updatedUser, const std::string& oldEmail);
void DeleteUser(const User& deletedUser);