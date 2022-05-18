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

	const double tax = 13; // удержание НДФЛ

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
	
	void setPointPrice(double);
	double getPointPrice();

	int addEmployee(std::string, double);
	void deleteEmployee(int);
	void editEmployee(int, std::string);
	void editEmployee(int, double);

	std::shared_ptr<Employee<std::string>> getEmployeeById(int);
	std::map<int, Employee<std::string>> getEmployees();

	void addTaskByPoint(std::string, int);
	void addTaskByPercent(std::string, double);
	void deleteTask(int);
	void editTask(int, std::string);
	void editTask(int, double);
	void editTask(int, int);
	void setTaskCompleted(int);

	std::map<int, TaskByPoint> getFreeTasksByPoint();
	std::map<int, TaskByPercent> getFreeTasksByPercent();
	std::map<int, TaskByPoint> getHoldedTasksByPoint();
	std::map<int, TaskByPercent> getHoldedTasksByPercent();
	std::map<int, TaskByPoint> getCompletedTasksByPoint();
	std::map<int, TaskByPercent> getCompletedTasksByPercent();

	void setTaskToEmployee(int, int);
	void deleteTaskFromEmployee(int, int);
	void editTaskFromEmployee(int, int, int);

	void payBonuses();
	void payBonuses(int);

	friend std::ofstream& operator<<(std::ofstream&, BonusSystem);
	friend std::ifstream& operator>>(std::ifstream&, BonusSystem&);
};

