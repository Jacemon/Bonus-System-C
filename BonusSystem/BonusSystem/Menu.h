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

	bool searchUser(std::string login);
	bool searchEmployee(std::string name, bool sort);
	bool searchEmployee(int id, bool sort);
	bool searchTask(int id);
	bool searchTask(int points, bool sort);
	bool searchTask(double percents, bool sort);

	bool searchTaskWithBorder(double percents, bool sort, bool flag);
	bool searchTaskWithBorder(int points, bool sort, bool flag);

	void userMenu(std::shared_ptr<User> user);

	void writeSourceBonusSystem(std::shared_ptr<SourceBonusSystem> sbs);
	void readSourceBonusSystem(std::shared_ptr<SourceBonusSystem> sbs);
	void writeLoginSystem(std::shared_ptr<LoginSystem> ls);
	void readLoginSystem(std::shared_ptr<LoginSystem> ls);
	void writeBonusSystem(std::shared_ptr<BonusSystem> bs);
	void readBonusSystem(std::shared_ptr<BonusSystem> bs);
};