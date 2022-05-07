#include "TaskByPoint.h"

TaskByPoint::TaskByPoint() { }
TaskByPoint::TaskByPoint(std::string taskText, int points) :
	_points(points), Task(taskText, TaskType::byPoint) { }

int TaskByPoint::getPoints() {
	return _points;
}

std::ostream& operator<<(std::ostream& os, TaskByPoint task) {
	os << task._taskText << " - " << task._points << "á.";
	return os;
}

std::ofstream& operator<<(std::ofstream& ofs, TaskByPoint task) {
	ofs << task._taskText << std::endl << task._points;
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, TaskByPoint& task) {
	std::getline(ifs, task._taskText);
	ifs >> task._points;
	task._type = Task::TaskType::byPoint;
	return ifs;
}