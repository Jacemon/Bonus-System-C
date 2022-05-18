#include "Menu.h"

void Menu::writeSourceBonusSystem(std::shared_ptr<SourceBonusSystem> sourceBonusSystem) {
    std::ofstream fout;
    fout.open(SourceBonusSystemFileName + Extension, std::ios::binary);
    fout << *sourceBonusSystem;
    fout.close();
}

void Menu::readSourceBonusSystem(std::shared_ptr<SourceBonusSystem> sourceBonusSystem) {
    std::ifstream fin;
    fin.open(SourceBonusSystemFileName + Extension, std::ios::binary);
    fin >> *sourceBonusSystem;
    fin.close();
}

void Menu::writeLoginSystem(std::shared_ptr<LoginSystem> loginSystem) {
    std::ofstream fout;
    fout.open(LoginSystemFileName + Extension, std::ios::binary);
    fout << *loginSystem;
    fout.close();
}

void Menu::readLoginSystem(std::shared_ptr<LoginSystem> loginSystem) {
    std::ifstream fin;
    fin.open(LoginSystemFileName + Extension, std::ios::binary);
    fin >> *loginSystem;
    fin.close();
}

void Menu::writeBonusSystem(std::shared_ptr<BonusSystem> bonusSystem) {
    std::ofstream fout;
    fout.open(BonusSystemFileName + Extension, std::ios::binary);
    fout << *bonusSystem;
    fout.close();
}

void Menu::readBonusSystem(std::shared_ptr<BonusSystem> bonusSystem) {
    std::ifstream fin;
    fin.open(BonusSystemFileName + Extension, std::ios::binary);
    try {
        fin >> *bonusSystem;
    }
    catch (std::string exc) {
        throw exc;
    }
    fin.close();
}

void Menu::startMenu() {
	system("chcp 1251>nul");

	std::shared_ptr<LoginSystem> loginSystem = LoginSystem::getInstance();
	std::shared_ptr<BonusSystem> bonusSystem = BonusSystem::getInstance();
    std::shared_ptr<SourceBonusSystem> sourceBonusSystem = SourceBonusSystem::getInstance();
	std::shared_ptr<User> user;
	std::string login;
	std::string password;

    try {
        readBonusSystem(bonusSystem);
        readLoginSystem(loginSystem);
        readSourceBonusSystem(sourceBonusSystem);
    }
    catch (std::string exc) {
        std::cout << exc << std::endl;
        if (check::getCharValueFromString("yn", "����������� ���� ������? ��� ������ ����� ��������! (y/n)\n>>> ",
            "�������� ����!") == 'y') {
            loginSystem = LoginSystem::resetToDefault();
            bonusSystem = BonusSystem::resetToDefault();
            sourceBonusSystem = SourceBonusSystem::getInstance();
        }
        else {
            return;
        }
    }

	while (true) {
		system("cls");
		std::cout << "1. ����" << std::endl;
		std::cout << "2. ����������" << std::endl;
		std::cout << "3. ����� ���� ������" << std::endl;
		std::cout << "4. �����" << std::endl;
		switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
		case 1:
			login = check::getWordValue("������� �����: ", "�������� ����!");
			password = check::getPasswordValue("������� ������ (���. " 
				+ std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
				" ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);
			user = (*loginSystem).LogIn(login, password);
			if (user != nullptr) {
				userMenu(user);
			}
            else {
                std::cout << "������������ ����� ��� ������!" << std::endl;
            }
			user = nullptr;
			break;
		case 2:
			std::cout << "��� ���������� ���������� \033[33m\"������� ������� �����������"
				<< " �� ����������� ����\"\033[0m\n���� ����������� ��������� "
				<< "\033[36m��. 024402 \033[35m�������� �.�.\033[0m, 2022 �." << std::endl;
			break;
        case 3:
            if (check::getCharValueFromString("yn", "�� �������, ��� ������ ��� �������? ��� ������ ����� ��������! (y/n)\n>>> ",
                "�������� ����!") == 'y') {
                loginSystem = LoginSystem::resetToDefault();
                bonusSystem = BonusSystem::resetToDefault();
            }
            break;
		case 4:
            writeBonusSystem(bonusSystem);
            writeLoginSystem(loginSystem);
            writeSourceBonusSystem(sourceBonusSystem);
			return;
		}
        std::cout << "��� ����������� ������� ����� �������..." << std::endl;
        system("pause>nul");
	}
}

