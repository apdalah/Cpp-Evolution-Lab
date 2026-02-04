#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include "functions-headers.h"

/*
* ==================== Screen Utilities ====================
*/

void ClearBuff()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ClearScreen()
{
	std::cout << "\033[2J\033[H";
	std::cout.flush();
}

// Pauses execution until the user presses Enter.
void PauseScreen()
{
	std::cout << "\nPress Enter to continue..." << std::endl;
	std::cin.get();
}

void RefreshScreen()
{
	ClearScreen();
	ShowHeader();
}

void ShowHeader()
{
	std::cout << "=======================================" << std::endl;
	std::cout << "|          Blog System                 |" << std::endl;
	std::cout << "=======================================" << std::endl;
}

void InitialScreen()
{
	RefreshScreen();
	std::cout << "|                                     |" << std::endl;
	std::cout << "|  1- Login                           |" << std::endl;
	std::cout << "|  2- Register                        |" << std::endl;
	std::cout << "|                                     |" << std::endl;
	std::cout << "=======================================" << std::endl;
}

void UserScreen(User& user)
{
	while (true)
	{
		RefreshScreen();
		std::cout << "|     Welcome, " << user.username << std::endl;
		std::cout << "|                                     |" << std::endl;
		std::cout << "|  1- Display Your Information        |" << std::endl;
		std::cout << "|  2- Edit Your Data                  |" << std::endl;
		std::cout << "|  3- Delete Your Account             |" << std::endl;
		std::cout << "|  4- LogOut                          |" << std::endl;
		std::cout << "|                                     |" << std::endl;
		std::cout << "=======================================" << std::endl;

		switch (UserChoice())
		{
		case 1:
			DisplayUser(user);
			PauseScreen();
			break;
		case 2:
			UpdateUser(user);
			PauseScreen();
			break;
		case 3:
			DeleteUser(user);
			PauseScreen();
			return;
		case 4:
			return;
		default:
			std::cout << "Invalid choice. Please try again..." << std::endl;
			PauseScreen();
			break;
		}
	}
}

/*
* ==================== Input & Choice ====================
*/

int InitialChoice()
{
	while (true)
	{
		int choice;
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cout << "Invalid input. Please enter a number." << std::endl;
			std::cin.clear();
			ClearBuff();
			continue;
		}

		ClearBuff();

		if (choice == 1 || choice == 2)
			return choice;

		std::cout << "Please enter 1 for Login or 2 for Register." << std::endl;
	}
}

int UserChoice()
{
	int choice;
	std::cin >> choice;

	if (std::cin.fail())
	{
		std::cin.clear();
		ClearBuff();
		return 0;
	}

	ClearBuff();
	return choice;
}

void LoginOrRegister(User& user, int initialChoice)
{
	if (initialChoice == 1)
		Login(user);
	else
		Register(user);
}

/*
* ==================== Validations ====================
*/

bool IsValidEmail(const std::string& email)
{
	if (email.empty())
		return false;

	size_t atPos = email.find('@');
	if (atPos == std::string::npos || atPos == 0)
		return false;

	size_t dotPos = email.find('.', atPos);
	if (dotPos == std::string::npos || dotPos == atPos + 1 || dotPos == email.length() - 1)
		return false;

	if (email.find(' ') != std::string::npos)
		return false;

	return true;
}

bool IsValidUsername(const std::string& username)
{
	if (username.empty())
		return false;

	if (!isalpha(username[0]))
		return false;

	if (username.length() < 3 || username.length() > 20)
		return false;

	for (char c : username)
	{
		if (!isalnum(c) && c != '_')
			return false;
	}

	return true;
}

bool IsValidPassword(const std::string& password)
{
	if (password.length() < 8)
		return false;

	bool hasUpper = false;
	bool hasLower = false;
	bool hasDigit = false;
	bool hasSpecial = false;

	for (char c : password)
	{
		if (isupper(c))        hasUpper = true;
		else if (islower(c))   hasLower = true;
		else if (isdigit(c))   hasDigit = true;
		else if (!isspace(c))  hasSpecial = true;
		else return false; // spaces not allowed
	}

	return hasUpper && hasLower && hasDigit && hasSpecial;
}

std::string GetValidEmail()
{
	std::string email;
	while (true)
	{
		std::getline(std::cin, email);
		if (IsValidEmail(email))
			return email;
		std::cout << "Invalid Email. Try again: ";
	}
}

std::string GetValidUsername()
{
	std::string username;
	while (true)
	{
		std::getline(std::cin, username);
		if (IsValidUsername(username))
			return username;
		std::cout << "Invalid Username (3-20 chars, starts with a letter, no spaces). Try again: ";
	}
}

std::string GetValidPassword()
{
	std::string password;
	while (true)
	{
		std::getline(std::cin, password);
		if (IsValidPassword(password))
			return password;
		std::cout << "Invalid Password (8+ chars, upper, lower, digit, special, no spaces). Try again: ";
	}
}

/*
* ==================== Login ====================
*/

