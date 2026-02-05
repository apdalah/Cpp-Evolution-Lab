#pragma once
#include "User.h"
#include <string>
#include <vector>


class UserRepository
{
private:
	std::string filePath;
public:
	// Constructor
	explicit UserRpository(const std::string& filePath = "data/users.txt");

	// CRUD operations
	bool create(const User& user);
	User* read(std::string& username);
	std::vector<User> getAllUsers() const;
	bool update(const User& user);
	bool remove(const std::string& username);


	// Helper methods
	bool exists(const std::string& username) const;
	int count() const;

	// Authenticate helpers
	bool validCredentials(const std::string& username, const std::string& password);

private:
	// I/O helpers
	std::vector<User> loadFromFile() const;
	bool saveToFile(const std::vector<User>& users);

	// File utilities
	bool fileExists();
	bool fileReadable() const;

};