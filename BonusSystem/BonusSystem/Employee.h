#pragma once

#include <iostream>
#include <vector>

#include "Task.h"

class Employee {
private:
	std::string _name;

	std::vector<Task> currentTasks;
	std::vector<Task> completedTasks;
public:
	Employee();
	Employee(std::string);

	std::string getName();
	void setName(std::string);
};

