#include "TaskByPoint.h"

TaskByPoint::TaskByPoint() { }
TaskByPoint::TaskByPoint(std::string taskText, int points) :
	_points(points), Task(taskText, TaskType::byPoint) { }

int TaskByPoint::getPoints() {
	return _points;
}

void TaskByPoint::setPoints(int points) {
	_points = points;
}

void TaskByPoint::setTaskText(std::string taskText) {
	_taskText = taskText;
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
	if (ifs.fail() != 0) {
		throw std::string();
	}
	task._type = Task::TaskType::byPoint;
	return ifs;
}