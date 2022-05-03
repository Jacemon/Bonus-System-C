#include "Task.h"

Task::Task() { }

Task::Task(std::string taskText, TaskType type) {
	_taskText = taskText;
	_type = type;
};