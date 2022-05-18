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
        if (check::getCharValueFromString("yn", "пересоздать базу данных? Все данные будут потеряны! (y/n)\n>>> ",
            "Неверный ввод!") == 'y') {
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
		std::cout << "1. Вход" << std::endl;
		std::cout << "2. Информация" << std::endl;
		std::cout << "3. Сброс базы данных" << std::endl;
		std::cout << "4. Выход" << std::endl;
		switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
		case 1:
			login = check::getWordValue("Введите логин: ", "Неверный ввод!");
			password = check::getPasswordValue("Введите пароль (мин. " 
				+ std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
				" символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);
			user = (*loginSystem).LogIn(login, password);
			if (user != nullptr) {
				userMenu(user);
			}
            else {
                std::cout << "Неправильный логин или пароль!" << std::endl;
            }
			user = nullptr;
			break;
		case 2:
			std::cout << "Это консольное приложение \033[33m\"Система расчёта премиальных"
				<< " по результатам года\"\033[0m\nбыло разработано студентом "
				<< "\033[36mгр. 024402 \033[35mБеляцким Е.В.\033[0m, 2022 г." << std::endl;
			break;
        case 3:
            if (check::getCharValueFromString("yn", "Вы уверены, что хотите это сделать? Все данные будут потеряны! (y/n)\n>>> ",
                "Неверный ввод!") == 'y') {
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
        std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
        system("pause>nul");
	}
}

bool Menu::showUsers(bool sort) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::map<std::string, User> users;
    users = (*_loginSystem).getUsers();
    if (users.empty()) {
        std::cout << "Пользователей нет." << std::endl;
        return false;
    }
    std::cout << "-<Пользователи>-" << std::endl;
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
        std::cout << "Работников нет." << std::endl;
        return false;
    }

    std::cout << "-<Работники>-" << std::endl;
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
            std::cout << "-<Свободные задачи>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-По баллам-" << std::endl;
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
                std::cout << "-По процентам-" << std::endl;
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
            std::cout << "-<Взятые задачи>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-По баллам-" << std::endl;
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
                std::cout << "-По процентам-" << std::endl;
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
            std::cout << "-<Выполненные задачи>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-По баллам-" << std::endl;
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
                std::cout << "-По процентам-" << std::endl;
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
            std::cout << "Задач нет." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 1) {
        if (flag1 == 0) {
            std::cout << "Свободных задач нет." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 2) {
        if (flag2 == 0) {
            std::cout << "Помеченных задач нет." << std::endl;
            return false;
        }
        return true;
    }
    else if (taskType == 3) {
        if (flag3 == 0) {
            std::cout << "Сделанных задач нет." << std::endl;
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
        std::cout << "У работника нет задач." << std::endl;
        return false;
    }
    std::cout << "-<Непомеченные задачи работника>-" << std::endl;
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

    std::cout << "-<Работники с помеченными задачами>-" << std::endl;
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
        std::cout << "Работников с помеченными задачами нет." << std::endl;
    }
    return flag;
}

bool Menu::searchUser(std::string login) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    auto users = (*_loginSystem).getUsers();
    if (users.empty()) {
        std::cout << "Пользователей нет." << std::endl;
        return false;
    }
    auto it = users.find(login);
    if (it == users.end()) {
        std::cout << "Пользователь не найден." << std::endl;
        return false;
    }
    std::cout << "-<Найден пользователь>-" << std::endl;
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
        std::cout << "Работников нет." << std::endl;
        return false;
    }

    auto itE = employees.find(employeeId);

    if (itE == employees.end()) {
        std::cout << "Работник не найден." << std::endl;
        return false;
    }

    std::cout << "-<Работник по ID>-" << std::endl;

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
        std::cout << "Работников нет." << std::endl;
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
        std::cout << "Работники не найден." << std::endl;
        return false;
    }

    std::cout << "-<Работник по ID>-" << std::endl;

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
        std::cout << "-<Задача по ID>-" << std::endl;
        std::cout << itTskByPnt->first << " - " << itTskByPnt->second << std::endl;
        return true;
    }
    auto itTskByPct = tasksByPercent.find(taskId);
    if (itTskByPct != tasksByPercent.end()) {
        std::cout << "-<Задача по ID>-" << std::endl;
        std::cout << itTskByPct->first << " - " << itTskByPct->second << std::endl;
        return true;
    }
    std::cout << "Задача не найдена." << std::endl;
    return false;
}

