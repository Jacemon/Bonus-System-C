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
void BonusSystem::markTaskCompleted(int taskId) {
    std::map<int, int>::iterator it = _taskID_employeeID.find(taskId);
    if (it == _taskID_employeeID.end()) {
        return;
    }
    std::shared_ptr<Employee> employee = getEmployeeById(it->second);
    std::map<int, std::shared_ptr<Task>> markedTasks = employee->getMarkedTasks();
    std::map<int, std::shared_ptr<Task>>::iterator itMrkTsk = markedTasks.find(taskId);
    if (itMrkTsk == markedTasks.end()) {
        return;
    }
    _taskID_employeeID.erase(it);
    std::map<int, std::shared_ptr<Task>>::iterator itHldTsk = _holdedTasks.find(taskId);
    _completedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, itHldTsk->second));
    _holdedTasks.erase(itHldTsk);

    employee->completeTask(taskId);
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
std::map<int, TaskByPoint> BonusSystem::getHoldedTasksByPoint() {
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, std::shared_ptr<Task>>::iterator it = _holdedTasks.begin();
    while (it != _holdedTasks.end()) {
        if (it->second->_type == Task::TaskType::byPoint) {
            tasksByPoint.insert(std::pair<int, TaskByPoint>(it->first, *(std::static_pointer_cast<TaskByPoint>(it->second))));
        }
        it++;
    }
    return tasksByPoint;
}
std::map<int, TaskByPercent> BonusSystem::getHoldedTasksByPercent() {
    std::map<int, TaskByPercent> tasksByPercent;
    std::map<int, std::shared_ptr<Task>>::iterator it = _holdedTasks.begin();
    while (it != _holdedTasks.end()) {
        if (it->second->_type == Task::TaskType::byPercent) {
            tasksByPercent.insert(std::pair<int, TaskByPercent>(it->first, *(std::static_pointer_cast<TaskByPercent>(it->second))));
        }
        it++;
    }
    return tasksByPercent;
}
std::map<int, TaskByPoint> BonusSystem::getCompletedTasksByPoint() {
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, std::shared_ptr<Task>>::iterator it = _completedTasks.begin();
    while (it != _completedTasks.end()) {
        if (it->second->_type == Task::TaskType::byPoint) {
            tasksByPoint.insert(std::pair<int, TaskByPoint>(it->first, *(std::static_pointer_cast<TaskByPoint>(it->second))));
        }
        it++;
    }
    return tasksByPoint;
}
std::map<int, TaskByPercent> BonusSystem::getCompletedTasksByPercent() {
    std::map<int, TaskByPercent> tasksByPercent;
    std::map<int, std::shared_ptr<Task>>::iterator it = _completedTasks.begin();
    while (it != _completedTasks.end()) {
        if (it->second->_type == Task::TaskType::byPercent) {
            tasksByPercent.insert(std::pair<int, TaskByPercent>(it->first, *(std::static_pointer_cast<TaskByPercent>(it->second))));
        }
        it++;
    }
    return tasksByPercent;
}

void BonusSystem::setTaskToEmployee(int employeeId, int taskId) {
    std::map<int, std::shared_ptr<Employee>>::iterator itEmp = _employees.find(employeeId);
    std::map<int, std::shared_ptr<Task>>::iterator itTsk = _tasks.find(taskId);

    if (itEmp == _employees.end() || itTsk == _tasks.end()) {
        return;
    }
    std::pair<int, std::shared_ptr<Task>> task = std::make_pair(taskId, itTsk->second);
    _holdedTasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _tasks.erase(itTsk);
    itEmp->second->addTask(task);
    _taskID_employeeID.insert(std::pair<int, int>(taskId, employeeId));
}

void BonusSystem::deleteTaskFromEmployee(int employeeId, int taskId) {
    std::map<int, std::shared_ptr<Employee>>::iterator itEmp = _employees.find(employeeId);
    
    if (itEmp == _employees.end()) {
        return;
    }
    std::map<int, std::shared_ptr<Task>> employeeTasks = itEmp->second->getCurrentTasks();
    std::map<int, std::shared_ptr<Task>>::iterator itEmpTsk = employeeTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator itTsk = _holdedTasks.find(taskId);

    if (itEmpTsk == employeeTasks.end() || itTsk == _holdedTasks.end()) {
        return;
    }

    std::map<int, int>::iterator itTskIdEmpId = _taskID_employeeID.find(taskId);
    _taskID_employeeID.erase(itTskIdEmpId);

    _tasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _holdedTasks.erase(itTsk);
    itEmp->second->deleteTask(taskId);
}

void BonusSystem::editTaskFromEmployee(int employeeId, int taskId, int newTaskId) {
    if (taskId == newTaskId) {
        return;
    }

    std::map<int, std::shared_ptr<Employee>>::iterator itEmp = _employees.find(employeeId);
    if (itEmp == _employees.end()) {
        return;
    }
    std::map<int, std::shared_ptr<Task>> employeeTasks = itEmp->second->getCurrentTasks();
    std::map<int, std::shared_ptr<Task>>::iterator itEmpTsk = employeeTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator itTsk = _holdedTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator itNewTsk = _tasks.find(newTaskId);

    if (itEmpTsk == employeeTasks.end() || itTsk == _holdedTasks.end() || itNewTsk == _tasks.end()) {
        return;
    }
    std::pair<int, std::shared_ptr<Task>> newTask = std::make_pair(newTaskId, itNewTsk->second);

    std::map<int, int>::iterator itTskIdEmpId = _taskID_employeeID.find(taskId);
    _taskID_employeeID.erase(itTskIdEmpId);
    _taskID_employeeID.insert(std::pair<int, int>(newTaskId, employeeId));

    _tasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _holdedTasks.erase(itTsk);
    _holdedTasks.insert(std::pair<int, std::shared_ptr<Task>>(itNewTsk->first, itNewTsk->second));
    _tasks.erase(itNewTsk);

    itEmp->second->deleteTask(taskId);
    itEmp->second->addTask(newTask);
}
