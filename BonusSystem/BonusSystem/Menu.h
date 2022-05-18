#pragma once
#include "LoginSystem.h"
#include "SourceBonusSystem.h"
#include "checking.h"

#include <string>
#include <memory>

class Menu {
private:
	const std::string LoginSystemFileName = "LoginSytem";
	const std::string BonusSystemFileName = "BonusSytem";
	const std::string SourceBonusSystemFileName = "SourceBonusSystem";
	const std::string Extension = ".dat";
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

	void writeSourceBonusSystem(std::shared_ptr<SourceBonusSystem>);
	void readSourceBonusSystem(std::shared_ptr<SourceBonusSystem>);
	void writeLoginSystem(std::shared_ptr<LoginSystem>);
	void readLoginSystem(std::shared_ptr<LoginSystem>);
	void writeBonusSystem(std::shared_ptr<BonusSystem>);
	void readBonusSystem(std::shared_ptr<BonusSystem>);
};