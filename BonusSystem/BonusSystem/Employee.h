#pragma once

#include <iostream>
#include <map>

#include "Task.h"
#include "TaskByPoint.h"
#include "TaskByPercent.h"

class Employee {
private:
	std::string _name;
	double _salary;
	int _points;
	double _percents;

	std::map<int, std::shared_ptr<Task>> _currentTasks;
	std::map<int, std::shared_ptr<Task>> _markedTasks;
	std::map<int, std::shared_ptr<Task>> _completedTasks;
public:
	Employee();
	Employee(std::string, double);

	std::string getName();
	void setName(std::string);

	double getSalary();
	void setSalary(double);

	int getPoints();
	void setPoints(int);
	double getPercents();
	void setPercents(double);

	void addTask(std::pair<int, std::shared_ptr<Task>>);
	void addCompletedTask(std::pair<int, std::shared_ptr<Task>>);
	bool deleteTask(int);
	bool deleteMarkedTask(int);
	bool deleteCompletedTask(int);
	void markTaskCompleted(int);
	void completeTask(int);

	std::map<int, std::shared_ptr<Task>> getCurrentTasks();
	std::map<int, std::shared_ptr<Task>> getMarkedTasks();
	std::map<int, std::shared_ptr<Task>> getCompletedTasks();

	friend std::ostream& operator<< (std::ostream&, Employee);
	friend std::ofstream& operator<< (std::ofstream&, Employee);
	friend std::ifstream& operator>> (std::ifstream&, Employee&);
};

