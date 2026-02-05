#pragma once
#include <string>

class Validator
{
	public:

	// Username validations
	static bool isValidUsername(const std::string& username);
	static bool isUsernameLength(const std::string& username);
	static bool hasNoSpaces(const std::string& username);

	// Password validations
	static bool isValidPassword(const std::string& password);
	static bool isPasswordStrong(const std::string& password);

	// Email validations
	static bool isValidEmail(const std::string& email);
	static bool hasAtSympol(const std::string& email);


	// Helper methods
	static bool isEmpty(const std::string& str);
	static bool isLengthInRange(const std::string& str, int min, int max);
	static bool containsOnlyAlphanumeric(const std::string& str);


	// Display validation errors
	std::string getValidationErrors(const std::string& field, const std::string& value);


private:
	Validator() = delete; // Prevent instantiation - All static methods

};