bool Menu::showUsers(bool sort) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::map<std::string, User> users;
    users = (*_loginSystem).getUsers();
    if (users.empty()) {
        std::cout << "������������� ���." << std::endl;
        return false;
    }
    std::cout << "-<������������>-" << std::endl;
    if (sort) {
        for (auto it = users.begin(); it != users.end(); it++) {
            std::cout << " - " << it->second;
        }
    }
    else {
        for (auto it = users.rbegin(); it != users.rend(); it++) {
            std::cout << " - " << it->second;
        }
    }
    return true;
}

bool Menu::showEmployees(bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee<std::string>> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    if (employees.empty()) {
        std::cout << "���������� ���." << std::endl;
        return false;
    }

    std::cout << "-<���������>-" << std::endl;
    if (sort) {
        for (auto itE = employees.begin(); itE != employees.end(); itE++) {
            std::cout << itE->first << " - " << itE->second << std::endl;
        }
    }
    else {
        for (auto itE = employees.rbegin(); itE != employees.rend(); itE++) {
            std::cout << itE->first << " - " << itE->second.getName() << std::endl;
        }
    }
    return true;
}

bool Menu::showTasks(bool sort, int taskType) {
    bool flag1 = false, flag2 = false, flag3 = false;
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, TaskByPercent> tasksByPercent;
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();

    switch (taskType) {
    case 0:
    case 1:
        if (taskType != 1 && taskType != 0) {
            break;
        }
        tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
        tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
        if (!tasksByPoint.empty() || !tasksByPercent.empty()) {
            std::cout << "-<��������� ������>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-�� ������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPoint.begin(); it != tasksByPoint.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPoint.rbegin(); it != tasksByPoint.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            if (!tasksByPercent.empty()) {
                std::cout << "-�� ���������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPercent.begin(); it != tasksByPercent.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPercent.rbegin(); it != tasksByPercent.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            flag1 = true;
        }
    case 2:
        if (taskType != 2 && taskType != 0) {
            break;
        }
        tasksByPoint = (*_bonusSystem).getHoldedTasksByPoint();
        tasksByPercent = (*_bonusSystem).getHoldedTasksByPercent();
        if (!tasksByPoint.empty() || !tasksByPercent.empty()) {
            std::cout << "-<������ ������>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-�� ������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPoint.begin(); it != tasksByPoint.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPoint.rbegin(); it != tasksByPoint.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            if (!tasksByPercent.empty()) {
                std::cout << "-�� ���������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPercent.begin(); it != tasksByPercent.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPercent.rbegin(); it != tasksByPercent.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            flag2 = true;
        }
    case 3:
        if (taskType != 3 && taskType != 0) {
            break;
        }
        tasksByPoint = (*_bonusSystem).getCompletedTasksByPoint();
        tasksByPercent = (*_bonusSystem).getCompletedTasksByPercent();
        if (!tasksByPoint.empty() || !tasksByPercent.empty()) {
            std::cout << "-<����������� ������>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-�� ������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPoint.begin(); it != tasksByPoint.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPoint.rbegin(); it != tasksByPoint.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            if (!tasksByPercent.empty()) {
                std::cout << "-�� ���������-" << std::endl;
                if (sort) {
                    for (auto it = tasksByPercent.begin(); it != tasksByPercent.end(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
                else {
                    for (auto it = tasksByPercent.rbegin(); it != tasksByPercent.rend(); it++) {
                        std::cout << it->first << " - " << it->second << std::endl;
                    }
                }
            }
            flag3 = true;
        }
        break;
    }
    if (taskType == 0) {
        if (flag1 == 0 && flag2 == 0 && flag3 == 0) {
            std::cout << "����� ���." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 1) {
        if (flag1 == 0) {
            std::cout << "��������� ����� ���." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 2) {
        if (flag2 == 0) {
            std::cout << "���������� ����� ���." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 3) {
        if (flag3 == 0) {
            std::cout << "��������� ����� ���." << std::endl;
            return false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool Menu::showEmployeeTasks(bool sort, int employeeId) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, std::shared_ptr<Task>> tasks;
    tasks = (*_bonusSystem).getEmployeeById(employeeId)->getCurrentTasks();
    if (tasks.empty()) {
        std::cout << "� ��������� ��� �����." << std::endl;
        return false;
    }
    std::cout << "-<������������ ������ ���������>-" << std::endl;
    if (sort) {
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << it->first << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << it->first << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
    }
    else {
        for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << it->first << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << it->first << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
    }
    return true;
}

bool Menu::showEmployeeWithMarkedTask(bool sort) {
    bool flag = false;
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee<std::string>> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    std::cout << "-<��������� � ����������� ��������>-" << std::endl;
    if (sort) {
        for (auto it = employees.begin(); it != employees.end(); it++) {
            tasks = it->second.getMarkedTasks();
            if (tasks.empty()) {
                continue;
            }
            flag = true;
            std::cout << it->first << " - " << it->second.getName() << std::endl;
            for (auto it = tasks.begin(); it != tasks.end(); it++) {
                if (it->second->_type == Task::TaskType::byPoint) {
                    std::cout << " * " << it->first << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                }
                if (it->second->_type == Task::TaskType::byPercent) {
                    std::cout << " * " << it->first << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                }
            }
        }
    }
    else {
        for (auto it = employees.rbegin(); it != employees.rend(); it++) {
            tasks = it->second.getMarkedTasks();
            if (tasks.empty()) {
                continue;
            }
            flag = true;
            std::cout << it->first << " - " << it->second.getName() << std::endl;
            for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
                if (it->second->_type == Task::TaskType::byPoint) {
                    std::cout << " * " << it->first << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                }
                if (it->second->_type == Task::TaskType::byPercent) {
                    std::cout << " * " << it->first << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                }
            }
        }
    }
    if (!flag) {
        std::cout << "���������� � ����������� �������� ���." << std::endl;
    }
    return flag;
}

bool Menu::searchUser(std::string login) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    auto users = (*_loginSystem).getUsers();
    if (users.empty()) {
        std::cout << "������������� ���." << std::endl;
        return false;
    }
    auto it = users.find(login);
    if (it == users.end()) {
        std::cout << "������������ �� ������." << std::endl;
        return false;
    }
    std::cout << "-<������ ������������>-" << std::endl;
    std::cout << " - " << it->second._login;
    if (it->second._employee.second != nullptr) {
        std::cout << " -> " << it->second._employee.second->getName();
    }
    std::cout << std::endl;
    return true;
}

bool Menu::searchEmployee(int employeeId, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee<std::string>> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    if (employees.empty()) {
        std::cout << "���������� ���." << std::endl;
        return false;
    }

    auto itE = employees.find(employeeId);

    if (itE == employees.end()) {
        std::cout << "�������� �� ������." << std::endl;
        return false;
    }

    std::cout << "-<�������� �� ID>-" << std::endl;

    std::cout << itE->first << " - " << itE->second.getName() << std::endl;

    if (sort) {
        tasks = itE->second.getCurrentTasks();
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
        tasks = itE->second.getMarkedTasks();
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " * " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " * " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
        tasks = itE->second.getCompletedTasks();
        for (auto it = tasks.begin(); it != tasks.end(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " + " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " + " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
    }
    else {
        tasks = itE->second.getCurrentTasks();
        for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
        tasks = itE->second.getMarkedTasks();
        for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " * " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " * " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
        tasks = itE->second.getCompletedTasks();
        for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
            if (it->second->_type == Task::TaskType::byPoint) {
                std::cout << " + " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
            }
            if (it->second->_type == Task::TaskType::byPercent) {
                std::cout << " + " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
            }
        }
    }
    return true;
}

bool Menu::searchEmployee(std::string employeeName, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee<std::string>> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    if (employees.empty()) {
        std::cout << "���������� ���." << std::endl;
        return false;
    }

    auto itE = employees.begin();
    itE = std::find_if(employees.begin(), employees.end(),
        [&](std::pair<int, Employee<std::string>> pair) -> bool {
            if (pair.second.getName() == employeeName) {
                return true;
            }
            return false;
        });

    if (itE == employees.end()) {
        std::cout << "��������� �� ������." << std::endl;
        return false;
    }

    std::cout << "-<�������� �� ID>-" << std::endl;

    for (auto itE = employees.begin(); itE != employees.end(); itE++) {
        if (itE->second.getName() == employeeName) {
            std::cout << itE->first << " - " << itE->second.getName() << std::endl;

            if (sort) {
                tasks = itE->second.getCurrentTasks();
                for (auto it = tasks.begin(); it != tasks.end(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
                tasks = itE->second.getMarkedTasks();
                for (auto it = tasks.begin(); it != tasks.end(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " * " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " * " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
                tasks = itE->second.getCompletedTasks();
                for (auto it = tasks.begin(); it != tasks.end(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " + " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " + " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
            }
            else {
                tasks = itE->second.getCurrentTasks();
                for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " - " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " - " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
                tasks = itE->second.getMarkedTasks();
                for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " * " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " * " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
                tasks = itE->second.getCompletedTasks();
                for (auto it = tasks.rbegin(); it != tasks.rend(); it++) {
                    if (it->second->_type == Task::TaskType::byPoint) {
                        std::cout << " + " << *std::static_pointer_cast<TaskByPoint>(it->second) << std::endl;
                    }
                    if (it->second->_type == Task::TaskType::byPercent) {
                        std::cout << " + " << *std::static_pointer_cast<TaskByPercent>(it->second) << std::endl;
                    }
                }
            }
        }
    }
    return true;
}

bool Menu::searchTask(int taskId) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    auto tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
    auto tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
    auto itTskByPnt = tasksByPoint.find(taskId);
    if (itTskByPnt != tasksByPoint.end()) {
        std::cout << "-<������ �� ID>-" << std::endl;
        std::cout << itTskByPnt->first << " - " << itTskByPnt->second << std::endl;
        return true;
    }
    auto itTskByPct = tasksByPercent.find(taskId);
    if (itTskByPct != tasksByPercent.end()) {
        std::cout << "-<������ �� ID>-" << std::endl;
        std::cout << itTskByPct->first << " - " << itTskByPct->second << std::endl;
        return true;
    }
    std::cout << "������ �� �������." << std::endl;
    return false;
}

bool Menu::searchTask(int points, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    auto tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
    if (tasksByPoint.empty()) {
        std::cout << "����� �� ������ ���." << std::endl;
    }
    auto itTskByPnt = std::find_if(tasksByPoint.begin(), tasksByPoint.end(),
        [&](std::pair<int, TaskByPoint> pair) -> bool {
            if (pair.second.getPoints() == points) {
                return true;
            }
            return false;
        });
    if (itTskByPnt == tasksByPoint.end()) {
        std::cout << "������ �� ������ �� �������." << std::endl;
        return false;
    }

    std::cout << "-<������ �� ������>-" << std::endl;
    if (sort) {
        for (itTskByPnt = tasksByPoint.begin(); itTskByPnt != tasksByPoint.end(); itTskByPnt++) {
            if (itTskByPnt->second.getPoints() == points) {
                std::cout << itTskByPnt->first << " - " << itTskByPnt->second << std::endl;
            }
        }
    }
    else {
        for (auto itTskByPnt = tasksByPoint.rbegin(); itTskByPnt != tasksByPoint.rend(); itTskByPnt++) {
            if (itTskByPnt->second.getPoints() == points) {
                std::cout << itTskByPnt->first << " - " << itTskByPnt->second << std::endl;
            }
        }
    }
    return true;
}

bool Menu::searchTask(double percent, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    auto tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
    if (tasksByPercent.empty()) {
        std::cout << "����� �� ��������� ���." << std::endl;
    }
    auto itTskByPct = std::find_if(tasksByPercent.begin(), tasksByPercent.end(),
        [&](std::pair<int, TaskByPercent> pair) -> bool {
            if (pair.second.getPercent() == percent) {
                return true;
            }
            return false;
        });
    if (itTskByPct == tasksByPercent.end()) {
        std::cout << "������ �� ������ �� �������." << std::endl;
        return false;
    }

    std::cout << "-<������ �� ������>-" << std::endl;
    if (sort) {
        for (itTskByPct = tasksByPercent.begin(); itTskByPct != tasksByPercent.end(); itTskByPct++) {
            if (itTskByPct->second.getPercent() == percent) {
                std::cout << itTskByPct->first << " - " << itTskByPct->second << std::endl;
            }
        }
    }
    else {
        for (auto itTskByPct = tasksByPercent.rbegin(); itTskByPct != tasksByPercent.rend(); itTskByPct++) {
            if (itTskByPct->second.getPercent() == percent) {
                std::cout << itTskByPct->first << " - " << itTskByPct->second << std::endl;
            }
        }
    }
    return true;
}

void Menu::userMenu(std::shared_ptr<User> mainUser) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();

    std::string userLogin, userPassword;
    std::string newUserLogin, newUserPassword;
    std::string employeeName, newEmployeeName;
    std::string taskText;
    int employeeId, taskId;
    int points;
    double percents;
    double salary;
    bool sort = true;

    std::shared_ptr<User> user;
    std::shared_ptr<Employee<std::string>> employee;
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, TaskByPercent> tasksByPercent;

    switch (mainUser->_role) {
    case User::Role::admin:
        while (true) {
            system("cls");
            std::cout << "����� ���� -" + mainUser->_login + "-: " << std::endl;
            std::cout << "1. �������������� � ��������������" << std::endl;
            std::cout << "2. �������������� � �����������" << std::endl;
            std::cout << "3. �������������� � ��������" << std::endl;
            std::cout << "4. �������������� � ����� �����" << std::endl;
            std::cout << "5. ��������� ������" << std::endl;
            std::cout << "6. ���������� ��� ����������" << std::endl;
            std::cout << "7. �����" << std::endl;
            std::cout << "8. <- ����� �� -" + mainUser->_login + "-" << std::endl;

            switch (check::getNaturalValueBefore(8, ">>> ", "�������� ����!")) {
            case 1:
                system("cls");

                showUsers(sort);

                std::cout << "1. �������� ������������" << std::endl;
                std::cout << "2. �������� ������������" << std::endl;
                std::cout << "3. ������� ������������" << std::endl;
                std::cout << "4. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                case 1:
                    userLogin = check::getWordValue("������� �����: ", "�������� ����!");
                    userPassword = check::getPasswordValue("������� ������ (���. "
                        + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                        " ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);

                    (*_loginSystem).addUser(userLogin, userPassword, User::Role::common);
                    break;
                case 2:
                    if (!showUsers(sort)) {
                        break;
                    }

                    userLogin = check::getWordValue("������� ����� ����������� ������������: ", "�������� ����!");
                    user = (*_loginSystem).getUserByLogin(userLogin);
                    if (user == nullptr) {
                        std::cout << "������������ � ������ ������� �� ����������!" << std::endl;
                        break;
                    }

                    std::cout << "1. �������� �����" << std::endl;
                    std::cout << "2. �������� ������" << std::endl;
                    std::cout << "3. ��������� ���������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        newUserLogin = check::getWordValue("������� ����� �����: ", "�������� ����!");

                        (*_loginSystem).editUserLogin(userLogin, newUserLogin);
                        break;
                    case 2:
                        newUserPassword = check::getPasswordValue("������� ����� ������ (���. "
                            + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                            " ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);

                        (*_loginSystem).editUserPassword(userLogin, newUserPassword);
                        break;
                    case 3:
                        if (!showEmployees(sort)) {
                            break;
                        }

                        employeeId = check::getNaturalValue("������� ID ������ ���������: ", "�������� ����!");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "��������� � ����� ID �� ����������" << std::endl;
                            break;
                        }
                        (*_loginSystem).setEmployeeToUser(_bonusSystem, userLogin, employeeId);
                        break;
                    }
                    break;
                case 3:
                    if (!showUsers(sort)) {
                        break;
                    }

                    userLogin = check::getWordValue("������� ����� ��� ��������: ", "�������� ����!");

                    (*_loginSystem).deleteUser(userLogin);
                    break;
                }
                break;
            case 2:
                system("cls");

                showEmployees(sort);

                std::cout << "1. �������� ���������" << std::endl;
                std::cout << "2. �������� ���������" << std::endl;
                std::cout << "3. ������� ���������" << std::endl;
                std::cout << "4. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                case 1:
                    employeeName = check::getProperNameValue("������� ��� ���������: ", "�������� ����");
                    salary = check::getDoubleValue("������� �������� ���������: ", "�������� ����");
                    (*_bonusSystem).addEmployee(employeeName, salary);
                    break;
                case 2:
                    if (!showEmployees(sort)) {
                        break;
                    }

                    employeeId = check::getNaturalValue("������� ID ��������� ��� ���������: ", "�������� ����");

                    std::cout << "1. �������� ���" << std::endl;
                    std::cout << "2. �������� ��������" << std::endl;
                    std::cout << "3. �������� ������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        newEmployeeName = check::getProperNameValue("������� ����� ��� ���������: ", "�������� ����");
                        (*_bonusSystem).editEmployee(employeeId, newEmployeeName);
                        break;
                    case 2:
                        salary = check::getDoubleValue("������� ����� �������� ���������: ", "�������� ����");
                        (*_bonusSystem).editEmployee(employeeId, salary);
                        break;
                    case 3:
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        std::cout << *employee << std::endl;

                        std::cout << "1. �������� ������" << std::endl;
                        std::cout << "2. �������� ������ �����������" << std::endl;
                        std::cout << "3. ������� ������" << std::endl;
                        std::cout << "4. <- �����" << std::endl;

                        switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                        case 1:
                            if (!showTasks(sort, 1)) {
                                break;
                            }

                            taskId = check::getNaturalValue("������� ID ������ ��� ����������: ", "�������� ����!");

                            (*_bonusSystem).setTaskToEmployee(employeeId, taskId);
                            break;
                        case 2:
                            std::cout << "������������� ������ ( - ) | ���������� ������ ( * ) | ����������� ������ ( + )" << std::endl;
                            std::cout << "�������� ����� ������ ������������� ������!" << std::endl;
                            taskId = check::getNaturalValue("������� ID ������ ������� ������ ��������: ", "�������� ����!");
                            employee->markTaskCompleted(taskId);
                            break;
                        case 3:
                            std::cout << "������� ����� ������ ��������� ������!" << std::endl;
                            taskId = check::getNaturalValue("������� ID ������ ��� ��������: ", "�������� ����!");

                            (*_bonusSystem).deleteTaskFromEmployee(employeeId, taskId);
                            break;
                        }
                        break;
                    }
                    break;
                case 3:
                    if (!showEmployees(sort)) {
                        break;
                    }

                    employeeId = check::getNaturalValue("������� ID ��������� ��� ��������: ", "�������� ����");
                    (*_bonusSystem).deleteEmployee(employeeId);
                    (*_loginSystem).deleteEmployeeOnUsers(employeeId);
                    break;
                }
                break;
            case 3:
                system("cls");

                showTasks(sort);

                std::cout << "1. �������� ������" << std::endl;
                std::cout << "2. �������� ������" << std::endl;
                std::cout << "3. ������� ������" << std::endl;
                std::cout << "4. ����������� ���������� ������" << std::endl;
                std::cout << "5. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(5, ">>> ", "�������� ����!")) {
                case 1:
                    std::cout << "������� ����� ������� (Enter ��� ����� �����): ";
                    std::getline(std::cin, taskText, '\n');

                    std::cout << "1. �������� ������ �� �����" << std::endl;
                    std::cout << "2. �������� ������ �� ������� �� �/�" << std::endl;
                    std::cout << "3. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                    case 1:
                        points = check::getNaturalValue("������� ���������� ������: ", "�������� ����!");
                        (*_bonusSystem).addTaskByPoint(taskText, points);
                        break;
                    case 2:
                        percents = check::getDoubleValueFromTo(0, 100, "������� ���������� ���������: ", "�������� ����!");
                        (*_bonusSystem).addTaskByPercent(taskText, percents);
                        break;
                    }
                    break;
                case 2:
                    std::cout << "�������� ����� ������ ��������� ������!" << std::endl;
                    if (!showTasks(sort, 1)) {
                        break;
                    }

                    std::cout << "1. �������� ����� ������" << std::endl;
                    std::cout << "2. �������� ����� ������" << std::endl;
                    std::cout << "3. �������� �������� ������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        taskId = check::getNaturalValue("������� ID ������ ��� ���������: ", "�������� ����!");
                        std::cout << "������� ����� ����� ������� (Enter ��� ����� �����): ";
                        std::getline(std::cin, taskText, '\n');

                        (*_bonusSystem).editTask(taskId, taskText);
                        break;
                    case 2:
                        tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
                        if (tasksByPoint.empty()) {
                            std::cout << "����� �� ����� ���." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ �� ������ ��� ���������: ", "�������� ����!");
                        points = check::getNaturalValue("������� ����� ���������� ������: ", "�������� ����!");

                        (*_bonusSystem).editTask(taskId, points);
                        break;
                    case 3:
                        tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
                        if (tasksByPercent.empty()) {
                            std::cout << "����� �� �������� ���." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ �� ��������� ��� ���������: ", "�������� ����!");
                        percents = check::getDoubleValueFromTo(0, 100, "������� ����� ���������� ���������: ", "�������� ����!");

                        (*_bonusSystem).editTask(taskId, percents);
                        break;
                    }
                    break;
                case 3:
                    tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
                    tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
                    if (tasksByPoint.empty() && tasksByPercent.empty()) {
                        std::cout << "����� ���." << std::endl;
                        break;
                    }

                    taskId = check::getNaturalValue("������� ID ������ ��� ��������: ", "�������� ����!");
                    (*_bonusSystem).deleteTask(taskId);
                    break;
                case 4:
                    if (!showEmployeeWithMarkedTask(sort)) {
                        break;
                    }

                    employeeId = check::getNaturalValue("������� ID ��������� �������� ��������� ������: ");
                    employee = (*_bonusSystem).getEmployeeById(employeeId);
                    if (employee == nullptr) {
                        std::cout << "��������� � ����� ID �� ����������" << std::endl;
                        break;
                    }
                    taskId = check::getNaturalValue("������� ID ������ ������� ������ ���������: ", "�������� ����!");
                    (*_bonusSystem).setTaskCompleted(taskId);

                    break;
                }
                break;
            case 4:
                std::cout << "������� ���� �����: 1�. = " << (*_bonusSystem).getPointPrice() << "$" << std::endl;

                std::cout << "1. ���������� ����� ���� �����" << std::endl;
                std::cout << "2. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(2, ">>> ", "�������� ����!")) {
                case 1:
                    (*_bonusSystem).setPointPrice(check::getDoubleValueFromTo(0, 100, "������� ���������� $ �� ����: ", "�������� ����!"));
                    break;
                }
                break;
            case 5:
                if (!showEmployees(sort)) {
                    break;
                }

                std::cout << "1. ��������� ������" << std::endl;
                std::cout << "2. ��������� ����" << std::endl;
                std::cout << "3. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                case 1:
                    employeeId = check::getNaturalValue("������� ID ��������� ��� ������� ������: ", "�������� ����");
                    (*_bonusSystem).payBonuses(employeeId);
                    break;
                case 2:
                    (*_bonusSystem).payBonuses();
                    break;
                }
                break;
            case 6:
                std::cout << "1. �� �����������" << std::endl;
                std::cout << "2. �� ��������" << std::endl;
                std::cout << "3. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                case 1:
                    sort = false;
                    break;
                case 2:
                    sort = true;
                    break;
                }
                break;
            case 7:
                std::cout << "1. ����� ������������" << std::endl;
                std::cout << "2. ����� ���������" << std::endl;
                std::cout << "3. ����� ������" << std::endl;
                std::cout << "4. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                case 1:
                    userLogin = check::getWordValue("������� �����: ", "�������� ����!");
                    searchUser(userLogin);
                    break;
                case 2:
                    std::cout << "1. ����� �� ����" << std::endl;
                    std::cout << "2. ����� �� �����" << std::endl;
                    std::cout << "3. <- �����" << std::endl;
                    switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                    case 1:
                        employeeId = check::getNaturalValue("������� ID �������� ���������: ");
                        searchEmployee(employeeId, sort);
                        break;
                    case 2:
                        employeeName = check::getProperNameValue("������� ��� �������� ���������: ", "�������� ����!");
                        searchEmployee(employeeName, sort);
                        break;
                    }
                    break;
                case 3:
                    std::cout << "1. ����� �� ����" << std::endl;
                    std::cout << "2. ����� �� ���������� ������" << std::endl;
                    std::cout << "3. ����� �� ���������� ���������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        taskId = check::getNaturalValue("������� ID ������� ������: ");
                        searchTask(taskId);
                        break;
                    case 2:
                        points = check::getNaturalValue("������� ���������� ������: ", "�������� ����!");
                        searchTask(points, sort);
                        break;
                    case 3:
                        percents = check::getDoubleValueFromTo(0, 100, "������� ���������� ���������: ", "�������� ����!");
                        searchTask(percents, sort);
                        break;
                    }
                    break;
                }
                break;
            case 8:
                return;
            }
            std::cout << "��� ����������� ������� ����� �������..." << std::endl;
            system("pause>nul");
        }
        break;
    case User::Role::common:
        while (true) {
            system("cls");
            if (mainUser->_employee.second == nullptr) {
                std::cout << "� ����� �������� �� �������� ��������." << std::endl;
                std::cout << "��� ����������� ������� ����� �������..." << std::endl;
                system("pause>nul");
                break;
            }
            employeeId = mainUser->_employee.first;
            employee = (*_bonusSystem).getEmployeeById(employeeId);

            std::cout << "���� ��������� -" << mainUser->_employee.second->getName()
                << "- <- " << mainUser->_login << std::endl;

            std::cout << "1. �������� � ������� � ����������" << std::endl;
            std::cout << "2. �������� � ��������" << std::endl;
            std::cout << "3. ���������� ��� ����������" << std::endl;
            std::cout << "4. ������� ������" << std::endl;
            std::cout << "5. <- ����� �� -" + mainUser->_login + "-" << std::endl;

            switch (check::getNaturalValueBefore(5, ">>> ", "�������� ����!")) {
            case 1:
                system("cls");
                std::cout << "���� ��������: " << employee->getSalary() << "$" << std::endl;
                std::cout << "���� �����: " << employee->getPoints() << "�. x " 
                    << (*_bonusSystem).getPointPrice() << "$" << std::endl;
                std::cout << "���� ��������: " << employee->getPercents() << "%" << std::endl;
                std::cout << "1. ������� ����������" << std::endl;
                std::cout << "2. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(2, ">>> ", "�������� ����!")) {
                case 1:
                    (*_bonusSystem).payBonuses(employeeId);
                    break;
                }
                break;
            case 2:
                system("cls");
                std::cout << *employee << std::endl;

                std::cout << "1. ����� ������" << std::endl;
                std::cout << "2. �������� ������ �����������" << std::endl;
                std::cout << "3. ����� ������" << std::endl;
                std::cout << "4. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                case 1:
                    if (!showTasks(sort, 1)) {
                        break;
                    }

                    taskId = check::getNaturalValue("������� ID ������ ��� ����������: ", "�������� ����!");

                    (*_bonusSystem).setTaskToEmployee(employeeId, taskId);
                    break;
                case 2:
                    std::cout << "������������� ������ ( - ) | ���������� ������ ( * ) | ����������� ������ ( + )" << std::endl;
                    std::cout << "�������� ����� ������ ������������� ������!" << std::endl;
                    taskId = check::getNaturalValue("������� ID ������ ������� ������ ��������: ", "�������� ����!");
                    employee->markTaskCompleted(taskId);
                    break;
                case 3:
                    std::cout << "1. ����� �� ����" << std::endl;
                    std::cout << "2. ����� �� ���������� ������" << std::endl;
                    std::cout << "3. ����� �� ���������� ���������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        taskId = check::getNaturalValue("������� ID ������� ������: ");
                        searchTask(taskId);
                        break;
                    case 2:
                        points = check::getNaturalValue("������� ���������� ������: ", "�������� ����!");
                        searchTask(points, sort);
                        break;
                    case 3:
                        percents = check::getDoubleValueFromTo(0, 100, "������� ���������� ���������: ", "�������� ����!");
                        searchTask(percents, sort);
                        break;
                    }
                    break;
                }
                break;
            case 3:
                std::cout << "1. �� �����������" << std::endl;
                std::cout << "2. �� ��������" << std::endl;
                std::cout << "3. <- �����" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                case 1:
                    sort = false;
                    break;
                case 2:
                    sort = true;
                    break;
                }
                break;
            case 4:
                userPassword = check::getPasswordValue("������� ������ ������ (���. "
                    + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                    " ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);
                newUserPassword = check::getPasswordValue("������� ����� ������ (���. "
                    + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                    " ��������): ", "�������� ����!", LoginSystem::PASSWORD_MIN_NUMBERS);
                if (mainUser->LogIn(mainUser->_login, userPassword)) {
                    (*_loginSystem).editUserPassword(mainUser->_login, newUserPassword);
                    std::cout << "������ ������� ������!" << std::endl;
                }
                else {
                    std::cout << "�������� ������ ������!" << std::endl;
                }
                break;
            case 5:
                return;
            }

            std::cout << "��� ����������� ������� ����� �������..." << std::endl;
            system("pause>nul");
        }
        break;
    }
}