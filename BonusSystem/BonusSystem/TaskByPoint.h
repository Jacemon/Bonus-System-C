#pragma once
#include "Task.h"

// разобраться с фриенд бонус
class TaskByPoint : public Task {
private:
	int _points;

	friend class BonusSystem;
public:
	TaskByPoint();
	TaskByPoint(std::string, int);

	int getPoints();

	friend std::ostream& operator<<(std::ostream&, TaskByPoint);
	friend std::ofstream& operator<<(std::ofstream&, TaskByPoint);
	friend std::ifstream& operator>>(std::ifstream&, TaskByPoint&);
};