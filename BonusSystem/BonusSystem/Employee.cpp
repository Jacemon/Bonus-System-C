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
