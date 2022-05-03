#pragma once
#include "Task.h"

class TaskByPoint : public Task {
private:
	int _points;

	TaskByPoint(std::string, int);

	friend class BonusSystem;
public:
	int getPoints();
};