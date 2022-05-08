#pragma once
#include "Task.h"

class TaskByPoint : public Task {
private:
	int _points;
public:
	TaskByPoint();
	TaskByPoint(std::string, int);

	int getPoints();
	void setPoints(int);

	friend std::ostream& operator<<(std::ostream&, TaskByPoint);
	friend std::ofstream& operator<<(std::ofstream&, TaskByPoint);
	friend std::ifstream& operator>>(std::ifstream&, TaskByPoint&);

	void setTaskText(std::string);
};