#pragma once

#include "User.h"
#include "Task.h"
#include "TaskByPoint.h"
#include "TaskByPercent.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

class BonusSystem {
private:
	static int TaskID;
	static int EmployeeID;

	std::map<int, std::shared_ptr<Task>> _tasks;
	std::map<int, std::shared_ptr<Employee>> _employees;
	std::map<int, int> _taskID_employeeID;

	static double PointPrice;
public:
	void setPointPrice(double);

	int addEmployee(std::string);
	void deleteEmployee(int);
	void editEmployee(int, std::string);

	std::shared_ptr<Employee> getEmployeeById(int);
	std::map<int, Employee> getEmployees();

	void createTaskByPoint(std::string, int);
	void createTaskByPercent(std::string, double);
	void deleteTask(int);
	void editTask(int, std::string);
	void editTask(int, double);
	void editTask(int, int);

	std::map<int, TaskByPoint> getTasksByPoint();
	std::map<int, TaskByPercent> getTasksByPercent();
	// назначить таску сотруднику ()
	// 

	static std::shared_ptr<BonusSystem> getInstance();
	double getPointPrice();
};