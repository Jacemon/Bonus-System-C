#pragma once

#include <iostream>
#include <fstream>

class SourceOfBonuses {
private:
	double _money = 0;
	std::string _name;
public:
	double getMoney();
	std::string getName();

	double takeMoney(double);
	friend std::ofstream& operator<<(std::ofstream& ofs, SourceOfBonuses sb);
	friend std::ifstream& operator>>(std::ifstream& ifs, SourceOfBonuses& sb);

	double operator+(SourceOfBonuses sb);
	double operator+(double money);
};