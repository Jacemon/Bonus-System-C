package by.jcompany.bonus_system_server.service;

import by.jcompany.bonus_system_server.dao.Dao;
import by.jcompany.bonus_system_server.dao.UserDao;
import by.jcompany.bonus_system_server.entity.User;

import java.util.List;

public class UserService implements Service<User, String> {
    Dao<User, String> userDao = new UserDao();
    
    @Override
    public boolean create(User user) {
        return userDao.create(user);
    }
    
    @Override
    public List<User> readAll() {
        return userDao.readAll();
    }
    
    @Override
    public boolean update(User user) {
        return userDao.update(user);
    }
    
    @Override
    public boolean delete(User user) {
        return userDao.delete(user);
    }
    
    @Override
    public User read(String login) {
        return userDao.read(login);
    }
}
