#include "BonusSystem.h"

int BonusSystem::TaskID = 1;
int BonusSystem::EmployeeID = 1;
double BonusSystem::PointPrice = 0;

std::shared_ptr<BonusSystem> BonusSystem::getInstance() {
    static std::shared_ptr<BonusSystem> _bonusSystem;
    if (_bonusSystem == nullptr) {
        _bonusSystem = std::make_shared<BonusSystem>(BonusSystem());
    }
    return _bonusSystem;
}

double BonusSystem::getPointPrice() {
    return PointPrice;
}

void BonusSystem::setPointPrice(double value) {
    if (value > 0) {
        PointPrice = value;
    }
}

void BonusSystem::createTaskByPoint(std::string taskText, int points) {
    _tasks.insert(std::pair<int, std::shared_ptr<Task>>(TaskID++, new TaskByPoint(taskText, points)));
}

void BonusSystem::createTaskByPercent(std::string taskText, double percent) {
    _tasks.insert(std::pair<int, std::shared_ptr<Task>>(TaskID++, new TaskByPercent(taskText, percent)));
}

void BonusSystem::editTask(int taskId, std::string taskText) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.find(taskId);
    if (it != _tasks.end()) {
        it->second->_taskText = taskText;
    }
}
void BonusSystem::editTask(int taskId, double percent) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.find(taskId);
    if (it != _tasks.end() && it->second->_type == Task::TaskType::byPercent) {
        std::static_pointer_cast<TaskByPercent>(it->second)->_percent = percent;
    }
}
void BonusSystem::editTask(int taskId, int points) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.find(taskId);
    if (it != _tasks.end() && it->second->_type == Task::TaskType::byPoint) {
        std::static_pointer_cast<TaskByPoint>(it->second)->_points = points;
    }
}
void BonusSystem::deleteTask(int taskId) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.find(taskId);
    if (it != _tasks.end()) {
        _tasks.erase(it);
    }
}

int BonusSystem::addEmployee(std::string name) {
    _employees.insert(std::pair<int, std::shared_ptr<Employee>>(EmployeeID, new Employee(name)));
    return EmployeeID++;
}
void BonusSystem::deleteEmployee(int employeeId) {
    std::map<int, std::shared_ptr<Employee>>::iterator it = _employees.find(employeeId);
    if (it != _employees.end()) {
        _employees.erase(it);
    }
}
void BonusSystem::editEmployee(int employeeId, std::string newName) {
    std::map<int, std::shared_ptr<Employee>>::iterator it = _employees.find(employeeId);
    if (it != _employees.end()) {
        it->second->setName(newName);
    }
}

std::shared_ptr<Employee> BonusSystem::getEmployeeById(int employeeId) {
    std::map<int, std::shared_ptr<Employee>>::iterator it = _employees.find(employeeId);
    if (it == _employees.end()) {
        return nullptr;
    }
    return it->second;
}

std::map<int, Employee> BonusSystem::getEmployees() {
    std::map<int, Employee> employees;
    std::map<int, std::shared_ptr<Employee>>::iterator it = _employees.begin();
    while (it != _employees.end()) {
        employees.insert(std::pair<int, Employee>(it->first, Employee(*it->second)));
        it++;
    }
    return employees;
}

std::map<int, TaskByPoint> BonusSystem::getTasksByPoint() {
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.begin();
    while (it != _tasks.end()) {
        if (it->second->_type == Task::TaskType::byPoint) {
            tasksByPoint.insert(std::pair<int, TaskByPoint>(it->first, *(std::static_pointer_cast<TaskByPoint>(it->second))));
        }
        it++;
    }
    return tasksByPoint;
}
std::map<int, TaskByPercent> BonusSystem::getTasksByPercent() {
    std::map<int, TaskByPercent> tasksByPercent;
    std::map<int, std::shared_ptr<Task>>::iterator it = _tasks.begin();
    while (it != _tasks.end()) {
        if (it->second->_type == Task::TaskType::byPercent) {
            tasksByPercent.insert(std::pair<int, TaskByPercent>(it->first, *(std::static_pointer_cast<TaskByPercent>(it->second))));
        }
        it++;
    }
    return tasksByPercent;
}