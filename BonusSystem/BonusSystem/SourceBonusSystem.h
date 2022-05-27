#pragma once

#include "SourceOfBonuses.h"

#include <memory>
#include <vector>

class SourceBonusSystem {
private:
	std::vector<std::shared_ptr<SourceOfBonuses>> _sourcesOfBonuses;

	static std::shared_ptr<SourceBonusSystem> _sourceBonusSystem;
public:
	static std::shared_ptr<SourceBonusSystem> getInstance();
	static std::shared_ptr<SourceBonusSystem> resetToDefault();
	
	double takeMoney(double money);

	friend std::ofstream& operator<<(std::ofstream& ofs, SourceBonusSystem sbs);
	friend std::ifstream& operator>>(std::ifstream& ifs, SourceBonusSystem& sbs);
};