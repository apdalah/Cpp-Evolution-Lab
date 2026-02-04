#pragma once

#include <string>

/*
* ==================== User Structure ====================
*/

struct User
{
	int id;
	std::string email;
	std::string username;
	std::string password;
	std::string createdAt;    // NEW: Account creation timestamp
	std::string lastLogin;    // NEW: Last login timestamp
};

/*
* ==================== Screen Utilities ====================
*/

void ClearBuff();
void ClearScreen();
void PauseScreen();
void RefreshScreen();
void ShowHeader();
void InitialScreen();
void UserScreen(User& user);
void ShowSuccessMessage(const std::string& message);      // NEW
void ShowErrorMessage(const std::string& message);        // NEW

/*
* ==================== Input & Choice ====================
*/

int InitialChoice();
int UserChoice();
void LoginOrRegister(User& user, int initialChoice);
bool ConfirmAction(const std::string& action);            // NEW

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
* ==================== CRUD Operations ====================
*/

void DisplayUser(const User& user);
bool CreateUser(User& user);
bool UserExists(const User& user);
bool EmailExists(const std::string& email);               // NEW
bool UsernameExists(const std::string& username);         // NEW
int GetLastId();
void UpdateUser(User& updatedUser);
void ChangePassword(User& user);                          // NEW
void RewriteUser(const User& updatedUser, const std::string& oldEmail);
void DeleteUser(const User& deletedUser);

/*
* ==================== Utility Functions ====================
*/

std::string GetCurrentDateTime();                         // NEW
void UpdateLastLogin(User& user);                         // NEW
