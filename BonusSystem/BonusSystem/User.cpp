#include "User.h"

#include "LoginSystem.h"
#include "BonusSystem.h"
#include "checking.h"

#include <string>
#include <memory>
#include <exception>

User::User() { }

User::User(const User& copy) {
    _login = copy._login;
    _passwordHash = NULL;
    _employee = copy._employee;
}

User::User(std::string login, std::string password, Role role) {
    _role = role;
    _login = login;
    _passwordHash = std::hash<std::string>{ }(password);
    //_employee = nullptr;
}

bool User::operator< (const User& other) const {
    return _login < other._login;
}
bool User::operator> (const User& other) const {
    return _login < other._login;
}

bool User::LogIn(std::string login, std::string password) {
    if (login != _login) {
        return false;
    }
    if (_passwordHash != std::hash<std::string>{ }(password)) {
        return false;
    }
    return true;
}

bool User::showUsers(bool sort) {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::map<std::string, User> users;
    users = (*_loginSystem).getUsers();
    if (!users.empty()) {
        std::cout << "-<������������>-" << std::endl;
        if (!sort) {
            for (auto it = users.begin(); it != users.end(); it++) {
                std::cout << " - " << it->second._login;
                if (it->second._employee.second != nullptr) {
                    std::cout << " -> " << it->second._employee.second->getName();
                }
                std::cout << std::endl;
            }
        }
        else {
            for (auto it = users.rbegin(); it != users.rend(); it++) {
                std::cout << " - " << it->second._login;
                if (it->second._employee.second != nullptr) {
                    std::cout << " -> " << it->second._employee.second->getName();
                }
                std::cout << std::endl;
            }
        }
    }
    else {
        std::cout << "������������� ���." << std::endl;
        return false;
    }
    return true;
}