void Login(User& user)
{
	ClearScreen();
	std::cout << "========== LOGIN ===================" << std::endl;
	std::cout << "Enter Username: ";
	user.username = GetValidUsername();

	std::cout << "Enter Password: ";
	std::getline(std::cin, user.password);

	std::ifstream file("users.txt");

	if (!file)
	{
		std::cout << "No users found. Please register first." << std::endl;
		PauseScreen();
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, email, username, password;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');

		if (user.username == username && user.password == password)
		{
			user.id = std::stoi(id);
			user.email = email;
			file.close();
			UserScreen(user);
			return;
		}
	}

	file.close();
	std::cout << "Wrong credentials." << std::endl;
	PauseScreen();
}

/*
* ==================== Register ====================
*/

void Register(User& user)
{
	ClearScreen();
	std::cout << "========== REGISTER ================" << std::endl;

	std::cout << "Enter Email: ";
	user.email = GetValidEmail();

	std::cout << "Enter Username: ";
	user.username = GetValidUsername();

	std::cout << "Enter Password: ";
	user.password = GetValidPassword();

	if (CreateUser(user))
	{
		std::cout << "Registration successful! Logging you in..." << std::endl;
		PauseScreen();
		Login(user);
	}
	else
	{
		std::cout << "User already exists." << std::endl;
		PauseScreen();
	}
}

/*
* ==================== CRUD ====================
*/

void DisplayUser(const User& user)
{
	std::cout << "========== YOUR INFORMATION ========" << std::endl;
	std::cout << "  ID:       " << user.id << std::endl;
	std::cout << "  Email:    " << user.email << std::endl;
	std::cout << "  Username: " << user.username << std::endl;
	std::cout << "  Password: " << user.password << std::endl;
	std::cout << "=====================================" << std::endl;
}

bool CreateUser(User& user)
{
	std::ofstream file("users.txt", std::ios::app);

	if (!file)
	{
		std::cerr << "Error: Can't open file for writing." << std::endl;
		return false;
	}

	if (UserExists(user))
		return false;

	user.id = GetLastId() + 1;

	file << user.id << ","
		<< user.email << ","
		<< user.username << ","
		<< user.password << '\n';

	file.close();
	return true;
}

bool UserExists(const User& user)
{
	std::ifstream file("users.txt");

	if (!file)
		return false;  // file doesn't exist yet => user doesn't exist

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, email;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');

		if (user.email == email)
		{
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

int GetLastId()
{
	std::ifstream file("users.txt");

	if (!file)
		return 0;

	std::string line;
	std::string lastId = "0";

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::getline(ss, lastId, ',');
	}

	file.close();
	return std::stoi(lastId);
}

void UpdateUser(User& updatedUser)
{
	ClearScreen();
	std::cout << "========== EDIT DATA ===============" << std::endl;
	std::cout << "  1- Email" << std::endl;
	std::cout << "  2- Username" << std::endl;
	std::cout << "  3- Password" << std::endl;
	std::cout << "=====================================" << std::endl;
	std::cout << "Your choice: ";

	int choice;
	std::cin >> choice;

	if (std::cin.fail())
	{
		std::cin.clear();
		ClearBuff();
		std::cout << "Invalid choice." << std::endl;
		return;
	}

	ClearBuff();

	const std::string oldEmail = updatedUser.email;

	switch (choice)
	{
	case 1:
		std::cout << "Enter new Email: ";
		updatedUser.email = GetValidEmail();
		break;
	case 2:
		std::cout << "Enter new Username: ";
		updatedUser.username = GetValidUsername();
		break;
	case 3:
		std::cout << "Enter new Password: ";
		updatedUser.password = GetValidPassword();
		break;
	default:
		std::cout << "Invalid choice." << std::endl;
		return;
	}

	RewriteUser(updatedUser, oldEmail);
}

void RewriteUser(const User& updatedUser, const std::string& oldEmail)
{
	std::ifstream in("users.txt");
	std::ofstream out("temp.txt");

	if (!in || !out)
	{
		std::cerr << "Error: Can't open file." << std::endl;
		return;
	}

	std::string line;

	while (std::getline(in, line))
	{
		std::stringstream ss(line);
		std::string id, email;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');

		if (oldEmail == email)
		{
			out << updatedUser.id << ','
				<< updatedUser.email << ','
				<< updatedUser.username << ','
				<< updatedUser.password << '\n';
		}
		else
		{
			out << line << '\n';
		}
	}

	in.close();
	out.close();

	remove("users.txt");

	if (rename("temp.txt", "users.txt") == 0)
		std::cout << "Updated successfully." << std::endl;
	else
		std::cerr << "Error: Failed to save changes." << std::endl;
}

void DeleteUser(const User& deletedUser)
{
	std::ifstream in("users.txt");
	std::ofstream out("temp.txt");

	if (!in || !out)
	{
		std::cerr << "Error: Can't open file." << std::endl;
		return;
	}

	std::string line;

	while (std::getline(in, line))
	{
		std::stringstream ss(line);
		std::string id, email;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');

		if (deletedUser.email != email)
			out << line << '\n';
	}

	in.close();
	out.close();

	remove("users.txt");

	if (rename("temp.txt", "users.txt") == 0)
		std::cout << "Account deleted successfully." << std::endl;
	else
		std::cerr << "Error: Failed to save changes." << std::endl;
}

/*
* ==================== Main ====================
*/

int main()
{
	while (true)
	{
		User user;
		InitialScreen();
		LoginOrRegister(user, InitialChoice());
	}

	return 0;
}