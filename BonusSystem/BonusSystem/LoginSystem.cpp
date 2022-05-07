#include "LoginSystem.h"

#include <memory>

std::shared_ptr<LoginSystem> LoginSystem::_loginSystem;

std::shared_ptr<LoginSystem> LoginSystem::getInstance() {
    if (_loginSystem == nullptr) {
        _loginSystem = std::make_shared<LoginSystem>(LoginSystem());
        (*_loginSystem).addUser("admin", "admin", User::Role::admin);
    }
    return _loginSystem;
}
std::shared_ptr<LoginSystem> LoginSystem::resetToDefault() {
    _loginSystem = nullptr;
    return getInstance();
}

std::shared_ptr<User> LoginSystem::LogIn(std::string login, std::string password) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it != _users.end() && it->second->LogIn(login, password)) {
        return it->second;
    }
    return nullptr;
}

LoginSystem::LoginSystem() { }

LoginSystem::LoginSystem(const LoginSystem& copy) : 
    _users(copy._users), _userLogin_employeeID(copy._userLogin_employeeID) { }
   

void LoginSystem::addUser(std::string login, std::string password, User::Role role) {
	_users.insert(std::pair<std::string, 
        std::shared_ptr<User>>(login, std::make_shared<User>(login, password, role)));
}
void LoginSystem::addUser(User user) {
    _users.insert(std::pair<std::string, 
        std::shared_ptr<User>>(user._login, std::make_shared<User>(user)));
}

void LoginSystem::deleteUser(std::string login) {
    if (getUserByLogin(login)->_role == User::Role::admin) {
        return;
    }
    _users.erase(login);
}

void LoginSystem::editUserLogin(std::string login, std::string newLogin) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.find(login);
    if (it == _users.end()) {
        return;
    }
    std::shared_ptr<User> user = it->second;
    (*user)._login = newLogin;
    _users.erase(it);
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
    (*user)._passwordHash = std::hash<std::string>{ }(newPassword);
}

void LoginSystem::setEmployeeToUser(std::shared_ptr<BonusSystem> bonusSystem, std::string login, int employeeId) {
    std::shared_ptr<Employee> employee = bonusSystem->getEmployeeById(employeeId);
    if (employee == nullptr) {
        return;
    }
    getUserByLogin(login)->_employee.second = employee;
    getUserByLogin(login)->_employee.first = employeeId;
    _userLogin_employeeID.erase(login);
    _userLogin_employeeID.insert(std::pair<std::string, int>(login, employeeId));
}

void LoginSystem::deleteEmployeeOnUsers(int employeeId) {
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.begin();

    while (it != _users.end()) {
        if (it->second->_employee.first == employeeId) {
            it->second->_employee = std::pair<int, std::shared_ptr<Employee>>();
            _userLogin_employeeID.erase(it->first);
        }
        it++;
    }
}

std::map<std::string, User> LoginSystem::getUsers() {
    std::map<std::string, User> users;
    std::map<std::string, std::shared_ptr<User>>::iterator it = _users.begin();

    while (it != _users.end()) {
        users.insert(std::pair<std::string, User>(it->first, User(*it->second)));
        it++;
    }

    return users;
}

std::ofstream& operator<<(std::ofstream& ofs, LoginSystem loginSystem) {
    ofs << loginSystem._users.size() << " " << loginSystem._userLogin_employeeID.size() << std::endl;
    for (auto user : loginSystem._users) {
        ofs << *user.second << std::endl;
    }
    for (auto userEmployee : loginSystem._userLogin_employeeID) {
        ofs << userEmployee.first << " " << userEmployee.second << std::endl;
    }
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, LoginSystem& loginSystem) {
    try {
        int userSize, userEmployeeSize;
        std::string login;
        int employeeId;
        User user;

        ifs >> userSize >> userEmployeeSize;

        loginSystem._users.clear();
        loginSystem._userLogin_employeeID.clear();
        for (int i = 0; i < userSize; i++) {
            ifs >> user;
            loginSystem.addUser(user);
        }
        for (int i = 0; i < userEmployeeSize; i++) {
            ifs >> login >> employeeId;
            loginSystem._userLogin_employeeID.insert(std::pair < std::string, int>(login, employeeId));
        }
        if (ifs.fail() != 0) {
            throw std::string();
        }
        auto bonusSystem = BonusSystem::getInstance();
        for (auto usrLempID : loginSystem._userLogin_employeeID) {
            loginSystem.setEmployeeToUser(bonusSystem, usrLempID.first, usrLempID.second);
        }
    }
    catch (...) {
        throw std::string("Произошла ошибка загрузки базы данных системы пользователей.");
    }
    return ifs;
}
