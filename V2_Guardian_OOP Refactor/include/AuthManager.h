#pragma once
#include <string>
#include "User.h"
#include "UserRepository.h"

class AuthManager {
private:
    UserRepository& repository;
    User* currentUser;

public:
    // Constructor / Destructor
    explicit AuthManager(UserRepository& repo);
    ~AuthManager();

    // Main operations (interactive - get input from user)
    bool registerUser();
    bool login();
    void logout();

    // Alternative: pass parameters (for testing or non-interactive use)
    bool registerUser(const std::string& username,
        const std::string& password,
        const std::string& email);
    bool login(const std::string& username, const std::string& password);

    // Session queries
    bool isLoggedIn() const { return currentUser != nullptr; }
    User* getCurrentUser() const { return currentUser; }
    std::string getCurrentUsername() const {
        return currentUser ? currentUser->getUsername() : "";
    }

    // Display current user info
    void displayCurrentUserInfo() const;

private:
    // Interactive input helpers (use Screen class)
    std::string promptUsername();
    std::string promptEmail();
    std::string promptPassword();

    // Validation (uses Validator class)
    bool validateRegistrationInput(const std::string& username,
        const std::string& password,
        const std::string& email);
};