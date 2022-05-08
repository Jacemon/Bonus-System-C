#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <string>

class Task {
public:
	enum class TaskType {
		byPoint,
		byPercent
	};
	TaskType _type;

	std::string getText() {
		return _taskText;
	}
	std::string _taskText;

	Task();
	Task(std::string, TaskType);
	virtual void setTaskText(std::string) = 0;
};

