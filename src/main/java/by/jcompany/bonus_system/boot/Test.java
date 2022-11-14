package by.jcompany.bonus_system.boot;

import by.jcompany.bonus_system.entity.Employee;
import by.jcompany.bonus_system.entity.User;
import by.jcompany.bonus_system.service.EmployeeService;
import by.jcompany.bonus_system.service.Service;
import by.jcompany.bonus_system.service.UserService;
import by.jcompany.bonus_system.util.HashManager;

public class Test {
    public static void test() {
        Service<Employee, Integer> employeeService = new EmployeeService();
        Service<User, String> userService = new UserService();
        
        String password = "123123123";
        userService.create(new User("login2", HashManager.getHash(password)));
        
        employeeService.create(new Employee("Eugene", "Bel"));
    }
}
