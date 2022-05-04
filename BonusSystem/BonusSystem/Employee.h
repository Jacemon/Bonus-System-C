#pragma once

#include <iostream>
#include <map>

#include "Task.h"

class Employee {
private:
	std::string _name;

	std::map<int, std::shared_ptr<Task>> _currentTasks;
	std::map<int, std::shared_ptr<Task>> _markedTasks;
	std::map<int, std::shared_ptr<Task>> _completedTasks;
public:
	Employee();
	Employee(std::string);

	std::string getName();
	void setName(std::string);

	void markTaskCompleted(int);
	void completeTask(int);

	void addTask(std::pair<int, std::shared_ptr<Task>>);
	bool deleteTask(int);

	std::map<int, std::shared_ptr<Task>> getCurrentTasks();
	std::map<int, std::shared_ptr<Task>> getMarkedTasks();
	std::map<int, std::shared_ptr<Task>> getCompletedTasks();
};

