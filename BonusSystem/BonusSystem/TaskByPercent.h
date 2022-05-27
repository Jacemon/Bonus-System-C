#pragma once
#include "Task.h"

class TaskByPercent : public Task {
private:
	double _percent;
public:
	TaskByPercent();
	TaskByPercent(std::string text, double percent);

	double getPercent();
	void setPercent(double percents);

	friend std::ostream& operator<<(std::ostream& os, TaskByPercent task);
	friend std::ofstream& operator<<(std::ofstream& ofs, TaskByPercent task);
	friend std::ifstream& operator>>(std::ifstream& ifs, TaskByPercent& task);

	void setTaskText(std::string text);
};