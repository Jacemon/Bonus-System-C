#include "TaskByPercent.h"

TaskByPercent::TaskByPercent(std::string taskText, double percent) : 
	_percent(percent), Task(taskText, TaskType::byPercent) { }

double TaskByPercent::getPercent() {
	return _percent;
}
