#include "BonusSystem.h"
#include "SourceBonusSystem.h"

#include <fstream>

std::shared_ptr<BonusSystem> BonusSystem::_bonusSystem;

std::shared_ptr<BonusSystem> BonusSystem::getInstance() {
    if (_bonusSystem == nullptr) {
        _bonusSystem = std::make_shared<BonusSystem>(BonusSystem());
    }
    return _bonusSystem;
}
std::shared_ptr<BonusSystem> BonusSystem::resetToDefault() {
    _bonusSystem = nullptr;
    return getInstance();
}

double BonusSystem::getPointPrice() {
    return PointPrice;
}
void BonusSystem::setPointPrice(double value) {
    if (value > 0) {
        PointPrice = value;
    }
}

void BonusSystem::addTaskByPoint(std::string taskText, int points) {
    auto task = _allTasks.insert(std::pair<int, std::shared_ptr<Task>>(TaskID++, new TaskByPoint(taskText, points)));
    _freeTasks.insert(std::pair<int, std::shared_ptr<Task>>(task.first->first, task.first->second));
}
void BonusSystem::addTaskByPercent(std::string taskText, double percent) {
    auto task = _allTasks.insert(std::pair<int, std::shared_ptr<Task>>(TaskID++, new TaskByPercent(taskText, percent)));
    _freeTasks.insert(std::pair<int, std::shared_ptr<Task>>(task.first->first, task.first->second));
}
void BonusSystem::editTask(int taskId, std::string taskText) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _freeTasks.find(taskId);
    if (it != _freeTasks.end()) {
        it->second->setTaskText(taskText);
    }
}
void BonusSystem::editTask(int taskId, double percent) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _freeTasks.find(taskId);
    if (it != _freeTasks.end() && it->second->_type == Task::TaskType::byPercent) {
        std::static_pointer_cast<TaskByPercent>(it->second)->setPercent(percent);
    }
}
void BonusSystem::editTask(int taskId, int points) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _freeTasks.find(taskId);
    if (it != _freeTasks.end() && it->second->_type == Task::TaskType::byPoint) {
        std::static_pointer_cast<TaskByPoint>(it->second)->setPoints(points);
    }
}
void BonusSystem::deleteTask(int taskId) {
    std::map<int, std::shared_ptr<Task>>::iterator it = _allTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator fit = _freeTasks.find(taskId);
    if (fit != _freeTasks.end()) {
        _freeTasks.erase(fit);
        if (it != _allTasks.end()) {
            _allTasks.erase(it);
        }
    }
}
void BonusSystem::setTaskCompleted(int taskId) {
    std::map<int, int>::iterator it = _taskID_employeeID.find(taskId);
    if (it == _taskID_employeeID.end()) {
        return;
    }
    std::shared_ptr<Employee<std::string>> employee = getEmployeeById(it->second);
    if (employee == nullptr) {
        return;
    }
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

int BonusSystem::addEmployee(std::string name, double salary) {
    _employees.insert(std::pair<int, std::shared_ptr<Employee<std::string>>>(EmployeeID,
        new Employee<std::string>(name, salary)));
    return EmployeeID++;
}
void BonusSystem::deleteEmployee(int employeeId) {
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator it = _employees.find(employeeId);
    if (it != _employees.end()) {
        _employees.erase(it);
    }
}
void BonusSystem::editEmployee(int employeeId, std::string newName) {
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator it = _employees.find(employeeId);
    if (it != _employees.end()) {
        it->second->setName(newName);
    }
}
void BonusSystem::editEmployee(int employeeId, double salary) {
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator it = _employees.find(employeeId);
    if (it != _employees.end()) {
        it->second->setSalary(salary);
    }
}

std::shared_ptr<Employee<std::string>> BonusSystem::getEmployeeById(int employeeId) {
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator it = _employees.find(employeeId);
    if (it == _employees.end()) {
        return nullptr;
    }
    return it->second;
}
std::map<int, Employee<std::string>> BonusSystem::getEmployees() {
    std::map<int, Employee<std::string>> employees;
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator it = _employees.begin();
    while (it != _employees.end()) {
        employees.insert(std::pair<int, Employee<std::string>>(it->first, Employee<std::string>(*it->second)));
        it++;
    }
    return employees;
}

std::map<int, TaskByPoint> BonusSystem::getFreeTasksByPoint() {
    std::map<int, TaskByPoint> tasksByPoint;
    std::map<int, std::shared_ptr<Task>>::iterator it = _freeTasks.begin();
    while (it != _freeTasks.end()) {
        if (it->second->_type == Task::TaskType::byPoint) {
            tasksByPoint.insert(std::pair<int, TaskByPoint>(it->first, *(std::static_pointer_cast<TaskByPoint>(it->second))));
        }
        it++;
    }
    return tasksByPoint;
}
std::map<int, TaskByPercent> BonusSystem::getFreeTasksByPercent() {
    std::map<int, TaskByPercent> tasksByPercent;
    std::map<int, std::shared_ptr<Task>>::iterator it = _freeTasks.begin();
    while (it != _freeTasks.end()) {
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
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator itEmp = _employees.find(employeeId);
    std::map<int, std::shared_ptr<Task>>::iterator itTsk = _freeTasks.find(taskId);

    if (itEmp == _employees.end() || itTsk == _freeTasks.end()) {
        return;
    }
    std::pair<int, std::shared_ptr<Task>> task = std::make_pair(taskId, itTsk->second);
    _holdedTasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _freeTasks.erase(itTsk);
    itEmp->second->addTask(task);
    _taskID_employeeID.insert(std::pair<int, int>(taskId, employeeId));
}
void BonusSystem::deleteTaskFromEmployee(int employeeId, int taskId) {
    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator itEmp = _employees.find(employeeId);
    
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

    _freeTasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _holdedTasks.erase(itTsk);
    itEmp->second->deleteTask(taskId);
}
void BonusSystem::editTaskFromEmployee(int employeeId, int taskId, int newTaskId) {
    if (taskId == newTaskId) {
        return;
    }

    std::map<int, std::shared_ptr<Employee<std::string>>>::iterator itEmp = _employees.find(employeeId);
    if (itEmp == _employees.end()) {
        return;
    }
    std::map<int, std::shared_ptr<Task>> employeeTasks = itEmp->second->getCurrentTasks();
    std::map<int, std::shared_ptr<Task>>::iterator itEmpTsk = employeeTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator itTsk = _holdedTasks.find(taskId);
    std::map<int, std::shared_ptr<Task>>::iterator itNewTsk = _freeTasks.find(newTaskId);

    if (itEmpTsk == employeeTasks.end() || itTsk == _holdedTasks.end() || itNewTsk == _freeTasks.end()) {
        return;
    }
    std::pair<int, std::shared_ptr<Task>> newTask = std::make_pair(newTaskId, itNewTsk->second);

    std::map<int, int>::iterator itTskIdEmpId = _taskID_employeeID.find(taskId);
    _taskID_employeeID.erase(itTskIdEmpId);
    _taskID_employeeID.insert(std::pair<int, int>(newTaskId, employeeId));

    _freeTasks.insert(std::pair<int, std::shared_ptr<Task>>(itTsk->first, itTsk->second));
    _holdedTasks.erase(itTsk);
    _holdedTasks.insert(std::pair<int, std::shared_ptr<Task>>(itNewTsk->first, itNewTsk->second));
    _freeTasks.erase(itNewTsk);

    itEmp->second->deleteTask(taskId);
    itEmp->second->addTask(newTask);
}

void BonusSystem::payBonuses() {
    for (auto employee : _employees) {
        payBonuses(employee.first);
    }
}
void BonusSystem::payBonuses(int employeeId) {
    auto employee = getEmployeeById(employeeId);
    if (employee == nullptr) {
        return;
    }
    std::shared_ptr<SourceBonusSystem> sourceBonusSystem = SourceBonusSystem::getInstance();
    double bonus = employee->getPoints() * PointPrice + employee->getPercents()
        * employee->getSalary() / 100.;
    double total = bonus * (100 - TAX) / 100.;
    if (bonus == 0) {
        std::cout << "У работника нет премий!" << std::endl;
        return;
    }
    if (!(*sourceBonusSystem).takeMoney(bonus)) {
        std::cout << "У источников премирования не достаточно денег для выплаты!" << std::endl;
        return;
    }
    std::cout << employee->getName() << " " << employee->getPoints() << "б. * "
        << PointPrice << " + " << employee->getPercents() << "% * " << employee->getSalary()
        << " = " << bonus << "$ -> " << total << "$ (НДФЛ - " << TAX << "%)" << std::endl;

    std::ofstream fout;
    fout.open("PaidBonuses.dat", std::ios::app, std::ios::binary);
    fout << employee->getName() << " " << employee->getPoints() << "б. * "
        << PointPrice << " + " << employee->getPercents() << "% * " << employee->getSalary()
        << " = " << bonus << "$ -> " << total << "$ (НДФЛ - " << TAX << "%)" << std::endl;
    fout.close();

    employee->setPoints(0);
    employee->setPercents(0);
}

std::ofstream& operator<<(std::ofstream& ofs, BonusSystem bonusSystem) {
    ofs << bonusSystem.TaskID << " " << bonusSystem.EmployeeID << " " << bonusSystem._allTasks.size() << " "
        << bonusSystem._freeTasks.size() << " " << bonusSystem._holdedTasks.size() << " "
        << bonusSystem._completedTasks.size() << " " << bonusSystem._employees.size() << " "
        << bonusSystem._taskID_employeeID.size() << " " << bonusSystem.PointPrice << std::endl;
    for (auto task : bonusSystem._allTasks) {
        if (task.second->_type == Task::TaskType::byPoint) {
            ofs << static_cast<int>(task.second->_type) << std::endl;
            ofs << *std::static_pointer_cast<TaskByPoint>(task.second) << " "
                << task.first << std::endl;
        }
        else if (task.second->_type == Task::TaskType::byPercent) {
            ofs << static_cast<int>(task.second->_type) << std::endl;
            ofs << *std::static_pointer_cast<TaskByPercent>(task.second) << " "
                << task.first << std::endl;
        }
    }
    for (auto task : bonusSystem._freeTasks) {
        ofs << task.first << " ";
    }
    ofs << std::endl;
    for (auto task : bonusSystem._holdedTasks) {
        ofs << task.first << " ";
    }
    ofs << std::endl;
    for (auto task : bonusSystem._completedTasks) {
        ofs << task.first << " ";
    }
    ofs << std::endl;
    for (auto task_employee : bonusSystem._taskID_employeeID) {
        ofs << task_employee.first << " " << task_employee.second << " ";
    }
    ofs << std::endl;
    for (auto employee : bonusSystem._employees) {
        ofs << employee.first << " ";
        ofs << *employee.second << std::endl;
    }
    return ofs;
}
std::ifstream& operator>>(std::ifstream& ifs, BonusSystem& bonusSystem) {
    try {
        int allTaskSize, freeTaskSize, holdedTaskSize, completedTaskSize, employeesSize, taskIDEmployeeIdSize;
        int taskType;
        ifs >> bonusSystem.TaskID >> bonusSystem.EmployeeID >> allTaskSize
            >> freeTaskSize >> holdedTaskSize >> completedTaskSize >> employeesSize
            >> taskIDEmployeeIdSize >> bonusSystem.PointPrice;
        int taskId, employeeId;

        for (int i = 0; i < allTaskSize; i++) {
            ifs >> taskType;
            ifs.get();
            if (static_cast<Task::TaskType>(taskType) == Task::TaskType::byPoint) {
                TaskByPoint taskByPoint;
                ifs >> taskByPoint >> taskId;
                bonusSystem._allTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, new TaskByPoint(taskByPoint)));
            }
            else if (static_cast<Task::TaskType>(taskType) == Task::TaskType::byPercent) {
                TaskByPercent taskByPercent;
                ifs >> taskByPercent >> taskId;
                bonusSystem._allTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, new TaskByPercent(taskByPercent)));
            }
        }
        for (int i = 0; i < freeTaskSize; i++) {
            ifs >> taskId;
            std::shared_ptr<Task> task = bonusSystem._allTasks[taskId];
            if (task != nullptr) {
                bonusSystem._freeTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, task));
            }
        }
        for (int i = 0; i < holdedTaskSize; i++) {
            ifs >> taskId;
            std::shared_ptr<Task> task = bonusSystem._allTasks[taskId];
            if (task != nullptr) {
                bonusSystem._holdedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, task));
            }
        }
        for (int i = 0; i < completedTaskSize; i++) {
            ifs >> taskId;
            std::shared_ptr<Task> task = bonusSystem._allTasks[taskId];
            if (task != nullptr) {
                bonusSystem._completedTasks.insert(std::pair<int, std::shared_ptr<Task>>(taskId, task));
            }
        }
        for (int i = 0; i < taskIDEmployeeIdSize; i++) {
            ifs >> taskId >> employeeId;
            bonusSystem._taskID_employeeID.insert(std::pair<int, int>(taskId, employeeId));
        }
        for (int i = 0; i < employeesSize; i++) {
            Employee<std::string> employee;
            ifs >> employeeId;
            ifs >> employee;
            bonusSystem._employees.insert(std::pair<int, std::shared_ptr<Employee<std::string>>>
                (employeeId, new Employee<std::string>(employee)));
        }
        if (ifs.fail() != 0) {
            throw std::string();
        }
        for (auto taskIdEmployeeId : bonusSystem._taskID_employeeID) {
            auto employee = bonusSystem.getEmployeeById(taskIdEmployeeId.second);
            if (employee == nullptr) {
                throw std::string();
            }
            employee->addTask(std::pair<int, std::shared_ptr<Task>>
                    (taskIdEmployeeId.first, bonusSystem._allTasks[taskIdEmployeeId.first]));
        }
        for (auto employee : bonusSystem._employees) {
            auto markedTasks = employee.second->getMarkedTasks();
            auto completedTasks = employee.second->getCompletedTasks();
            for (auto task : markedTasks) {
                if (employee.second->deleteMarkedTask(task.first)) {
                    employee.second->markTaskCompleted(task.first);
                }
            }
            for (auto task : completedTasks) {
                if (employee.second->deleteCompletedTask(task.first)) {
                    employee.second->addCompletedTask(std::pair<int, std::shared_ptr<Task>>
                        (task.first, bonusSystem._completedTasks[task.first]));
                }
            }
        }
    }
    catch (...) {
        throw std::string("Произошла ошибка загрузки базы данных системы премирования.");
    }
    return ifs;
}