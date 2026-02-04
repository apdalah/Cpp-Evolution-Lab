#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "header_functions.h"  // Your original header name

/*
* ==================== Screen Utilities ====================
*/

void ClearBuff()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ClearScreen()
{
	// Cross-platform clear screen
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[H";
	std::cout.flush();
#endif
}

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
	std::cout << "|       Blog System v1.0              |" << std::endl;
	std::cout << "=======================================" << std::endl;
}

void InitialScreen()
{
	RefreshScreen();
	std::cout << "|                                     |" << std::endl;
	std::cout << "|  1. Login                           |" << std::endl;
	std::cout << "|  2. Register                        |" << std::endl;
	std::cout << "|  3. Exit                            |" << std::endl;
	std::cout << "|                                     |" << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "\nEnter your choice: ";
}

void UserScreen(User& user)
{
	while (true)
	{
		RefreshScreen();
		std::cout << "|  Welcome, " << user.username << std::endl;
		std::cout << "|                                     |" << std::endl;
		std::cout << "|  1. Display Your Information        |" << std::endl;
		std::cout << "|  2. Edit Your Data                  |" << std::endl;
		std::cout << "|  3. Change Password                 |" << std::endl;
		std::cout << "|  4. Delete Your Account             |" << std::endl;
		std::cout << "|  5. Logout                          |" << std::endl;
		std::cout << "|                                     |" << std::endl;
		std::cout << "=======================================" << std::endl;
		std::cout << "\nEnter your choice: ";

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
			ChangePassword(user);
			PauseScreen();
			break;
		case 4:
			if (ConfirmAction("delete your account"))
			{
				DeleteUser(user);
				PauseScreen();
				return;
			}
			break;
		case 5:
			ShowSuccessMessage("Logged out successfully!");
			PauseScreen();
			return;
		default:
			ShowErrorMessage("Invalid choice. Please try again...");
			PauseScreen();
			break;
		}
	}
}

void ShowSuccessMessage(const std::string& message)
{
	std::cout << "\n[SUCCESS] " << message << std::endl;
}

void ShowErrorMessage(const std::string& message)
{
	std::cout << "\n[ERROR] " << message << std::endl;
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
			ShowErrorMessage("Invalid input. Please enter a number.");
			std::cin.clear();
			ClearBuff();
			std::cout << "Enter your choice: ";
			continue;
		}

		ClearBuff();

		if (choice >= 1 && choice <= 3)
			return choice;

		ShowErrorMessage("Please enter 1 for Login, 2 for Register, or 3 to Exit.");
		std::cout << "Enter your choice: ";
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
	switch (initialChoice)
	{
	case 1:
		Login(user);
		break;
	case 2:
		Register(user);
		break;
	case 3:
		std::cout << "\nThank you for using Blog System. Goodbye!" << std::endl;
		exit(0);
	}
}

bool ConfirmAction(const std::string& action)
{
	std::cout << "\n[WARNING] Are you sure you want to " << action << "? (y/n): ";
	char confirm;
	std::cin >> confirm;
	ClearBuff();
	return (confirm == 'y' || confirm == 'Y');
}

/*
* ==================== Validations ====================
*/

bool IsValidEmail(const std::string& email)
{
	if (email.empty() || email.length() > 100)
		return false;

	size_t atPos = email.find('@');
	if (atPos == std::string::npos || atPos == 0)
		return false;

	size_t dotPos = email.find('.', atPos);
	if (dotPos == std::string::npos || dotPos == atPos + 1 || dotPos == email.length() - 1)
		return false;

	if (email.find(' ') != std::string::npos)
		return false;

	// Check for valid characters before @
	for (size_t i = 0; i < atPos; ++i)
	{
		if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_' && email[i] != '-')
			return false;
	}

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
	if (password.length() < 8 || password.length() > 50)
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

		// Trim whitespace
		email.erase(0, email.find_first_not_of(" \t"));
		email.erase(email.find_last_not_of(" \t") + 1);

		if (IsValidEmail(email))
			return email;

		ShowErrorMessage("Invalid Email format.");
		std::cout << "Requirements: valid@email.com format, max 100 characters" << std::endl;
		std::cout << "Try again: ";
	}
}

