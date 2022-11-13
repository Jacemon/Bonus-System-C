package by.jcompany.bonus_system_server;

import by.jcompany.bonus_system_server.entity.Employee;
import by.jcompany.bonus_system_server.entity.User;
import by.jcompany.bonus_system_server.service.EmployeeService;
import by.jcompany.bonus_system_server.service.Service;
import by.jcompany.bonus_system_server.service.UserService;
import by.jcompany.bonus_system_server.util.HashManager;

public class Test {
    public static void main(String[] args) {
        Service<Employee, Integer> employeeService = new EmployeeService();
        Service<User, String> userService = new UserService();
        
        String password = "123123123";
        userService.create(new User("login2", HashManager.getHash(password)));
        
        employeeService.create(new Employee("Eugene", "Bel"));
    }
}
