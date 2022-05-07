#include "Employee.h"

#include <iostream>

Employee::Employee() { }

Employee::Employee(std::string name, double salary) : _name(name), _salary(salary), 
	_percents(0), _points(0) { }

std::string Employee::getName() {
	return _name;
}
void Employee::setName(std::string name) {
	_name = name;
}

double Employee::getSalary() {
	return _salary;
}
void Employee::setSalary(double salary) {
	_salary = salary;
}

int Employee::getPoints() {
	return _points;
}
void Employee::setPoints(int points) {
	_points = points;
}
void Employee::setPercents(double percents) {
	_percents = percents;
}
double Employee::getPercents() {
	return _percents;
}

void Employee::addTask(std::pair<int, std::shared_ptr<Task>> task) {
	_currentTasks.insert(task);
}
void Employee::addCompletedTask(std::pair<int, std::shared_ptr<Task>> task) {
	_completedTasks.insert(task);
}
bool Employee::deleteTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _currentTasks.find(taskId);
	if (itTsk != _currentTasks.end()) {
		_currentTasks.erase(itTsk);
		return true;
	}
	return false;
}
bool Employee::deleteMarkedTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _markedTasks.find(taskId);
	if (itTsk != _markedTasks.end()) {
		_markedTasks.erase(itTsk);
		return true;
	}
	return false;
}
bool Employee::deleteCompletedTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _completedTasks.find(taskId);
	if (itTsk != _completedTasks.end()) {
		_completedTasks.erase(itTsk);
		return true;
	}
	return false;
}
void Employee::markTaskCompleted(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator it = _currentTasks.find(taskId);
	if (it != _currentTasks.end()) {
		_markedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, it->second));
		_currentTasks.erase(it);
	}
}
void Employee::completeTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator it = _markedTasks.find(taskId);
	if (it == _markedTasks.end()) {
		return;
	}
	_completedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, it->second));
	if (it->second->_type == Task::TaskType::byPoint) {
		auto task = std::static_pointer_cast<TaskByPoint>(it->second);
		_points += task->getPoints();
	}
	else if (it->second->_type == Task::TaskType::byPercent) {
		auto task = std::static_pointer_cast<TaskByPercent>(it->second);
		_percents += task->getPercent();
	}
	
	_markedTasks.erase(it);
}

std::map<int, std::shared_ptr<Task>> Employee::getCurrentTasks() {
	return std::map<int, std::shared_ptr<Task>>(_currentTasks);
}
std::map<int, std::shared_ptr<Task>> Employee::getMarkedTasks() {
	return std::map<int, std::shared_ptr<Task>>(_markedTasks);
}
std::map<int, std::shared_ptr<Task>> Employee::getCompletedTasks() {
	return std::map<int, std::shared_ptr<Task>>(_completedTasks);
}

std::ostream& operator<<(std::ostream& os, Employee employee) {
	std::cout << employee._name << " (" << employee._salary << "$) - <" << employee._points << "б./" << employee._percents << "%>";
	for (auto task : employee._currentTasks) {
		if (task.second->_type == Task::TaskType::byPoint) {
			std::cout << std::endl << " " << task.first << " - " << *std::static_pointer_cast<TaskByPoint>(task.second);
		}
		else if (task.second->_type == Task::TaskType::byPercent) {
			std::cout << std::endl << " " << task.first << " - " << *std::static_pointer_cast<TaskByPercent>(task.second);
		}
	}
	for (auto task : employee._markedTasks) {
		if (task.second->_type == Task::TaskType::byPoint) {
			std::cout << std::endl << " " << task.first << " * " << *std::static_pointer_cast<TaskByPoint>(task.second);
		}
		else if (task.second->_type == Task::TaskType::byPercent) {
			std::cout << std::endl << " " << task.first << " * " << *std::static_pointer_cast<TaskByPercent>(task.second);
		}
	}
	for (auto task : employee._completedTasks) {
		if (task.second->_type == Task::TaskType::byPoint) {
			std::cout << std::endl << " " << task.first << " + " << *std::static_pointer_cast<TaskByPoint>(task.second);
		}
		else if (task.second->_type == Task::TaskType::byPercent) {
			std::cout << std::endl << " " << task.first << " + " << *std::static_pointer_cast<TaskByPercent>(task.second);
		}
	}
	return os;
}
std::ofstream& operator<<(std::ofstream& ofs, Employee employee) {
	ofs << employee._name << " " << employee._salary << " "
		<< employee._points << " " << employee._percents << " " 
		<< employee._markedTasks.size() << " " << employee._completedTasks.size() << std::endl;
	for (auto task : employee._markedTasks) {
		ofs << task.first << " ";
	}
	for (auto task : employee._completedTasks) {
		ofs << task.first << " ";
	}
	return ofs;
}
std::ifstream& operator>>(std::ifstream& ifs, Employee& employee) {
	try {
		int marTaskSize, comTaskSize, taskId;
		ifs >> employee._name >> employee._salary
			>> employee._points >> employee._percents >> marTaskSize >> comTaskSize;
		for (int i = 0; i < marTaskSize; i++) {
			ifs >> taskId;
			employee._markedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, nullptr));
		}
		for (int i = 0; i < comTaskSize; i++) {
			ifs >> taskId;
			employee._completedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, nullptr));
		}
	}
	catch (...) {
		throw std::string("Ошибка загрузки работника!");
	}
	return ifs;
}
