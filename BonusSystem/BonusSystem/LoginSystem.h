#pragma once
#include "User.h"
#include "BonusSystem.h"
#include <map>
#include <memory>

class LoginSystem {
private:
	std::map<std::string, std::shared_ptr<User>> _users;
public:
	static const int PASSWORD_MIN_NUMBERS = 5;

	void addUser(std::string, std::string, User::Role);
	void deleteUser(std::string);
	void editUserLogin(std::string, std::string);
	void editUserPassword(std::string, std::string);

	void setEmployeeToUser(std::shared_ptr<BonusSystem>, std::string, int);
	void deleteEmployeeOnUsers(int);

	std::shared_ptr<User> getUserByLogin(std::string);

	std::vector<User> getUsers();

	static std::shared_ptr<LoginSystem> getInstance();

	std::shared_ptr<User> LogIn(std::string, std::string);
};