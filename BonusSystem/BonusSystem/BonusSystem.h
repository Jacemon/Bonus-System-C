#pragma once

#include "User.h"
#include "Task.h"
#include "TaskByPoint.h"
#include "TaskByPercent.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>

class BonusSystem {
private:
	static std::shared_ptr<BonusSystem> _bonusSystem;

	const double TAX = 13; // удержание НДФЛ

	int TaskID = 1;
	int EmployeeID = 1;
	double PointPrice = 0;

	std::map<int, std::shared_ptr<Task>> _allTasks;
	std::map<int, std::shared_ptr<Task>> _freeTasks;
	std::map<int, std::shared_ptr<Task>> _holdedTasks;
	std::map<int, std::shared_ptr<Task>> _completedTasks;

	std::map<int, std::shared_ptr<Employee<std::string>>> _employees;
	std::map<int, int> _taskID_employeeID;
public:
	static std::shared_ptr<BonusSystem> getInstance();
	static std::shared_ptr<BonusSystem> resetToDefault();
	
	void setPointPrice(double pointPrice);
	double getPointPrice();

	int addEmployee(std::string name, double salary);
	void deleteEmployee(int id);
	void editEmployee(int id, std::string name);
	void editEmployee(int id, double salary);

	std::shared_ptr<Employee<std::string>> getEmployeeById(int id);
	std::map<int, Employee<std::string>> getEmployees();

	void addTaskByPoint(std::string text, int points);
	void addTaskByPercent(std::string text, double percents);
	void deleteTask(int id);
	void editTask(int id, std::string text);
	void editTask(int id, double percents);
	void editTask(int id, int points);
	void setTaskCompleted(int id);

	std::map<int, TaskByPoint> getFreeTasksByPoint();
	std::map<int, TaskByPercent> getFreeTasksByPercent();
	std::map<int, TaskByPoint> getHoldedTasksByPoint();
	std::map<int, TaskByPercent> getHoldedTasksByPercent();
	std::map<int, TaskByPoint> getCompletedTasksByPoint();
	std::map<int, TaskByPercent> getCompletedTasksByPercent();

	void setTaskToEmployee(int employeeId, int taskId);
	void deleteTaskFromEmployee(int employeeId, int taskId);
	void editTaskFromEmployee(int employeeId, int taskId, int newTaskId);

	void payBonuses();
	void payBonuses(int employeeId);

	friend std::ofstream& operator<<(std::ofstream& ofs, BonusSystem bs);
	friend std::ifstream& operator>>(std::ifstream& ifs, BonusSystem& bs);
};