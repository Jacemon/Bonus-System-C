#pragma once
#include "Task.h"
class TaskByPercent : public Task {
private:
	double _percent;

	TaskByPercent(std::string, double percent);

	friend class BonusSystem;
public:
	double getPercent();

	friend std::ostream& operator<<(std::ostream&, TaskByPercent&);
};

