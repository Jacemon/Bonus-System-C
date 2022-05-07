#pragma once
#include "User.h"
#include "BonusSystem.h"
#include <map>
#include <fstream>
#include <memory>

class LoginSystem {
private:
	static std::shared_ptr<LoginSystem> _loginSystem;

	std::map<std::string, std::shared_ptr<User>> _users;
	std::map<std::string, int> _userLogin_employeeID;
public:
	LoginSystem();
	LoginSystem(const LoginSystem&);

	static const int PASSWORD_MIN_NUMBERS = 5;

	void addUser(std::string, std::string, User::Role);
	void addUser(User);
	void deleteUser(std::string);
	void editUserLogin(std::string, std::string);
	void editUserPassword(std::string, std::string);

	void setEmployeeToUser(std::shared_ptr<BonusSystem>, std::string, int);
	void deleteEmployeeOnUsers(int);

	std::shared_ptr<User> getUserByLogin(std::string);

	std::map<std::string, User> getUsers();

	static std::shared_ptr<LoginSystem> getInstance();
	static std::shared_ptr<LoginSystem> resetToDefault();

	std::shared_ptr<User> LogIn(std::string, std::string);

	friend std::ofstream& operator<<(std::ofstream&, LoginSystem);
	friend std::ifstream& operator>>(std::ifstream&, LoginSystem&);
};