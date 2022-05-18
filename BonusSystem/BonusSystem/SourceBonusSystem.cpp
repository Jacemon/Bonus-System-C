#include "SourceBonusSystem.h"

std::shared_ptr<SourceBonusSystem> SourceBonusSystem::_sourceBonusSystem;

std::shared_ptr<SourceBonusSystem> SourceBonusSystem::getInstance() {
    if (_sourceBonusSystem == nullptr) {
        _sourceBonusSystem = std::make_shared<SourceBonusSystem>(SourceBonusSystem());
    }
    return _sourceBonusSystem;
}
std::shared_ptr<SourceBonusSystem> SourceBonusSystem::resetToDefault() {
    _sourceBonusSystem = nullptr;
    return getInstance();
}

double SourceBonusSystem::takeMoney(double money) {
    double allMoney = 0;
    for (auto sb : _sourcesOfBonuses) {
        allMoney += sb->getMoney();
    }
    if (allMoney < money) {
        return 0.0;
    }
    double notTakedMoney = money;
    for (auto sb : _sourcesOfBonuses) {
        if (notTakedMoney == 0) {
            break;
        }
        if (sb->getMoney() >= notTakedMoney) {
            sb->takeMoney(notTakedMoney);
            notTakedMoney = 0;
        }
        else {
            notTakedMoney -= sb->getMoney();
            sb->takeMoney(sb->getMoney());
        }
    }
    return money;
}

std::ofstream& operator<<(std::ofstream& ofs, SourceBonusSystem sourceBonusSystem) {
    ofs << sourceBonusSystem._sourcesOfBonuses.size() << std::endl;
    for (auto sb : sourceBonusSystem._sourcesOfBonuses) {
        ofs << *sb << std::endl;
    }
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, SourceBonusSystem& sourceBonusSystem) {
    try {
        SourceOfBonuses sb;
        int size;
        ifs >> size;
        ifs.ignore(1);
        for (int i = 0; i < size; i++) {
            ifs >> sb;
            if (ifs.fail() != 0) {
                throw std::string();
            }
            sourceBonusSystem._sourcesOfBonuses.push_back(
                std::make_shared<SourceOfBonuses>(sb));
        }
    }
    catch (...) {
        throw std::string("ѕроизошла ошибка загрузки базы данных системы источников премировани€.");
    }
    return ifs;
}