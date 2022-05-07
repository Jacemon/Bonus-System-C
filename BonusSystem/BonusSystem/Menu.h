#pragma once
#include "LoginSystem.h"
#include "checking.h"

#include <string>
#include <memory>

class Menu {
public:
	void startMenu();

	bool showUsers(bool sort);
	bool showEmployees(bool sort);
	bool showTasks(bool sort, int taskType = 0);
	bool showEmployeeTasks(bool sort, int employeeId);
	bool showEmployeeWithMarkedTask(bool sort);

	bool searchUser(std::string);
	bool searchEmployee(std::string, bool);
	bool searchEmployee(int, bool);
	bool searchTask(int);
	bool searchTask(int, bool);
	bool searchTask(double, bool);

	void userMenu(std::shared_ptr<User>);

	void writeLoginSystem(std::shared_ptr<LoginSystem>);
	void readLoginSystem(std::shared_ptr<LoginSystem>);
	void writeBonusSystem(std::shared_ptr<BonusSystem>);
	void readBonusSystem(std::shared_ptr<BonusSystem>);
};

