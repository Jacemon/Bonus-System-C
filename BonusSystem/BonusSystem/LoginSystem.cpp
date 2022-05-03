#include "LoginSystem.h"

#include <memory>

std::shared_ptr<LoginSystem> LoginSystem::getInstance() {
    static std::shared_ptr<LoginSystem> _loginSystem;
    if (_loginSystem == nullptr) {
        _loginSystem = std::make_shared<LoginSystem>(LoginSystem());
        (*_loginSystem).addUser("admin", "admin", User::Role::admin);
    }
    return _loginSystem;
}

std::shared_ptr<User> LoginSystem::LogIn(std::string login, std::string password) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it != _users.end() && it->second->LogIn(login, password)) {
        return it->second;
    }
    return nullptr;
}

void LoginSystem::addUser(std::string login, std::string password, User::Role role) {
	_users.insert(std::pair<std::string, 
        std::shared_ptr<User>>(login, std::make_shared<User>(login, password, role)));
}

void LoginSystem::deleteUser(std::string login) {
    _users.erase(login);
}

void LoginSystem::editUserLogin(std::string login, std::string newLogin) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it == _users.end()) {
        return;
    }
    std::shared_ptr<User> user = it->second;
    (*user)._login = newLogin;
    _users.insert(std::pair<std::string, std::shared_ptr<User>>(newLogin, user));
}

std::shared_ptr<User> LoginSystem::getUserByLogin(std::string login) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it == _users.end()) {
        return nullptr;
    }
    return it->second;
}

void LoginSystem::editUserPassword(std::string login, std::string newPassword) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it == _users.end()) {
        return;
    }
    std::shared_ptr<User> user = it->second;
    (*user)._passwordHash = std::hash<std::string>{ }(newPassword);;
    _users.insert(std::pair<std::string, std::shared_ptr<User>>(login, user));
}

void LoginSystem::setEmployeeToUser(std::shared_ptr<BonusSystem> bonusSystem, std::string login, int employeeId) {
    std::shared_ptr<Employee> employee = bonusSystem->getEmployeeById(employeeId);
    if (employee == nullptr) {
        return;
    }
    getUserByLogin(login)->_employee.second = employee;
    getUserByLogin(login)->_employee.first = employeeId;
}

void LoginSystem::deleteEmployeeOnUsers(int employeeId) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.begin();

    while (it != _users.end()) {
        if (it->second->_employee.first == employeeId) {
            it->second->_employee = std::pair<int, std::shared_ptr<Employee>>();
        }
        it++;
    }
}

std::vector<User> LoginSystem::getUsers() {
    std::vector<User> users;
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.begin();

    while (it != _users.end()) {
        users.push_back(User(*(it->second)));
        it++;
    }

    return users;
}
