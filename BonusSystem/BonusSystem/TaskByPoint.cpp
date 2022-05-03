#include "TaskByPoint.h"

TaskByPoint::TaskByPoint(std::string taskText, int points) :
	_points(points), Task(taskText, TaskType::byPoint) { }

int TaskByPoint::getPoints() {
	return _points;
}

std::ostream& operator<<(std::ostream& os, TaskByPoint& task) {
	os << task._taskText << " - " << task._points << "p.";
	return os;
}