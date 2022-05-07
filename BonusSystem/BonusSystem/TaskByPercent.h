#pragma once
#include "Task.h"
class TaskByPercent : public Task {
private:
	double _percent;

	friend class BonusSystem;
public:
	TaskByPercent();
	TaskByPercent(std::string, double percent);

	double getPercent();

	friend std::ostream& operator<<(std::ostream&, TaskByPercent);
	friend std::ofstream& operator<<(std::ofstream&, TaskByPercent);
	friend std::ifstream& operator>>(std::ifstream&, TaskByPercent&);
};

