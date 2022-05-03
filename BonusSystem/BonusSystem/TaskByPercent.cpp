#include "TaskByPercent.h"

TaskByPercent::TaskByPercent(std::string taskText, double percent) : 
	_percent(percent), Task(taskText, TaskType::byPercent) { }

double TaskByPercent::getPercent() {
	return _percent;
}

std::ostream& operator<<(std::ostream& os, TaskByPercent& task) {
	os << task._taskText << " - " << task._percent << "%";
	return os;
}
