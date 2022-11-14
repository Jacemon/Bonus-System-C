package by.jcompany.bonus_system.boot;

import by.jcompany.bonus_system.entity.User;
import by.jcompany.bonus_system.service.Service;
import by.jcompany.bonus_system.service.UserService;

public class ClientFunctions {
    private static final Service<User, String> userService = new UserService();
    
    public static boolean createUser(User user) {
        return userService.create(user);
    }
}
