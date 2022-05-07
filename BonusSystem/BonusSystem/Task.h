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
protected:
	std::string _taskText;

	Task();
	Task(std::string, TaskType);
	
	friend class BonusSystem;
};

