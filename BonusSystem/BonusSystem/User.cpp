#include "User.h"

#include "LoginSystem.h"
#include "BonusSystem.h"
#include "checking.h"

#include <fstream>
#include <string>
#include <memory>
#include <exception>

User::User() { }

User::User(const User& copy) {
    _login = copy._login;
    _passwordHash = copy._passwordHash;
    _employee = copy._employee;
    _role = copy._role;
}

User::User(std::string login, std::string password, Role role) {
    _role = role;
    _login = login;
    _passwordHash = std::hash<std::string>{ }(password);
    _employee = std::pair<int, std::shared_ptr<Employee>>();
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

std::ostream& operator<<(std::ostream& os, User user) {
    std::cout << user._login;
    if (user._employee.second != nullptr) {
        std::cout << " -> " << user._employee.second->getName();
    }
    std::cout << std::endl;
    return os;
}

std::ofstream& operator<<(std::ofstream& ofs, User user) {
    ofs << user._login << " " << user._passwordHash << " " << static_cast<int>(user._role);
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, User& user) {
    int role;
    ifs >> user._login >> user._passwordHash >> role;
    user._role = static_cast<User::Role>(role);
    return ifs;
};