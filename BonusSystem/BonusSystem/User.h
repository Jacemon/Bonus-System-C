#pragma once
#include <iostream>
#include "Employee.h"

class User {
private:
	enum class Role {
		admin,
		common,
	};
	Role _role;

	std::string _login;
	std::size_t _passwordHash;

	std::pair<int, std::shared_ptr<Employee<std::string>>> _employee;

	bool LogIn(std::string login, std::string password);

	friend class LoginSystem;
	friend class Menu;
public:
	User();
	User(const User& copy);
	User(std::string, std::string, Role role);
	bool operator< (const User& other) const;
	bool operator> (const User& other) const;

	friend std::ostream& operator<<(std::ostream& os, User user);
	friend std::ofstream& operator<<(std::ofstream& ofs, User user);
	friend std::ifstream& operator>>(std::ifstream& ifs, User& user);
};