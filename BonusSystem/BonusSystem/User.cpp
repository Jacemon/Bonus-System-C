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
                std::cout << "Админ меню -" + _login + "-: " << std::endl;
                std::cout << "1. Добавить/изменить/удалить пользователя" << std::endl;
                std::cout << "2. Добавить/изменить/удалить работника" << std::endl;
                std::cout << "3. Добавить/изменить/удалить задачу" << std::endl;
                std::cout << "4. Добавить/изменить/удалить задачу работнику" << std::endl;
                std::cout << "5. Пометить задачу выполненной" << std::endl;
                std::cout << "6. Показать пользователей" << std::endl;
                std::cout << "7. Показать работников" << std::endl;
                std::cout << "8. Показать задачи" << std::endl;
                std::cout << "9. <- Назад" << std::endl;

         
                // работнику назначают задачу
                // он её "выполняет" и помечает выполненной
                // она будет отображаться в списке под пунктом 5 (мб вывести сразу перед началом меню)
                // если админ решит что она "выполнена" то помечает её выполненной и
                // работнику начисляются проценты или баллы

                // выплатить премии добавить пункт как дойду вообще до денег

                // установить цену баллу

                switch (check::getNaturalValueBefore(9, ">>> ", "Неверный ввод!")) {
                case 1:
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

                        (*_loginSystem).addUser(userLogin, userPassword, Role::common);

                        employeeName = check::getProperNameValue("Введите имя работника: ");
                        employeeId = (*_bonusSystem).addEmployee(employeeName);

                        (*_loginSystem).setEmployeeToUser(_bonusSystem, userLogin, employeeId);
                        break;
                    case 2:
                        std::cout << "-<Пользователи>-" << std::endl;
                        users = (*_loginSystem).getUsers();
                        for (User user : users) {
                            std::cout << " - " << user._login;
                            if (user._employee.second != nullptr) {
                                std::cout << " -> " << user._employee.second->getName();
                            }
                            std::cout << std::endl;
                        }

                        userLogin = check::getWordValue("Введите логин изменяемого пользователя: ", "Неверный ввод!");
                        user = (*_loginSystem).getUserByLogin(userLogin);
                        if (user == nullptr) {
                            std::cout << "Пользователя с данным логином не существует!" << std::endl;
                            break;
                        }

                        std::cout << "1. Изменить логин" << std::endl;
                        std::cout << "2. Изменить пароль" << std::endl;
                        std::cout << "3. Изменить работника" << std::endl;
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
                            std::cout << "1. Изменить имя работника" << std::endl;
                            std::cout << "2. Назначить другого работника" << std::endl;
                            std::cout << "3. <- Назад" << std::endl;

                            switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                            case 1:
                                newEmployeeName = check::getProperNameValue("Введите новое имя работника: ");
                                (*_loginSystem).getUserByLogin(userLogin)->_employee.second->setName(newEmployeeName);
                                break;
                            case 2:
                                std::cout << "-<Работники>-" << std::endl;
                                employees = (*_bonusSystem).getEmployees();
                                for (std::pair<int, Employee> employee : employees) {
                                    std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                                }

                                employeeId = check::getNaturalValue("Введите ID нового работника: ", "Неверный ввод!");
                                employee = (*_bonusSystem).getEmployeeById(employeeId);
                                while (employee == nullptr) {
                                    std::cout << "Такого ID нет" << std::endl;
                                    employeeId = check::getNaturalValue("Введите ID нового работника: ", "Неверный ввод!");
                                    employee = (*_bonusSystem).getEmployeeById(employeeId);
                                }
                                (*_loginSystem).setEmployeeToUser(_bonusSystem, userLogin, employeeId);
                                break;
                            }
                            break;
                        }
                        break;
                    case 3:
                        std::cout << "-<Пользователи>-" << std::endl;
                        users = (*_loginSystem).getUsers();
                        for (User user : users) {
                            std::cout << " - " << user._login;
                            if (user._employee.second != nullptr) {
                                std::cout << " -> " << user._employee.second->getName();
                            }
                            std::cout << std::endl;
                        }

                        userLogin = check::getWordValue("Введите логин для удаления: ", "Неверный ввод!");

                        (*_loginSystem).deleteUser(userLogin);
                        break;
                    }
                    break;
                case 2:
                    std::cout << "1. Добавить работника" << std::endl;
                    std::cout << "2. Изменить работника" << std::endl;
                    std::cout << "3. Удалить работника" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        (*_bonusSystem).addEmployee(check::getProperNameValue("Введите имя работника: "));
                        break;
                    case 2:
                        std::cout << "-<Работники>-" << std::endl;
                        employees = (*_bonusSystem).getEmployees();
                        for (std::pair<int, Employee> employee : employees) {
                            std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                        }

                        employeeId = check::getNaturalValue("Введите ID работника для изменения: ");
                        newEmployeeName = check::getProperNameValue("Введите новое имя работника: ");
                        (*_bonusSystem).editEmployee(employeeId, newEmployeeName);
                        break;
                    case 3:
                        std::cout << "-<Работники>-" << std::endl;
                        employees = (*_bonusSystem).getEmployees();
                        for (std::pair<int, Employee> employee : employees) {
                            std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                        }

                        employeeId = check::getNaturalValue("Введите ID работника для удаления: ");
                        (*_bonusSystem).deleteEmployee(employeeId);
                        (*_loginSystem).deleteEmployeeOnUsers(employeeId);
                        break;
                    }
                    break;
                case 3:
                    std::cout << "1. Добавить задачу" << std::endl;
                    std::cout << "2. Изменить задачу" << std::endl;
                    std::cout << "3. Удалить задачу" << std::endl;
                    std::cout << "4. <- Назад" << std::endl;

                    switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                    case 1:
                        std::cout << "Введите текст задания (Enter для конца ввода): ";
                        std::getline(std::cin, taskText, '\n');

                        std::cout << "1. Добавить задачу за баллы" << std::endl;
                        std::cout << "2. Добавить задачу за процент от з/п" << std::endl;
                        std::cout << "3. <- Назад" << std::endl;

                        switch (check::getNaturalValueBefore(3, ">>> ", "Неверный ввод!")) {
                        case 1:
                            points = check::getNaturalValue("Введите количество баллов: ", "Неверный ввод!");
                            (*_bonusSystem).createTaskByPoint(taskText, points);
                            break;
                        case 2:
                            percents = check::getDoubleValueFromTo(0, 100, "Введите количество процентов: ", "Неверный ввод!");
                            (*_bonusSystem).createTaskByPercent(taskText, percents);
                            break;
                        }
                        break;
                    case 2:
                        std::cout << "1. Изменить текст задачи" << std::endl;
                        std::cout << "2. Изменить баллы задачи" << std::endl;
                        std::cout << "3. Изменить проценты задачи" << std::endl;
                        std::cout << "4. <- Назад" << std::endl;

                        switch (check::getNaturalValueBefore(4, ">>> ", "Неверный ввод!")) {
                        case 1:
                            std::cout << "-<Задачи>-" << std::endl;
                            std::cout << "-По баллам-" << std::endl;
                            tasksByPoint = (*_bonusSystem).getTasksByPoint();
                            for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                            }
                            std::cout << "-По процентам-" << std::endl;
                            tasksByPercent = (*_bonusSystem).getTasksByPercent();
                            for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                            }

                            taskId = check::getNaturalValue("Введите ID задачи для изменения: ", "Неверный ввод!");
                            std::cout << "Введите новый текст задания (Enter для конца ввода): ";
                            std::getline(std::cin, taskText, '\n');

                            (*_bonusSystem).editTask(taskId, taskText);
                            break;
                        case 2:
                            std::cout << "-<Задачи>-" << std::endl;
                            std::cout << "-По баллам-" << std::endl;
                            tasksByPoint = (*_bonusSystem).getTasksByPoint();
                            for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                            }

                            taskId = check::getNaturalValue("Введите ID задачи для изменения: ", "Неверный ввод!");
                            points = check::getNaturalValue("Введите новое количество баллов: ", "Неверный ввод!");

                            (*_bonusSystem).editTask(taskId, points);
                            break;
                        case 3:
                            std::cout << "-<Задачи>-" << std::endl;
                            std::cout << "-По процентам-" << std::endl;
                            tasksByPercent = (*_bonusSystem).getTasksByPercent();
                            for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                                std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                            }

                            taskId = check::getNaturalValue("Введите ID задачи для изменения: ", "Неверный ввод!");
                            percents = check::getDoubleValueFromTo(0, 100, "Введите новое количество процентов: ", "Неверный ввод!");

                            (*_bonusSystem).editTask(taskId, percents);
                            break;
                        }
                        break;
                    case 3:
                        std::cout << "-<Задачи>-" << std::endl;
                        std::cout << "-По баллам-" << std::endl;
                        tasksByPoint = (*_bonusSystem).getTasksByPoint();
                        for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                            std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                        }
                        std::cout << "-По процентам-" << std::endl;
                        tasksByPercent = (*_bonusSystem).getTasksByPercent();
                        for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                            std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                        }

                        taskId = check::getNaturalValue("Введите ID задачи для удаления: ", "Неверный ввод!");
                        (*_bonusSystem).deleteTask(taskId);
                        break;
                    }
                    break;
                case 6:
                    std::cout << "-<Пользователи>-" << std::endl;
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
                    std::cout << "-<Работники>-" << std::endl;
                    employees = (*_bonusSystem).getEmployees();
                    for (std::pair<int, Employee> employee : employees) {
                        std::cout << employee.first << " - " << employee.second.getName() << std::endl;
                    }
                    break;
                case 8:
                    std::cout << "-<Задачи>-" << std::endl;
                    std::cout << "-По баллам-" << std::endl;
                    tasksByPoint = (*_bonusSystem).getTasksByPoint();
                    for (std::pair<int, TaskByPoint> task : tasksByPoint) {
                        std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPoints() << std::endl;
                    }
                    std::cout << "-По процентам-" << std::endl;
                    tasksByPercent = (*_bonusSystem).getTasksByPercent();
                    for (std::pair<int, TaskByPercent> task : tasksByPercent) {
                        std::cout << task.first << " - " << task.second.getText() << " - " << task.second.getPercent() << std::endl;
                    }
                    break;
                case 9:
                    return;
                }
                std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
                system("pause>nul");
            }
            break;
        case User::Role::common:
            std::cout << "Меню работника -" << _employee.second->getName() << "- <- " << _login << std::endl;
            std::cout << "Just user\n";
            std::cout << "Для продолжения нажмите любую клавишу..." << std::endl;
            system("pause>nul");
            break;
        }
    }
    catch (std::exception ex) {
        std::cout << ex.what();
    }
}