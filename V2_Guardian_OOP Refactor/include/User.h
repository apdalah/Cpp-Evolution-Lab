#pragma once
#include <string>

class User
{
private:
	int id;
	std::string username;
	std::string password;
	std::string email;
	std::string createdDate;

public:
	// Getters
	int getId() const;
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getEmail() const;

	// Setters
	void setId(int id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setEmail(const std::string& email);

	//Display user info
	void displayInfo() const;
	void displaySummary() const;

	//Serialization and Deserialization
	std::string toFileString() const;
	std::string fromFileString(const std::string& line);

};