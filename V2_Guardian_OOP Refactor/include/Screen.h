#pragma once
#include <string>
#include <vector>

class Screen
{
public:
    // Display utilities
    static void clear();
    static void pause();
    static void printLine(char character = '=', int length = 50);
    static void printHeader(const std::string& title);
    static void printError(const std::string& message);
    static void printSuccess(const std::string& message);
    static void printWarning(const std::string& message);
    static void printInfo(const std::string& message);

    // Menu utilities
	static void displayMenu(const std::vector<std::string>& options, const std::string& title = "Menu");
	static int getMenuChoice(int minOption, int maxOption);

	//Input utilities
	static std::string getInput(const std::string& prompt); // Visible input
    static std::string getPasswordInput(const std::string& prompt); // Hide input
	static bool confirmAction(const std::string& prompt); //Yes/No confirmation

    // Table display
	static void displayTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows);

private:
	Screen() = delete; // Prevent instantiation - All static methods

};
