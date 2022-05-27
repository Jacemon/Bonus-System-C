#pragma once

#include <iostream>
#include <map>

#include "Task.h"
#include "TaskByPoint.h"
#include "TaskByPercent.h"

template <typename T>
class Employee {
private:
	T _name;
	double _salary;
	int _points;
	double _percents;

	std::map<int, std::shared_ptr<Task>> _currentTasks;
	std::map<int, std::shared_ptr<Task>> _markedTasks;
	std::map<int, std::shared_ptr<Task>> _completedTasks;
public:
	Employee();
	Employee(T name, double salary);

	T getName();
	void setName(T name);

	double getSalary();
	void setSalary(double salary);

	int getPoints();
	void setPoints(int points);
	double getPercents();
	void setPercents(double percents);

	void addTask(std::pair<int, std::shared_ptr<Task>> task);
	void addCompletedTask(std::pair<int, std::shared_ptr<Task>> task);
	bool deleteTask(int id);
	bool deleteMarkedTask(int id);
	bool deleteCompletedTask(int id);
	void markTaskCompleted(int id);
	void completeTask(int id);

	std::map<int, std::shared_ptr<Task>> getCurrentTasks();
	std::map<int, std::shared_ptr<Task>> getMarkedTasks();
	std::map<int, std::shared_ptr<Task>> getCompletedTasks();

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, Employee<T> employee) {
		std::cout << employee._name << " (" << employee._salary << "$) - <" << employee._points << "á./" << employee._percents << "%>";
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
	template <typename T>
	friend std::ofstream& operator<<(std::ofstream& ofs, Employee<T> employee) {
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
	template <typename T>
	friend std::ifstream& operator>>(std::ifstream& ifs, Employee<T>& employee) {
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
		if (ifs.fail() != 0) {
			throw std::string();
		}
		return ifs;
	}
};

template <typename T>
Employee<T>::Employee() { }

template <typename T>
Employee<T>::Employee(T name, double salary) : _name(name), _salary(salary),
_percents(0), _points(0) { }

template <typename T>
T Employee<T>::getName() {
	return _name;
}
template <typename T>
void Employee<T>::setName(T name) {
	_name = name;
}

template <typename T>
double Employee<T>::getSalary() {
	return _salary;
}
template <typename T>
void Employee<T>::setSalary(double salary) {
	_salary = salary;
}
template <typename T>
int Employee<T>::getPoints() {
	return _points;
}
template <typename T>
void Employee<T>::setPoints(int points) {
	_points = points;
}
template <typename T>
void Employee<T>::setPercents(double percents) {
	_percents = percents;
}
template <typename T>
double Employee<T>::getPercents() {
	return _percents;
}
template <typename T>
void Employee<T>::addTask(std::pair<int, std::shared_ptr<Task>> task) {
	_currentTasks.insert(task);
}
template <typename T>
void Employee<T>::addCompletedTask(std::pair<int, std::shared_ptr<Task>> task) {
	_completedTasks.insert(task);
}
template <typename T>
bool Employee<T>::deleteTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _currentTasks.find(taskId);
	if (itTsk != _currentTasks.end()) {
		_currentTasks.erase(itTsk);
		return true;
	}
	return false;
}
template <typename T>
bool Employee<T>::deleteMarkedTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _markedTasks.find(taskId);
	if (itTsk != _markedTasks.end()) {
		_markedTasks.erase(itTsk);
		return true;
	}
	return false;
}
template <typename T>
bool Employee<T>::deleteCompletedTask(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator itTsk = _completedTasks.find(taskId);
	if (itTsk != _completedTasks.end()) {
		_completedTasks.erase(itTsk);
		return true;
	}
	return false;
}
template <typename T>
void Employee<T>::markTaskCompleted(int taskId) {
	std::map<int, std::shared_ptr<Task>>::iterator it = _currentTasks.find(taskId);
	if (it != _currentTasks.end()) {
		_markedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, it->second));
		_currentTasks.erase(it);
	}
}
template <typename T>
void Employee<T>::completeTask(int taskId) {
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
template <typename T>
std::map<int, std::shared_ptr<Task>> Employee<T>::getCurrentTasks() {
	return std::map<int, std::shared_ptr<Task>>(_currentTasks);
}
template <typename T>
std::map<int, std::shared_ptr<Task>> Employee<T>::getMarkedTasks() {
	return std::map<int, std::shared_ptr<Task>>(_markedTasks);
}
template <typename T>
std::map<int, std::shared_ptr<Task>> Employee<T>::getCompletedTasks() {
	return std::map<int, std::shared_ptr<Task>>(_completedTasks);
}