std::string GetValidUsername()
{
	std::string username;
	while (true)
	{
		std::getline(std::cin, username);

		// Trim whitespace
		username.erase(0, username.find_first_not_of(" \t"));
		username.erase(username.find_last_not_of(" \t") + 1);

		if (IsValidUsername(username))
			return username;

		ShowErrorMessage("Invalid Username.");
		std::cout << "Requirements: 3-20 chars, starts with letter, alphanumeric + underscore" << std::endl;
		std::cout << "Try again: ";
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

		ShowErrorMessage("Password too weak.");
		std::cout << "Requirements: 8+ chars, uppercase, lowercase, digit, special char, no spaces" << std::endl;
		std::cout << "Try again: ";
	}
}

/*
* ==================== Login ====================
*/

void Login(User& user)
{
	ClearScreen();
	std::cout << "=======================================" << std::endl;
	std::cout << "|              LOGIN                  |" << std::endl;
	std::cout << "=======================================" << std::endl;

	std::cout << "\nEnter Username: ";
	user.username = GetValidUsername();

	std::cout << "Enter Password: ";
	std::getline(std::cin, user.password);

	std::ifstream file("users.txt");

	if (!file)
	{
		ShowErrorMessage("No users found. Please register first.");
		PauseScreen();
		return;
	}

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, email, username, password, createdAt, lastLogin;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		std::getline(ss, createdAt, ',');
		std::getline(ss, lastLogin, ',');

		if (user.username == username && user.password == password)
		{
			user.id = std::stoi(id);
			user.email = email;
			user.createdAt = createdAt;
			user.lastLogin = lastLogin;

			file.close();

			// Update last login
			UpdateLastLogin(user);

			ShowSuccessMessage("Login successful!");
			PauseScreen();
			UserScreen(user);
			return;
		}
	}

	file.close();
	ShowErrorMessage("Invalid username or password.");
	PauseScreen();
}

/*
* ==================== Register ====================
*/

void Register(User& user)
{
	ClearScreen();
	std::cout << "=======================================" << std::endl;
	std::cout << "|          REGISTRATION               |" << std::endl;
	std::cout << "=======================================" << std::endl;

	std::cout << "\nEnter Email: ";
	user.email = GetValidEmail();

	// Check if email already exists
	if (EmailExists(user.email))
	{
		ShowErrorMessage("Email already registered. Please use a different email or login.");
		PauseScreen();
		return;
	}

	std::cout << "Enter Username: ";
	user.username = GetValidUsername();

	// Check if username already exists
	if (UsernameExists(user.username))
	{
		ShowErrorMessage("Username already taken. Please choose a different username.");
		PauseScreen();
		return;
	}

	std::cout << "Enter Password: ";
	user.password = GetValidPassword();

	std::cout << "Confirm Password: ";
	std::string confirmPassword;
	std::getline(std::cin, confirmPassword);

	if (user.password != confirmPassword)
	{
		ShowErrorMessage("Passwords do not match!");
		PauseScreen();
		return;
	}

	if (CreateUser(user))
	{
		ShowSuccessMessage("Registration successful! Welcome to Blog System!");
		PauseScreen();
		UserScreen(user);
	}
	else
	{
		ShowErrorMessage("Registration failed. Please try again.");
		PauseScreen();
	}
}

/*
* ==================== CRUD ====================
*/

void DisplayUser(const User& user)
{
	ClearScreen();
	std::cout << "=======================================" << std::endl;
	std::cout << "|       YOUR INFORMATION              |" << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "\n  ID:              " << user.id << std::endl;
	std::cout << "  Email:           " << user.email << std::endl;
	std::cout << "  Username:        " << user.username << std::endl;
	std::cout << "  Password:        " << std::string(user.password.length(), '*') << " (hidden)" << std::endl;
	std::cout << "  Account Created: " << user.createdAt << std::endl;
	std::cout << "  Last Login:      " << user.lastLogin << std::endl;
	std::cout << "\n=======================================" << std::endl;
}

bool CreateUser(User& user)
{
	std::ofstream file("users.txt", std::ios::app);

	if (!file)
	{
		std::cerr << "Error: Can't open file for writing." << std::endl;
		return false;
	}

	user.id = GetLastId() + 1;
	user.createdAt = GetCurrentDateTime();
	user.lastLogin = user.createdAt;

	file << user.id << ","
		<< user.email << ","
		<< user.username << ","
		<< user.password << ","
		<< user.createdAt << ","
		<< user.lastLogin << '\n';

	file.close();
	return true;
}

bool UserExists(const User& user)
{
	return EmailExists(user.email);
}

