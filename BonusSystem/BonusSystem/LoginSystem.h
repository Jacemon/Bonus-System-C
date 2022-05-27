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
	LoginSystem(const LoginSystem& copy);

	static const int PASSWORD_MIN_NUMBERS = 5;

	void addUser(std::string login, std::string password, User::Role role);
	void addUser(User user);
	void deleteUser(std::string login);
	void editUserLogin(std::string login, std::string newLogin);
	void editUserPassword(std::string login, std::string newPassword);

	void setEmployeeToUser(std::shared_ptr<BonusSystem> bs, std::string login, int employeeId);
	void deleteEmployeeOnUsers(int employeeId);

	std::shared_ptr<User> getUserByLogin(std::string login);

	std::map<std::string, User> getUsers();

	static std::shared_ptr<LoginSystem> getInstance();
	static std::shared_ptr<LoginSystem> resetToDefault();

	std::shared_ptr<User> LogIn(std::string login, std::string password);

	friend std::ofstream& operator<<(std::ofstream& ofs, LoginSystem ls);
	friend std::ifstream& operator>>(std::ifstream& ifs, LoginSystem& ls);
};