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
	bool showUsers(bool sort);
	bool showEmployees(bool sort);
	bool showTasks(bool sort, int taskType = 0);
	bool showEmployeeTasks(bool sort, std::shared_ptr<Employee> employee);
	bool showEmployeeWithCompletedTask(bool sort);

	bool searchUser(std::string);
	bool searchEmployee(std::string, bool);
	bool searchEmployee(int, bool);
	bool searchTask(int);
	bool searchTask(double);

	void Menu();

	friend class LoginSystem;
	friend class Menu;

public:
	User();
	User(const User& copy);
	User(std::string, std::string, Role role);
	bool operator< (const User& other) const;
	bool operator> (const User& other) const;
};