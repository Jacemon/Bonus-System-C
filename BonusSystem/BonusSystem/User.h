#pragma once
#include <iostream>
#include "Employee.h"

class User {
private:
	enum class Role {
		admin,
		common,
		// guest
	};
	Role _role;

	std::string _login;
	std::size_t _passwordHash;

	std::pair<int, std::shared_ptr<Employee>> _employee;

	bool LogIn(std::string, std::string);

	friend class LoginSystem;
	friend class Menu;
public:
	User();
	User(const User& copy);
	User(std::string, std::string, Role role);
	bool operator< (const User& other) const;
	bool operator> (const User& other) const;

	friend std::ostream& operator<<(std::ostream&, User);
	friend std::ofstream& operator<<(std::ofstream&, User);
	friend std::ifstream& operator>>(std::ifstream&, User&);
};