bool EmailExists(const std::string& email)
{
	std::ifstream file("users.txt");

	if (!file)
		return false;

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, fileEmail;

		std::getline(ss, id, ',');
		std::getline(ss, fileEmail, ',');

		if (email == fileEmail)
		{
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

bool UsernameExists(const std::string& username)
{
	std::ifstream file("users.txt");

	if (!file)
		return false;

	std::string line;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string id, email, fileUsername;

		std::getline(ss, id, ',');
		std::getline(ss, email, ',');
		std::getline(ss, fileUsername, ',');

		if (username == fileUsername)
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

std::string GetCurrentDateTime()
{
	time_t now = time(0);
	tm ltm;

	// Use safe version for Windows
#ifdef _WIN32
	localtime_s(&ltm, &now);
#else
	localtime_r(&now, &ltm);
#endif

	std::ostringstream oss;
	oss << std::setfill('0')
		<< std::setw(4) << 1900 + ltm.tm_year << "-"
		<< std::setw(2) << 1 + ltm.tm_mon << "-"
		<< std::setw(2) << ltm.tm_mday << " "
		<< std::setw(2) << ltm.tm_hour << ":"
		<< std::setw(2) << ltm.tm_min << ":"
		<< std::setw(2) << ltm.tm_sec;

	return oss.str();
}

void UpdateLastLogin(User& user)
{
	user.lastLogin = GetCurrentDateTime();
	RewriteUser(user, user.email);
}

void UpdateUser(User& updatedUser)
{
	ClearScreen();
	std::cout << "=======================================" << std::endl;
	std::cout << "|          EDIT DATA                  |" << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "\n  1. Email" << std::endl;
	std::cout << "  2. Username" << std::endl;
	std::cout << "  3. Cancel" << std::endl;
	std::cout << "\n=======================================" << std::endl;
	std::cout << "\nYour choice: ";

	int choice;
	std::cin >> choice;

	if (std::cin.fail())
	{
		std::cin.clear();
		ClearBuff();
		ShowErrorMessage("Invalid choice.");
		return;
	}

	ClearBuff();

	const std::string oldEmail = updatedUser.email;

	switch (choice)
	{
	case 1:
		std::cout << "\nEnter new Email: ";
		{
			std::string newEmail = GetValidEmail();
			if (EmailExists(newEmail) && newEmail != oldEmail)
			{
				ShowErrorMessage("Email already in use.");
				return;
			}
			updatedUser.email = newEmail;
		}
		break;
	case 2:
		std::cout << "\nEnter new Username: ";
		{
			std::string newUsername = GetValidUsername();
			if (UsernameExists(newUsername) && newUsername != updatedUser.username)
			{
				ShowErrorMessage("Username already taken.");
				return;
			}
			updatedUser.username = newUsername;
		}
		break;
	case 3:
		std::cout << "\nCancelled." << std::endl;
		return;
	default:
		ShowErrorMessage("Invalid choice.");
		return;
	}

	RewriteUser(updatedUser, oldEmail);
	ShowSuccessMessage("Information updated successfully!");
}

void ChangePassword(User& user)
{
	ClearScreen();
	std::cout << "=======================================" << std::endl;
	std::cout << "|       CHANGE PASSWORD               |" << std::endl;
	std::cout << "=======================================" << std::endl;

	std::cout << "\nEnter current password: ";
	std::string currentPassword;
	std::getline(std::cin, currentPassword);

	if (currentPassword != user.password)
	{
		ShowErrorMessage("Incorrect current password!");
		return;
	}

	std::cout << "Enter new password: ";
	std::string newPassword = GetValidPassword();

	std::cout << "Confirm new password: ";
	std::string confirmPassword;
	std::getline(std::cin, confirmPassword);

	if (newPassword != confirmPassword)
	{
		ShowErrorMessage("Passwords do not match!");
		return;
	}

	if (newPassword == currentPassword)
	{
		ShowErrorMessage("New password must be different from current password!");
		return;
	}

	user.password = newPassword;
	RewriteUser(user, user.email);
	ShowSuccessMessage("Password changed successfully!");
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
				<< updatedUser.password << ','
				<< updatedUser.createdAt << ','
				<< updatedUser.lastLogin << '\n';
		}
		else
		{
			out << line << '\n';
		}
	}

	in.close();
	out.close();

	remove("users.txt");
	rename("temp.txt", "users.txt");
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
		ShowSuccessMessage("Account deleted successfully.");
	else
		ShowErrorMessage("Failed to delete account. Please try again.");
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
		int choice = InitialChoice();

		if (choice == 3)
			break;

		LoginOrRegister(user, choice);
	}

	std::cout << "\nThank you for using Blog System v1.0!" << std::endl;
	std::cout << "Goodbye!" << std::endl;

	return 0;
}