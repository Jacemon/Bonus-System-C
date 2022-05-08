#include "TaskByPercent.h"

TaskByPercent::TaskByPercent() { }
TaskByPercent::TaskByPercent(std::string taskText, double percent) : 
	_percent(percent), Task(taskText, TaskType::byPercent) { }

double TaskByPercent::getPercent() {
	return _percent;
}

void TaskByPercent::setPercent(double percent) {
	_percent = percent;
}

void TaskByPercent::setTaskText(std::string taskText) {
	_taskText = taskText;
}

std::ostream& operator<<(std::ostream& os, TaskByPercent task) {
	os << task._taskText << " - " << task._percent << "%";
	return os;
}

std::ofstream& operator<<(std::ofstream& ofs, TaskByPercent task) {
	ofs << task._taskText << std::endl << task._percent;
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, TaskByPercent& task) {
	std::getline(ifs, task._taskText);
	ifs >> task._percent;
	if (ifs.fail() != 0) {
		throw std::string();
	}
	task._type = Task::TaskType::byPercent;
	return ifs;
}