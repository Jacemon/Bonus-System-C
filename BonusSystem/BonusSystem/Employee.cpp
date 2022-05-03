#include "Employee.h"

#include <iostream>

Employee::Employee() { }

Employee::Employee(std::string name) : _name(name) { }

std::string Employee::getName() {
	return _name;
}

void Employee::setName(std::string name) {
	_name = name;
}

void Employee::markTaskCompleted(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator it = _currentTasks.find(taskId);
	if (it != _currentTasks.end()) {
		_completedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, it->second));
		_currentTasks.erase(it);
	}
}

void Employee::addTask(std::pair<int, std::shared_ptr<Task>> task) {
	_currentTasks.insert(task);
}

bool Employee::deleteTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _currentTasks.find(taskId);
	if (itTsk != _currentTasks.end()) {
		_currentTasks.erase(itTsk);
		return true;
	}
	return false;
}

std::map<int, std::shared_ptr<Task>> Employee::getCurrentTasks() {
	return std::map<int, std::shared_ptr<Task>>(_currentTasks);
}
std::map<int, std::shared_ptr<Task>> Employee::getCompletedTasks() {
	return std::map<int, std::shared_ptr<Task>>(_completedTasks);
}