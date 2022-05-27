#pragma once
#include "Task.h"

class TaskByPoint : public Task {
private:
	int _points;
public:
	TaskByPoint();
	TaskByPoint(std::string text, int points);

	int getPoints();
	void setPoints(int points);

	friend std::ostream& operator<<(std::ostream& os, TaskByPoint task);
	friend std::ofstream& operator<<(std::ofstream& ofs, TaskByPoint task);
	friend std::ifstream& operator>>(std::ifstream& ifs, TaskByPoint& task);

	void setTaskText(std::string text);
};