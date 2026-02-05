#pragma once
#include "User.h"
#include <string>
#include <vector>

class UserRepository {
private:
    std::string filePath;

public:
    // Constructor
    explicit UserRepository(const std::string& filePath = "data/users.txt");

    // CRUD operations
    bool create(const User& user);
    User* read(const std::string& username) const;
    std::vector<User> getAllUsers() const;
    bool update(const User& user);
    bool remove(const std::string& username);

    // Helper methods
    bool exists(const std::string& username) const;
    int count() const;
    int getNextId() const;

    // Authentication helper
    bool validateCredentials(const std::string& username,
        const std::string& password) const;

private:
    // I/O helpers
    std::vector<User> loadFromFile() const;
    bool saveToFile(const std::vector<User>& users) const;

    // File utilities
    bool fileExists() const;
    void createFileIfNotExists() const;
};