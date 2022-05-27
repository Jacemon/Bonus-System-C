#include "SourceOfBonuses.h"
#include <string>

double SourceOfBonuses::getMoney() {
	return _money;
}

std::string SourceOfBonuses::getName() {
	return _name;
}

double SourceOfBonuses::takeMoney(double takedMoney) {
	if (_money >= takedMoney) {
		_money -= takedMoney;
		return takedMoney;
	}
	return 0.0;
}

double SourceOfBonuses::operator+(SourceOfBonuses sb) {
	return _money + sb._money;
}
double SourceOfBonuses::operator+(double value) {
	return _money + value;
}

std::ofstream& operator<<(std::ofstream& ofs, SourceOfBonuses sb) {
	ofs << sb._name << std::endl << sb._money;
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, SourceOfBonuses& sb) {
	std::getline(ifs, sb._name,'\n');
	ifs >> sb._money;
	return ifs;
}