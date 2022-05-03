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

void User::Menu() {
    std::shared_ptr<LoginSystem> _loginSystem = LoginSystem::getInstance();
    std::shared_ptr<BonusSystem> _bonusSystem = BonusSystem::getInstance();
    std::string userLogin, userPassword;
    std::string newUserLogin, newUserPassword;
    std::string employeeName, newEmployeeName;
    int employeeId;
    int taskId;
    std::vector<User> users;
    std::map<int, Employee> employees;
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
                std::cout << "6. �������� �������������" << std::endl;
                std::cout << "7. �������� ����������" << std::endl;
                std::cout << "8. �������� ������" << std::endl;
                std::cout << "9. <- �����" << std::endl;

         
                // ��������� ��������� ������
                // �� � "���������" � �������� �����������
                // ��� ����� ������������ � ������ ��� ������� 5 (�� ������� ����� ����� ������� ����)
                // ���� ����� ����� ��� ��� "���������" �� �������� � ����������� �
                // ��������� ����������� �������� ��� �����

                // ��������� ������ �������� ����� ��� ����� ������ �� �����

                // ���������� ���� �����

                switch (check::getNaturalValueBefore(9, ">>> ", "�������� ����!")) {
                case 1:
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
                        std::cout << "-<������������>-" << std::endl;
                        users = (*_loginSystem).getUsers();
                        for (User user : users) {
                            std::cout << " - " << user._login;
                            if (user._employee.second != nullptr) {
                                std::cout << " -> " << user._employee.second->getName();
                            }
                            std::cout << std::endl;
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
                                newEmployeeName = check::getProperNameValue("������� ����� ��� ���������: ");
                                (*_loginSystem).getUserByLogin(userLogin)->_employee.second->setName(newEmployeeName);
                                break;
                            case 2:
                                std::cout << "-<���������>-" << std::endl;
                                employees = (*_bonusSystem).getEmployees();
                                for (std::pair<int, Employee> employee : employees) {
                                    std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                                }

                                employeeId = check::getNaturalValue("������� ID ������ ���������: ", "�������� ����!");
                                employee = (*_bonusSystem).getEmployeeById(employeeId);
                                while (employee == nullptr) {
                                    std::cout << "������ ID ���" << std::endl;
                                    employeeId = check::getNaturalValue("������� ID ������ ���������: ", "�������� ����!");
                                    employee = (*_bonusSystem).getEmployeeById(employeeId);
                                }
                                (*_loginSystem).setEmployeeToUser(_bonusSystem, userLogin, employeeId);
                                break;
                            }
                            break;
                        }
                        break;
                    case 3:
                        std::cout << "-<������������>-" << std::endl;
                        users = (*_loginSystem).getUsers();
                        for (User user : users) {
                            std::cout << " - " << user._login;
                            if (user._employee.second != nullptr) {
                                std::cout << " -> " << user._employee.second->getName();
                            }
                            std::cout << std::endl;
                        }

                        userLogin = check::getWordValue("������� ����� ��� ��������: ", "�������� ����!");

                        (*_loginSystem).deleteUser(userLogin);
                        break;
                    }
                    break;
                case 2:
                    std::cout << "1. �������� ���������" << std::endl;
                    std::cout << "2. �������� ���������" << std::endl;
                    std::cout << "3. ������� ���������" << std::endl;
                    std::cout << "4. <- �����" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                    case 1:
                        (*_bonusSystem).addEmployee(check::getProperNameValue("������� ��� ���������: "));
                        break;
                    case 2:
                        std::cout << "-<���������>-" << std::endl;
                        employees = (*_bonusSystem).getEmployees();
                        for (std::pair<int, Employee> employee : employees) {
                            std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                        }

                        employeeId = check::getNaturalValue("������� ID ��������� ��� ���������: ");
                        newEmployeeName = check::getProperNameValue("������� ����� ��� ���������: ");
                        (*_bonusSystem).editEmployee(employeeId, newEmployeeName);
                        break;
                    case 3:
                        std::cout << "-<���������>-" << std::endl;
                        employees = (*_bonusSystem).getEmployees();
                        for (std::pair<int, Employee> employee : employees) {
                            std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                        }

                        employeeId = check::getNaturalValue("������� ID ��������� ��� ��������: ");
                        (*_bonusSystem).deleteEmployee(employeeId);
                        (*_loginSystem).deleteEmployeeOnUsers(employeeId);
                        break;
                    }
                    break;
                case 3:
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
                        std::cout << "1. �������� ����� ������" << std::endl;
                        std::cout << "2. �������� ����� ������" << std::endl;
                        std::cout << "3. �������� �������� ������" << std::endl;
                        std::cout << "4. <- �����" << std::endl;

                        switch (check::getNaturalValueBefore(4, ">>> ", "�������� ����!")) {
                        case 1:
                            std::cout << "-<������>-" << std::endl;
                            std::cout << "-�� ������-" << std::endl;
                            tasksByPoint = (*_bonusSystem).getTasksByPoint();
                            for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                            }
                            std::cout << "-�� ���������-" << std::endl;
                            tasksByPercent = (*_bonusSystem).getTasksByPercent();
                            for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                            }

                            taskId = check::getNaturalValue("������� ID ������ ��� ���������: ", "�������� ����!");
                            std::cout << "������� ����� ����� ������� (Enter ��� ����� �����): ";
                            std::getline(std::cin, taskText, '\n');

                            (*_bonusSystem).editTask(taskId, taskText);
                            break;
                        case 2:
                            std::cout << "-<������>-" << std::endl;
                            std::cout << "-�� ������-" << std::endl;
                            tasksByPoint = (*_bonusSystem).getTasksByPoint();
                            for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                            }

                            taskId = check::getNaturalValue("������� ID ������ ��� ���������: ", "�������� ����!");
                            points = check::getNaturalValue("������� ����� ���������� ������: ", "�������� ����!");

                            (*_bonusSystem).editTask(taskId, points);
                            break;
                        case 3:
                            std::cout << "-<������>-" << std::endl;
                            std::cout << "-�� ���������-" << std::endl;
                            tasksByPercent = (*_bonusSystem).getTasksByPercent();
                            for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                            }

                            taskId = check::getNaturalValue("������� ID ������ ��� ���������: ", "�������� ����!");
                            percents = check::getDoubleValueFromTo(0, 100, "������� ����� ���������� ���������: ", "�������� ����!");

                            (*_bonusSystem).editTask(taskId, percents);
                            break;
                        }
                        break;
                    case 3:
                        std::cout << "-<������>-" << std::endl;
                        std::cout << "-�� ������-" << std::endl;
                        tasksByPoint = (*_bonusSystem).getTasksByPoint();
                        for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                            std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                        }
                        std::cout << "-�� ���������-" << std::endl;
                        tasksByPercent = (*_bonusSystem).getTasksByPercent();
                        for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                            std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                        }

                        taskId = check::getNaturalValue("������� ID ������ ��� ��������: ", "�������� ����!");
                        (*_bonusSystem).deleteTask(taskId);
                        break;
                    }
                    break;
                case 6:
                    std::cout << "-<������������>-" << std::endl;
                    users = (*_loginSystem).getUsers();
                    for (User user : users) {
                        std::cout << " - " << user._login;
                        if (user._employee.second != nullptr) {
                            std::cout << " -> " << user._employee.second->getName();
                        }
                        std::cout << std::endl;
                    }
                    break;
                case 7:
                    std::cout << "-<���������>-" << std::endl;
                    employees = (*_bonusSystem).getEmployees();
                    for (std::pair<int, Employee> employee : employees) {
                        std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                    }
                    break;
                case 8:
                    std::cout << "-<������>-" << std::endl;
                    std::cout << "-�� ������-" << std::endl;
                    tasksByPoint = (*_bonusSystem).getTasksByPoint();
                    for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                        std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                    }
                    std::cout << "-�� ���������-" << std::endl;
                    tasksByPercent = (*_bonusSystem).getTasksByPercent();
                    for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                        std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                    }
                    break;
                case 9:
                    return;
                }
                std::cout << "��� ����������� ������� ����� �������..." << std::endl;
                system("pause>nul");
            }
            break;
        case User::Role::common:
            std::cout << "���� ��������� -" << _employee.second->getName() << "- <- " << _login << std::endl;
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