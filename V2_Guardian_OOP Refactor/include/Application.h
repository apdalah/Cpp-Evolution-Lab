#pragma once
#include "AuthManager.h"
#include "UserRepository.h"

class Application
{
private:
	AuthManager auth;
	UserRepository repo;
	bool running;

public:
	// Constructor
	Application();

	// Main entry point
	void run();

	// Dashboard menu (logged in)
	void showDashboard();
	void handleDashboard();

	// Menu handlers
	void handleRegister();
	void handleLogin();
	void handleLogout();
	void handleViewProfile();
	void handleChangePassword();
	void handleExit();

	// Helpers
	void displayWelcome();
	void displayGoodbye();
};