bool Menu::searchTask(int points, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    auto tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
    if (tasksByPoint.empty()) {
        std::cout << "Задач по баллам нет." << std::endl;
    }
    auto itTskByPnt = std::find_if(tasksByPoint.begin(), tasksByPoint.end(),
        [&](std::pair<int, TaskByPoint> pair) -> bool {
            if (pair.second.getPoints() == points) {
                return true;
            }
            return false;
        });
    if (itTskByPnt == tasksByPoint.end()) {
        std::cout << "Задачи по баллам не найдено." << std::endl;
        return false;
    }

    std::cout << "-<Задачи по баллам>-" << std::endl;
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
        std::cout << "Задач по процентам нет." << std::endl;
    }
    auto itTskByPct = std::find_if(tasksByPercent.begin(), tasksByPercent.end(),
        [&](std::pair<int, TaskByPercent> pair) -> bool {
            if (pair.second.getPercent() == percent) {
                return true;
            }
            return false;
        });
    if (itTskByPct == tasksByPercent.end()) {
        std::cout << "Задачи по баллам не найдено." << std::endl;
        return false;
    }

    std::cout << "-<Задачи по баллам>-" << std::endl;
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
            std::cout << "Админ меню -" + mainUser->_login + "-: " << std::endl;
            std::cout << "1. Взаимодействия с пользователями" << std::endl;
            std::cout << "2. Взаимодействие с работниками" << std::endl;
            std::cout << "3. Взаимодействие с задачами" << std::endl;
            std::cout << "4. Взаимодействие с ценой балла" << std::endl;
            std::cout << "5. Выплатить премии" << std::endl;
            std::cout << "6. Установить тип сортировки" << std::endl;
            std::cout << "7. Поиск" << std::endl;
            std::cout << "8. <- Выйти из -" + mainUser->_login + "-" << std::endl;

            switch (check::getNaturalValueBefore(8, ">>> ", "Неверный ввод!")) {
            case 1:
                system("cls");

                showUsers(sort);

                std::cout << "1. Добавить пользователя" << std::endl;
                std::cout << "2. Изменить пользователя" << std::endl;
                std::cout << "3. Удалить пользователя" << std::endl;
                std::cout << "4. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                case 1:
                    userLogin = check::getWordValue("Введите логин: ", "Неверный ввод!");
                    userPassword = check::getPasswordValue("Введите пароль (мин. "
                        + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                        " символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);

                    (*_loginSystem).addUser(userLogin, userPassword, User::Role::common);
                    break;
                case 2:
                    if (!showUsers(sort)) {
                        break;
                    }

                    userLogin = check::getWordValue("Введите логин изменяемого пользователя: ", "Неверный ввод!");
                    user = (*_loginSystem).getUserByLogin(userLogin);
                    if (user == nullptr) {
                        std::cout << "Пользователя с данным логином не существует!" << std::endl;
                        break;
                    }

                    std::cout << "1. Изменить логин" << std::endl;
                    std::cout << "2. Изменить пароль" << std::endl;
                    std::cout << "3. Назначить работника" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        newUserLogin = check::getWordValue("Введите новый логин: ", "Неверный ввод!");

                        (*_loginSystem).editUserLogin(userLogin, newUserLogin);
                        break;
                    case 2:
                        newUserPassword = check::getPasswordValue("Введите новый пароль (мин. "
                            + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                            " символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);

                        (*_loginSystem).editUserPassword(userLogin, newUserPassword);
                        break;
                    case 3:
                        if (!showEmployees(sort)) {
                            break;
                        }

                        employeeId = check::getNaturalValue("Введите ID нового работника: ", "Неверный ввод!");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "Работника с таким ID не существует" << std::endl;
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

                    userLogin = check::getWordValue("Введите логин для удаления: ", "Неверный ввод!");

                    (*_loginSystem).deleteUser(userLogin);
                    break;
                }
                break;
            case 2:
                system("cls");

                showEmployees(sort);

                std::cout << "1. Добавить работника" << std::endl;
                std::cout << "2. Изменить работника" << std::endl;
                std::cout << "3. Удалить работника" << std::endl;
                std::cout << "4. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                case 1:
                    employeeName = check::getProperNameValue("Введите имя работника: ", "Неверный ввод");
                    salary = check::getDoubleValue("Введите зарплату работника: ", "Неверный ввод");
                    (*_bonusSystem).addEmployee(employeeName, salary);
                    break;
                case 2:
                    if (!showEmployees(sort)) {
                        break;
                    }

                    employeeId = check::getNaturalValue("Введите ID работника для изменения: ", "Неверный ввод");

                    std::cout << "1. Изменить имя" << std::endl;
                    std::cout << "2. Изменить зарплату" << std::endl;
                    std::cout << "3. Изменить задачи" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        newEmployeeName = check::getProperNameValue("Введите новое имя работника: ", "Неверный ввод");
                        (*_bonusSystem).editEmployee(employeeId, newEmployeeName);
                        break;
                    case 2:
                        salary = check::getDoubleValue("Введите новую зарплату работника: ", "Неверный ввод");
                        (*_bonusSystem).editEmployee(employeeId, salary);
                        break;
                    case 3:
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        std::cout << *employee << std::endl;

                        std::cout << "1. Добавить задачу" << std::endl;
                        std::cout << "2. Пометить задачу выполненной" << std::endl;
                        std::cout << "3. Удалить задачу" << std::endl;
                        std::cout << "4. <- Назад" << std::endl;

                        switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                        case 1:
                            if (!showTasks(sort, 1)) {
                                break;
                            }

                            taskId = check::getNaturalValue("Введите ID задачи для добавления: ", "Неверный ввод!");

                            (*_bonusSystem).setTaskToEmployee(employeeId, taskId);
                            break;
                        case 2:
                            std::cout << "Невыполненные задачи ( - ) | Помеченные задачи ( * ) | Выполненные задачи ( + )" << std::endl;
                            std::cout << "Помечать можно только невыполненные задачи!" << std::endl;
                            taskId = check::getNaturalValue("Введите ID задачи которую хотите пометить: ", "Неверный ввод!");
                            employee->markTaskCompleted(taskId);
                            break;
                        case 3:
                            std::cout << "Удалить можно только свободную задачу!" << std::endl;
                            taskId = check::getNaturalValue("Введите ID задачи для удаления: ", "Неверный ввод!");

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

                    employeeId = check::getNaturalValue("Введите ID работника для удаления: ", "Неверный ввод");
                    (*_bonusSystem).deleteEmployee(employeeId);
                    (*_loginSystem).deleteEmployeeOnUsers(employeeId);
                    break;
                }
                break;
            case 3:
                system("cls");

                showTasks(sort);

                std::cout << "1. Добавить задачу" << std::endl;
                std::cout << "2. Изменить задачу" << std::endl;
                std::cout << "3. Удалить задачу" << std::endl;
                std::cout << "4. Подтвердить выполнение задачи" << std::endl;
                std::cout << "5. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(5, ">>> ", "Неверный ввод!")) {
                case 1:
                    std::cout << "Введите текст задания (Enter для конца ввода): ";
                    std::getline(std::cin, taskText, '\n');

                    std::cout << "1. Добавить задачу за баллы" << std::endl;
                    std::cout << "2. Добавить задачу за процент от з/п" << std::endl;
                    std::cout << "3. <- Назад" << std::endl;

                    switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                    case 1:
                        points = check::getNaturalValue("Введите количество баллов: ", "Неверный ввод!");
                        (*_bonusSystem).addTaskByPoint(taskText, points);
                        break;
                    case 2:
                        percents = check::getDoubleValueFromTo(0, 100, "Введите количество процентов: ", "Неверный ввод!");
                        (*_bonusSystem).addTaskByPercent(taskText, percents);
                        break;
                    }
                    break;
                case 2:
                    std::cout << "Изменить можно только свободные задачи!" << std::endl;
                    if (!showTasks(sort, 1)) {
                        break;
                    }

                    std::cout << "1. Изменить текст задачи" << std::endl;
                    std::cout << "2. Изменить баллы задачи" << std::endl;
                    std::cout << "3. Изменить проценты задачи" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        taskId = check::getNaturalValue("Введите ID задачи для изменения: ", "Неверный ввод!");
                        std::cout << "Введите новый текст задания (Enter для конца ввода): ";
                        std::getline(std::cin, taskText, '\n');

                        (*_bonusSystem).editTask(taskId, taskText);
                        break;
                    case 2:
                        tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
                        if (tasksByPoint.empty()) {
                            std::cout << "Задач за баллы нет." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("Введите ID задачи по баллам для изменения: ", "Неверный ввод!");
                        points = check::getNaturalValue("Введите новое количество баллов: ", "Неверный ввод!");

                        (*_bonusSystem).editTask(taskId, points);
                        break;
                    case 3:
                        tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
                        if (tasksByPercent.empty()) {
                            std::cout << "Задач за проценты нет." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("Введите ID задачи по процентам для изменения: ", "Неверный ввод!");
                        percents = check::getDoubleValueFromTo(0, 100, "Введите новое количество процентов: ", "Неверный ввод!");

                        (*_bonusSystem).editTask(taskId, percents);
                        break;
                    }
                    break;
                case 3:
                    tasksByPoint = (*_bonusSystem).getFreeTasksByPoint();
                    tasksByPercent = (*_bonusSystem).getFreeTasksByPercent();
                    if (tasksByPoint.empty() && tasksByPercent.empty()) {
                        std::cout << "Задач нет." << std::endl;
                        break;
                    }

                    taskId = check::getNaturalValue("Введите ID задачи для удаления: ", "Неверный ввод!");
                    (*_bonusSystem).deleteTask(taskId);
                    break;
                case 4:
                    if (!showEmployeeWithMarkedTask(sort)) {
                        break;
                    }

                    employeeId = check::getNaturalValue("Введите ID работника которому выполнить задачу: ");
                    employee = (*_bonusSystem).getEmployeeById(employeeId);
                    if (employee == nullptr) {
                        std::cout << "Работника с таким ID не существует" << std::endl;
                        break;
                    }
                    taskId = check::getNaturalValue("Введите ID задачи которую хотите выполнить: ", "Неверный ввод!");
                    (*_bonusSystem).setTaskCompleted(taskId);

                    break;
                }
                break;
            case 4:
                std::cout << "Текущая цена балла: 1б. = " << (*_bonusSystem).getPointPrice() << "$" << std::endl;

                std::cout << "1. Установить новую цену балла" << std::endl;
                std::cout << "2. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(2, ">>> ", "Неверный ввод!")) {
                case 1:
                    (*_bonusSystem).setPointPrice(check::getDoubleValueFromTo(0, 100, "Введите количество $ за балл: ", "Неверный ввод!"));
                    break;
                }
                break;
            case 5:
                if (!showEmployees(sort)) {
                    break;
                }

                std::cout << "1. Выплатить одному" << std::endl;
                std::cout << "2. Выплатить всем" << std::endl;
                std::cout << "3. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                case 1:
                    employeeId = check::getNaturalValue("Введите ID работника для выплаты премии: ", "Неверный ввод");
                    (*_bonusSystem).payBonuses(employeeId);
                    break;
                case 2:
                    (*_bonusSystem).payBonuses();
                    break;
                }
                break;
            case 6:
                std::cout << "1. По возрастанию" << std::endl;
                std::cout << "2. По убыванию" << std::endl;
                std::cout << "3. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                case 1:
                    sort = false;
                    break;
                case 2:
                    sort = true;
                    break;
                }
                break;
            case 7:
                std::cout << "1. Поиск пользователя" << std::endl;
                std::cout << "2. Поиск работника" << std::endl;
                std::cout << "3. Поиск задачи" << std::endl;
                std::cout << "4. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                case 1:
                    userLogin = check::getWordValue("Введите логин: ", "Неверный ввод!");
                    searchUser(userLogin);
                    break;
                case 2:
                    std::cout << "1. Поиск по айди" << std::endl;
                    std::cout << "2. Поиск по имени" << std::endl;
                    std::cout << "3. <- Назад" << std::endl;
                    switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                    case 1:
                        employeeId = check::getNaturalValue("Введите ID искомого работника: ");
                        searchEmployee(employeeId, sort);
                        break;
                    case 2:
                        employeeName = check::getProperNameValue("Введите имя искомого работника: ", "Неверный ввод!");
                        searchEmployee(employeeName, sort);
                        break;
                    }
                    break;
                case 3:
                    std::cout << "1. Поиск по айди" << std::endl;
                    std::cout << "2. Поиск по количеству баллов" << std::endl;
                    std::cout << "3. Поиск по количеству процентов" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        taskId = check::getNaturalValue("Введите ID искомой задачи: ");
                        searchTask(taskId);
                        break;
                    case 2:
                        points = check::getNaturalValue("Введите количество баллов: ", "Неверный ввод!");
                        searchTask(points, sort);
                        break;
                    case 3:
                        percents = check::getDoubleValueFromTo(0, 100, "Введите количество процентов: ", "Неверный ввод!");
                        searchTask(percents, sort);
                        break;
                    }
                    break;
                }
                break;
            case 8:
                return;
            }
            std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
            system("pause>nul");
        }
        break;
    case User::Role::common:
        while (true) {
            system("cls");
            if (mainUser->_employee.second == nullptr) {
                std::cout << "К этому аккаунту не привязан работник." << std::endl;
                std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
                system("pause>nul");
                break;
            }
            employeeId = mainUser->_employee.first;
            employee = (*_bonusSystem).getEmployeeById(employeeId);

            std::cout << "Меню работника -" << mainUser->_employee.second->getName()
                << "- <- " << mainUser->_login << std::endl;

            std::cout << "1. Действия с баллами и процентами" << std::endl;
            std::cout << "2. Действия с задачами" << std::endl;
            std::cout << "3. Установить тип сортировки" << std::endl;
            std::cout << "4. Сменить пароль" << std::endl;
            std::cout << "5. <- Выйти из -" + mainUser->_login + "-" << std::endl;

            switch (check::getNaturalValueBefore(5, ">>> ", "Неверный ввод!")) {
            case 1:
                system("cls");
                std::cout << "Ваша зарплата: " << employee->getSalary() << "$" << std::endl;
                std::cout << "Ваши баллы: " << employee->getPoints() << "б. x " 
                    << (*_bonusSystem).getPointPrice() << "$" << std::endl;
                std::cout << "Ваши проценты: " << employee->getPercents() << "%" << std::endl;
                std::cout << "1. Вывести премильные" << std::endl;
                std::cout << "2. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(2, ">>> ", "Неверный ввод!")) {
                case 1:
                    (*_bonusSystem).payBonuses(employeeId);
                    break;
                }
                break;
            case 2:
                system("cls");
                std::cout << *employee << std::endl;

                std::cout << "1. Взять задачу" << std::endl;
                std::cout << "2. Пометить задачу выполненной" << std::endl;
                std::cout << "3. Поиск задачи" << std::endl;
                std::cout << "4. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                case 1:
                    if (!showTasks(sort, 1)) {
                        break;
                    }

                    taskId = check::getNaturalValue("Введите ID задачи для добавления: ", "Неверный ввод!");

                    (*_bonusSystem).setTaskToEmployee(employeeId, taskId);
                    break;
                case 2:
                    std::cout << "Невыполненные задачи ( - ) | Помеченные задачи ( * ) | Выполненные задачи ( + )" << std::endl;
                    std::cout << "Помечать можно только невыполненные задачи!" << std::endl;
                    taskId = check::getNaturalValue("Введите ID задачи которую хотите пометить: ", "Неверный ввод!");
                    employee->markTaskCompleted(taskId);
                    break;
                case 3:
                    std::cout << "1. Поиск по айди" << std::endl;
                    std::cout << "2. Поиск по количеству баллов" << std::endl;
                    std::cout << "3. Поиск по количеству процентов" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;
                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        taskId = check::getNaturalValue("Введите ID искомой задачи: ");
                        searchTask(taskId);
                        break;
                    case 2:
                        points = check::getNaturalValue("Введите количество баллов: ", "Неверный ввод!");
                        searchTask(points, sort);
                        break;
                    case 3:
                        percents = check::getDoubleValueFromTo(0, 100, "Введите количество процентов: ", "Неверный ввод!");
                        searchTask(percents, sort);
                        break;
                    }
                    break;
                }
                break;
            case 3:
                std::cout << "1. По возрастанию" << std::endl;
                std::cout << "2. По убыванию" << std::endl;
                std::cout << "3. <- Назад" << std::endl;

                switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                case 1:
                    sort = false;
                    break;
                case 2:
                    sort = true;
                    break;
                }
                break;
            case 4:
                userPassword = check::getPasswordValue("Введите старый пароль (мин. "
                    + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                    " символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);
                newUserPassword = check::getPasswordValue("Введите новый пароль (мин. "
                    + std::to_string(LoginSystem::PASSWORD_MIN_NUMBERS) +
                    " символов): ", "Неверный ввод!", LoginSystem::PASSWORD_MIN_NUMBERS);
                if (mainUser->LogIn(mainUser->_login, userPassword)) {
                    (*_loginSystem).editUserPassword(mainUser->_login, newUserPassword);
                    std::cout << "Пароль успешно изменён!" << std::endl;
                }
                else {
                    std::cout << "Неверный старый пароль!" << std::endl;
                }
                break;
            case 5:
                return;
            }

            std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
            system("pause>nul");
        }
        break;
    }
}