bool User::showEmployees(bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    if (!employees.empty()) {
        std::cout << "-<���������>-" << std::endl;
        if (!sort) {
            for (auto itE = employees.begin(); itE != employees.end(); itE++) {
                std::cout << itE->first << " - " << itE->second.getName() << std::endl;

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
        }
        else {
            for (auto itE = employees.rbegin(); itE != employees.rend(); itE++) {
                std::cout << itE->first << " - " << itE->second.getName() << std::endl;

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
    else {
        std::cout << "���������� ���." << std::endl;
        return false;
    }
    return true;
}

bool User::showTasks(bool sort, int taskType) {
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
        tasksByPoint = (*_bonusSystem).getTasksByPoint();
        tasksByPercent = (*_bonusSystem).getTasksByPercent();
        if (!tasksByPoint.empty() || !tasksByPercent.empty()) {
            std::cout << "-<��������� ������>-" << std::endl;
            if (!tasksByPoint.empty()) {
                std::cout << "-�� ������-" << std::endl;
                if (!sort) {
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
                if (!sort) {
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
                if (!sort) {
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
                if (!sort) {
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
                if (!sort) {
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
                if (!sort) {
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
}

bool User::showEmployeeTasks(bool sort, std::shared_ptr<Employee> employee) {
    std::map<int, std::shared_ptr<Task>> tasks;
    tasks = employee->getCurrentTasks();
    if (tasks.empty()) {
        std::cout << "� ��������� ��� �����." << std::endl;
        return false;
    }
    std::cout << "-<������������ ������ ���������>-" << std::endl;
    if (!sort) {
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

bool User::showEmployeeWithCompletedTask(bool sort) {
    bool flag = false;
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    std::cout << "-<��������� � ����������� ��������>-" << std::endl;
    if (!sort) {
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
        std::cout << "���������� � ������������ �������� ���." << std::endl;
    }
    return flag;
}

bool User::searchUser(std::string login) {
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

bool User::searchEmployee(int employeeId, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee> employees = (*_bonusSystem).getEmployees();
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

    if(!sort) {
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

bool User::searchTask(int)
{
    return false;
}

bool User::searchEmployee(std::string employeeName, bool sort) {
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::map<int, Employee> employees = (*_bonusSystem).getEmployees();
    std::map<int, std::shared_ptr<Task>> tasks;

    if (employees.empty()) {
        std::cout << "���������� ���." << std::endl;
        return false;
    }

    auto itE = employees.begin();
    itE =  std::find_if(employees.begin(), employees.end(),
        [&](std::pair<int, Employee> pair) -> bool {
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

            if (!sort) {
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

void User::Menu() {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::string userLogin, userPassword;
    std::string newUserLogin, newUserPassword;
    std::string employeeName, newEmployeeName;
    int employeeId, taskId, newTaskId;
    bool sort = true;
    std::shared_ptr<User> user;
    std::shared_ptr<Employee> employee;
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, TaskByPercent> tasksByPercent;

    std::string taskText;
    int points;
    double percents;

    try {
        switch (_role) {
        case User::Role::admin:
            while (true) {
                system("cls");
                std::cout << "����� ���� -" + _login + "-: " << std::endl;
                std::cout << "1. ��������/��������/������� ������������" << std::endl;
                std::cout << "2. ��������/��������/������� ���������" << std::endl;
                std::cout << "3. ��������/��������/������� ������" << std::endl;
                std::cout << "4. ��������/��������/������� ������ ���������" << std::endl;
                std::cout << "5. �������� ������ �����������" << std::endl;
                std::cout << "6. ���������� ���� �����" << std::endl;
                std::cout << "7. ��������� ������" << std::endl;
                std::cout << "8. ���������� ��� ����������" << std::endl;
                std::cout << "9. �����" << std::endl;
                std::cout << "10. <- ����� �� -" + _login + "-" << std::endl;

                // ��������� ������
                // - ��������� ����
                // - ��������� ������
                // ��������� ����������� �������� ��� �����
                // Employee - $

                // ���������� ���� �����

                switch (check::getNaturalValueBefore(10, ">>> ", "�������� ����!")) {
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

                        (*_loginSystem).addUser(userLogin, userPassword, Role::common);

                        employeeName = check::getProperNameValue("������� ��� ���������: ");
                        employeeId = (*_bonusSystem).addEmployee(employeeName);

                        (*_loginSystem).setEmployeeToUser(_bonusSystem, userLogin, employeeId);
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
                        std::cout << "3. �������� ���������" << std::endl;
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
                            std::cout << "1. �������� ��� ���������" << std::endl;
                            std::cout << "2. ��������� ������� ���������" << std::endl;
                            std::cout << "3. <- �����" << std::endl;

                            switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                            case 1:
                                employee = (*_loginSystem).getUserByLogin(userLogin)->_employee.second;
                                if (employee == nullptr) {
                                    std::cout << "� ������������ �� �������� ��������." << std::endl;
                                    break;
                                }
                                newEmployeeName = check::getProperNameValue("������� ����� ��� ���������: ");
                                employee->setName(newEmployeeName);
                                break;
                            case 2:
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
                        (*_bonusSystem).addEmployee(check::getProperNameValue("������� ��� ���������: "));
                        break;
                    case 2:
                        if (!showEmployees(sort)) {
                            break;
                        }

                        employeeId = check::getNaturalValue("������� ID ��������� ��� ���������: ");
                        newEmployeeName = check::getProperNameValue("������� ����� ��� ���������: ");
                        (*_bonusSystem).editEmployee(employeeId, newEmployeeName);
                        break;
                    case 3:
                        if (!showEmployees(sort)) {
                            break;
                        }

                        employeeId = check::getNaturalValue("������� ID ��������� ��� ��������: ");
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
                    std::cout << "4. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        std::cout << "������� ����� ������� (Enter ��� ����� �����): ";
                        std::getline(std::cin, taskText, '\n');

                        std::cout << "1. �������� ������ �� �����" << std::endl;
                        std::cout << "2. �������� ������ �� ������� �� �/�" << std::endl;
                        std::cout << "3. <- �����" << std::endl;

                        switch (check::getNaturalValueBefore(3, ">>> ", "�������� ����!")) {
                        case 1:
                            points = check::getNaturalValue("������� ���������� ������: ", "�������� ����!");
                            (*_bonusSystem).createTaskByPoint(taskText, points);
                            break;
                        case 2:
                            percents = check::getDoubleValueFromTo(0, 100, "������� ���������� ���������: ", "�������� ����!");
                            (*_bonusSystem).createTaskByPercent(taskText, percents);
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
                            tasksByPoint = (*_bonusSystem).getTasksByPoint();
                            if (tasksByPoint.empty()) {
                                std::cout << "����� �� ����� ���." << std::endl;
                                break;
                            }
                            
                            taskId = check::getNaturalValue("������� ID ������ �� ������ ��� ���������: ", "�������� ����!");
                            points = check::getNaturalValue("������� ����� ���������� ������: ", "�������� ����!");

                            (*_bonusSystem).editTask(taskId, points);
                            break;
                        case 3:
                            tasksByPercent = (*_bonusSystem).getTasksByPercent();
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
                        tasksByPoint = (*_bonusSystem).getTasksByPoint();
                        tasksByPercent = (*_bonusSystem).getTasksByPercent();
                        if (tasksByPoint.empty() && tasksByPercent.empty()) {
                            std::cout << "����� ���." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ ��� ��������: ", "�������� ����!");
                        (*_bonusSystem).deleteTask(taskId);
                        break;
                    }
                    break;
                case 4:
                    system("cls");

                    if (!showEmployees(sort)) {
                        break;
                    }

                    std::cout << "1. �������� ������ ���������" << std::endl;
                    std::cout << "2. �������� ������ ���������" << std::endl;
                    std::cout << "3. ������� ������ ���������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        if (!showTasks(sort, 1)) {
                            break;
                        }

                        showEmployees(sort);
                        
                        taskId = check::getNaturalValue("������� ID ������ ��� ����������: ", "�������� ����!");

                        employeeId = check::getNaturalValue("������� ID ��������� �������� �������� ������: ");

                        (*_bonusSystem).setTaskToEmployee(employeeId, taskId);
                        break;
                    case 2:
                        showEmployees(sort);

                        employeeId = check::getNaturalValue("������� ID ��������� �������� �������� ������: ");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "��������� � ����� ID �� ����������" << std::endl;
                            break;
                        }

                        if (!showEmployeeTasks(sort, employee) || !showTasks(sort, 1)) {
                            std::cout << "� ��������� ��� ����� ��� ��������� ��� ��� ��������� �����." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ ��������� ������� ������ ��������: ", "�������� ����!");
                        
                        newTaskId = check::getNaturalValue("������� ID ����� ������ �� ���������: ", "�������� ����!");

                        (*_bonusSystem).editTaskFromEmployee(employeeId, taskId, newTaskId);
                        break;
                    case 3:
                        showEmployees(sort);

                        employeeId = check::getNaturalValue("������� ID ��������� �������� ������� ������: ");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "��������� � ����� ID �� ����������" << std::endl;
                            break;
                        }

                        if (!showEmployeeTasks(sort, employee)) {
                            std::cout << "� ��������� ��� ����� ��� ��������." << std::endl;
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ ��� ��������: ", "�������� ����!");

                        (*_bonusSystem).deleteTaskFromEmployee(employeeId, taskId);
                        break;
                    }
                    break;
                case 5:
                    system("cls");

                    if (!showEmployees(sort)) {
                        break;
                    }

                    std::cout << "1. �������� ������ ����������� � ���������" << std::endl;
                    std::cout << "2. ���������� ���������� ������������ � ���������� � �������� ������������ ���������" << std::endl;
                    std::cout << "3. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        employeeId = check::getNaturalValue("������� ID ��������� �������� �������� ������: ");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "��������� � ����� ID �� ����������" << std::endl;
                            break;
                        }
                        
                        if (!showEmployeeTasks(sort, employee)) {
                            break;
                        }

                        taskId = check::getNaturalValue("������� ID ������ ������� ������ ��������: ", "�������� ����!");
                        employee->markTaskCompleted(taskId);
                        break;
                    case 2:
                        if (!showEmployeeWithCompletedTask(sort)) {
                            break;
                        }

                        employeeId = check::getNaturalValue("������� ID ��������� �������� ��������� ������: ");
                        employee = (*_bonusSystem).getEmployeeById(employeeId);
                        if (employee == nullptr) {
                            std::cout << "��������� � ����� ID �� ����������" << std::endl;
                            break;
                        }
                        taskId = check::getNaturalValue("������� ID ������ ������� ������ ���������: ", "�������� ����!");
                        (*_bonusSystem).markTaskCompleted(taskId);
                        break;
                    }
                    break;
                case 8:
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
                case 9:
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
                        switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
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
                        /*searchTask(points);
                        searchTask(percents);*/
                        break;
                    }
                    break;
                case 10:
                    return;
                }
                std::cout << "��� ����������� ������� ����� �������..." << std::endl;
                system("pause>nul");
            }
            break;
        case User::Role::common:
            if (_employee.second == nullptr) {
                std::cout << "� ����� �������� �� �������� ��������." << std::endl;
                std::cout << "��� ����������� ������� ����� �������..." << std::endl;
                system("pause>nul");
                break;
            }
            std::cout << "���� ��������� -" << _employee.second->getName() << "- <- " << _login << std::endl;

            // ����� ������
            // �������� ������������
            // ������������� �����, ������
            // ����� �������
            // ��� ����������
            // ����������� ����� � ��������
            // �������
            std::cout << "Just user\n";

            std::cout << "��� ����������� ������� ����� �������..." << std::endl;
            system("pause>nul");
            break;
        }
    }
    catch (std::exception ex) {
        std::cout << ex.what();
    }
}