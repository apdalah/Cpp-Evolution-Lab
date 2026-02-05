#pragma once
#include <string>

class User {
private:
    int id;
    std::string username;
    std::string password;
    std::string email;
    std::string createdDate;

public:
    // Constructors
    User(); // Default constructor
    User(int id, const std::string& username, const std::string& password,
        const std::string& email);

    // Getters
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getEmail() const;
    std::string getCreatedDate() const;

    // Setters
    void setId(int id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);

    // Validation
    bool isValid() const;

    // Serialization
    std::string toFileString() const;
    static User fromFileString(const std::string& line);
};