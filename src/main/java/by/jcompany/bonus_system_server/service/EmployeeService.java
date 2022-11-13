package by.jcompany.bonus_system_server.service;

import by.jcompany.bonus_system_server.dao.Dao;
import by.jcompany.bonus_system_server.dao.EmployeeDao;
import by.jcompany.bonus_system_server.entity.Employee;

import java.util.List;

public class EmployeeService implements Service<Employee, Integer> {
    Dao<Employee, Integer> employeeDao = new EmployeeDao();
    
    @Override
    public boolean create(Employee employee) {
        return employeeDao.create(employee);
    }
    
    @Override
    public List<Employee> readAll() {
        return employeeDao.readAll();
    }
    
    @Override
    public boolean update(Employee employee) {
        return employeeDao.update(employee);
    }
    
    @Override
    public boolean delete(Employee employee) {
        return employeeDao.delete(employee);
    }
    
    @Override
    public Employee read(Integer id) {
        return employeeDao.read(id);
    }
}
