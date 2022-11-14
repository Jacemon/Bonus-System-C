package by.jcompany.bonus_system.dao;

import by.jcompany.bonus_system.entity.User;
import by.jcompany.bonus_system.util.HibernateSessionFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.util.ArrayList;
import java.util.List;

public class UserDao implements Dao<User, String> {
    @Override
    public boolean create(User user) {
        try (Session session = HibernateSessionFactory.getSessionFactory().openSession()) {
            Transaction transaction = session.beginTransaction();
            session.persist(user);
            transaction.commit();
        } catch (HibernateException exception) {
            exception.printStackTrace();
            return false;
        }
        return true;
    }
    
    @Override
    public List<User> readAll() {
        List<User> clients;
        try (Session session = HibernateSessionFactory.getSessionFactory().openSession()) {
            clients = new ArrayList<>(session.createQuery("FROM User", User.class).getResultList());
        } catch (HibernateException exception) {
            exception.printStackTrace();
            return null;
        }
        return clients;
    }
    
    @Override
    public boolean update(User user) {
        try (Session session = HibernateSessionFactory.getSessionFactory().openSession()) {
            Transaction transaction = session.beginTransaction();
            if (user.getLogin() == null) {
                throw new HibernateException("Entity has null id");
            }
            session.merge(user);
            transaction.commit();
        } catch (HibernateException exception) {
            exception.printStackTrace();
            return false;
        }
        return true;
    }
    
    @Override
    public boolean delete(User user) {
        try (Session session = HibernateSessionFactory.getSessionFactory().openSession()) {
            Transaction transaction = session.beginTransaction();
            session.remove(user);
            transaction.commit();
        } catch (HibernateException exception) {
            exception.printStackTrace();
            return false;
        }
        return true;
    }
    
    @Override
    public User read(String login) {
        User user;
        try (Session session = HibernateSessionFactory.getSessionFactory().openSession()) {
            user = session.get(User.class, login);
        } catch (HibernateException exception) {
            exception.printStackTrace();
            return null;
        }
        return user;
    }
}
