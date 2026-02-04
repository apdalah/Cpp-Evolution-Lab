# 🔐 v1: Foundations (UserLoginSystem)

[![Version](https://img.shields.io/badge/Version-1.0-blue.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)
[![Status](https://img.shields.io/badge/Status-Complete-success.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)
[![Paradigm](https://img.shields.io/badge/Paradigm-Procedural-orange.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)

> **The Foundation**: A procedural approach to user authentication and data management

---

## 📌 Version Overview

**Foundations** is the first iteration in the C++ Evolution Lab series, implementing a complete user authentication system using procedural programming principles. This version establishes the core functionality that will be refined and expanded in subsequent versions.

### 🎯 Primary Goals

- ✅ Implement user registration and login
- ✅ Validate user input effectively
- ✅ Persist data using file-based storage
- ✅ Create modular, reusable functions
- ✅ Handle errors gracefully

---

## 🏗️ Architecture

### System Design

```
┌─────────────────────────────────────────────────┐
│                                                 │
│              User Interface (Console)           │
│                                                 │
└────────────────┬────────────────────────────────┘
                 │
         ┌───────▼────────┐
         │  Main Menu     │
         │  Controller    │
         └───┬────────┬───┘
             │        │
     ┌───────▼──┐  ┌──▼────────┐
     │ Register │  │  Login    │
     │ Function │  │  Function │
     └────┬─────┘  └─────┬─────┘
          │              │
          └──────┬───────┘
                 │
        ┌────────▼─────────┐
        │  Validation      │
        │  Functions       │
        └────────┬─────────┘
                 │
        ┌────────▼─────────┐
        │  File I/O        │
        │  (users.txt)     │
        └──────────────────┘
```

### Procedural Approach

This version uses a **function-based architecture** where each task is broken down into discrete, reusable functions:

- **Separation of Concerns**: Each function handles one specific task
- **Top-Down Design**: Main function orchestrates high-level flow
- **Sequential Execution**: Clear, linear program flow
- **Global Data**: Shared data structures accessible across functions

---

## 📁 File Structure

```
UserLoginSystem/
│
├── UserLoginSystem.cpp      # Main program file
├── functions.h              # Function declarations
├── validation.cpp           # Input validation logic
├── fileHandler.cpp          # File I/O operations
├── users.txt                # Data storage (created at runtime)
└── README.md                # This file
```

### File Descriptions

| File | Purpose | Lines |
|------|---------|-------|
| **UserLoginSystem.cpp** | Main program logic, menu system, and core functions | ~200 |
| **functions.h** | Function prototypes and constants | ~30 |
| **validation.cpp** | Input validation and sanitization | ~80 |
| **fileHandler.cpp** | File reading/writing operations | ~100 |
| **users.txt** | Plain text storage for user credentials | Runtime |

---

## ✨ Features

### 1. User Registration ✍️

```cpp
// Functional Flow:
1. Prompt for username
2. Validate username (alphanumeric, length)
3. Check for duplicates in users.txt
4. Prompt for password
5. Validate password (length, complexity)
6. Confirm password match
7. Append user to users.txt
8. Display success message
```

**Validation Rules**:
- Username: 4-20 characters, alphanumeric only
- Password: 6-30 characters, must contain letters and numbers
- No duplicate usernames allowed

### 2. User Login 🔑

```cpp
// Functional Flow:
1. Prompt for username
2. Prompt for password
3. Read users.txt line by line
4. Compare credentials
5. Grant/deny access
6. Display appropriate message
```

**Security Features**:
- Password masking during input
- Case-sensitive username matching
- Limited login attempts (3 tries)
- Clear error messages

### 3. File-Based Persistence 💾

**Data Format** (`users.txt`):
```
username1:password1
username2:password2
username3:password3
```

**Operations**:
- ✅ Append new users
- ✅ Read all users for authentication
- ✅ Check for duplicate usernames
- ✅ Handle file creation on first run

### 4. Input Validation ✔️

Comprehensive validation prevents crashes and security issues:

| Check | Purpose |
|-------|---------|
| Empty Input | Prevents null entries |
| Length Limits | Prevents buffer issues |
| Character Type | Ensures alphanumeric data |
| Whitespace | Trims leading/trailing spaces |
| Special Characters | Blocks SQL injection patterns |

---

## 🎮 User Interface

### Main Menu

```
╔════════════════════════════════════════╗
║                                        ║
║     USER AUTHENTICATION SYSTEM         ║
║                 v1.0                   ║
║                                        ║
╠════════════════════════════════════════╣
║                                        ║
║     1. Register New Account            ║
║     2. Login to Account                ║
║     3. Exit Program                    ║
║                                        ║
╚════════════════════════════════════════╝

Enter your choice (1-3): _
```

### Registration Flow

```
╔════════════════════════════════════════╗
║          ACCOUNT REGISTRATION          ║
╚════════════════════════════════════════╝

Enter username (4-20 characters): johnsmith
✓ Username available

Enter password (6-30 characters): ********
Enter password again: ********
✓ Passwords match

✓ Registration successful!
Welcome, johnsmith!

Press any key to continue...
```

### Login Flow

```
╔════════════════════════════════════════╗
║             ACCOUNT LOGIN              ║
╚════════════════════════════════════════╝

Username: johnsmith
Password: ********

✓ Login successful!
Welcome back, johnsmith!

Press any key to continue...
```

---

## 🔧 Technical Implementation

### Core Functions

#### 1. Main Controller

```cpp
int main() {
    int choice;
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: exitProgram(); return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
```

#### 2. Registration Function

```cpp
void registerUser() {
    string username, password, confirmPassword;
    
    // Get and validate username
    username = getValidUsername();
    if (usernameExists(username)) {
        cout << "Username already taken!\n";
        return;
    }
    
    // Get and validate password
    password = getValidPassword();
    confirmPassword = getValidPassword();
    
    if (password != confirmPassword) {
        cout << "Passwords don't match!\n";
        return;
    }
    
    // Save to file
    saveUser(username, password);
    cout << "Registration successful!\n";
}
```

#### 3. Login Function

```cpp
void loginUser() {
    string username, password;
    
    username = getInput("Username: ");
    password = getPasswordInput("Password: ");
    
    if (authenticateUser(username, password)) {
        cout << "Login successful!\n";
        displayUserDashboard(username);
    } else {
        cout << "Invalid credentials!\n";
    }
}
```

#### 4. Validation Functions

```cpp
bool isValidUsername(const string& username) {
    if (username.length() < 4 || username.length() > 20)
        return false;
    
    for (char c : username) {
        if (!isalnum(c)) return false;
    }
    
    return true;
}

bool isValidPassword(const string& password) {
    if (password.length() < 6 || password.length() > 30)
        return false;
    
    bool hasLetter = false, hasDigit = false;
    
    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        if (isdigit(c)) hasDigit = true;
    }
    
    return hasLetter && hasDigit;
}
```

#### 5. File Operations

```cpp
void saveUser(const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    
    if (file.is_open()) {
        file << username << ":" << password << "\n";
        file.close();
    } else {
        cout << "Error: Cannot access file!\n";
    }
}

bool authenticateUser(const string& username, const string& password) {
    ifstream file("users.txt");
    string line;
    
    while (getline(file, line)) {
        size_t pos = line.find(':');
        string storedUser = line.substr(0, pos);
        string storedPass = line.substr(pos + 1);
        
        if (storedUser == username && storedPass == password) {
            file.close();
            return true;
        }
    }
    
    file.close();
    return false;
}
```

---

## 🚀 Getting Started

### Prerequisites

```
- Windows 10/11
- Visual Studio 2022
- C++17 compiler
```

### Build & Run

1. **Open Project**:
   ```
   Open Cpp-Evolution-Lab.sln in Visual Studio
   ```

2. **Set Startup Project**:
   ```
   Right-click "UserLoginSystem" → Set as Startup Project
   ```

3. **Build**:
   ```
   Press Ctrl+Shift+B or Build → Build Solution
   ```

4. **Run**:
   ```
   Press F5 or Debug → Start Debugging
   ```

### First Time Setup

The program will automatically:
- Create `users.txt` if it doesn't exist
- Set up necessary file permissions
- Initialize the system

---

## 📊 Testing Scenarios

### Test Case 1: Successful Registration

```
Input:
  Username: testuser123
  Password: secure456
  Confirm: secure456

Expected Output:
  ✓ Registration successful!
  Welcome, testuser123!
```

### Test Case 2: Invalid Username

```
Input:
  Username: ab  (too short)

Expected Output:
  ✗ Username must be 4-20 characters!
```

### Test Case 3: Duplicate Username

```
Input:
  Username: testuser123  (already exists)

Expected Output:
  ✗ Username already taken!
```

### Test Case 4: Password Mismatch

```
Input:
  Password: secure456
  Confirm: secure457

Expected Output:
  ✗ Passwords don't match!
```

### Test Case 5: Successful Login

```
Input:
  Username: testuser123
  Password: secure456

Expected Output:
  ✓ Login successful!
  Welcome back, testuser123!
```

---

## 🎓 Learning Outcomes

This version demonstrates mastery of:

### C++ Fundamentals
- ✅ Variables, data types, and operators
- ✅ Control structures (if, switch, loops)
- ✅ Functions and parameter passing
- ✅ String manipulation

### File I/O
- ✅ Reading from files (`ifstream`)
- ✅ Writing to files (`ofstream`)
- ✅ File modes (append, truncate)
- ✅ Error handling for file operations

### Programming Practices
- ✅ Code organization and modularity
- ✅ Input validation and sanitization
- ✅ Error handling and user feedback
- ✅ Comments and documentation

---

## 🔄 Evolution Path

### Current Limitations (Addressed in v2)

| Issue | v1 Status | v2 Solution |
|-------|-----------|-------------|
| No password encryption | ❌ Plain text | ✅ SHA-256 hashing |
| Global variables | ❌ Used throughout | ✅ Encapsulated in classes |
| No class structure | ❌ Procedural only | ✅ User, Auth classes |
| Limited error handling | ⚠️ Basic try-catch | ✅ Custom exceptions |
| No code reusability | ⚠️ Function-based | ✅ Inheritance & polymorphism |

### Next Steps → v2: Guardian

The next version will transform this procedural code into an object-oriented architecture:

```cpp
// v1: Procedural
void registerUser() { ... }
void loginUser() { ... }

// v2: Object-Oriented
class User {
    private:
        string username;
        string passwordHash;
    public:
        User(string uname, string pass);
        bool authenticate(string pass);
};

class AuthenticationManager {
    private:
        vector<User> users;
    public:
        void registerUser(User user);
        bool loginUser(string uname, string pass);
};
```

---

## 📈 Metrics

```
Total Functions: 12
Lines of Code: ~410
Code Files: 4
Storage Method: Plain Text File
Security Level: Basic
Complexity: Low
Maintainability: Medium
```

---

## 🐛 Known Issues

1. **Password Security**: Stored in plain text (fixed in v2)
2. **Concurrency**: No multi-user support (fixed in v5)
3. **Data Integrity**: No backup mechanism (fixed in v5)
4. **Scalability**: Linear search O(n) (fixed in v5 with indexing)

---

## 🤝 Contributing

This version is **complete and stable**. All new features will be implemented in subsequent versions.

For bug reports or suggestions:
1. Open an issue with the `v1-foundations` label
2. Provide detailed reproduction steps
3. Include system information

---

## 📜 Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0.0 | 2024-02 | Initial release |
| 1.0.1 | 2024-02 | Added input validation |
| 1.0.2 | 2024-02 | Improved error messages |

---

## 🔗 Related Versions

- **Current**: v1: Foundations (UserLoginSystem)
- **Next**: [v2: Guardian](/v2-guardian) - OOP Refactor
- **Future**: [v3: Chronicle](/v3-chronicle) - Blog System

---

<div align="center">

### ⭐ This is where the journey begins!

**Next Stop**: Object-Oriented Programming in v2: Guardian

[← Back to Main Project](../README.md) | [View v2 Plans →](/v2-guardian)

</div>
