package by.jcompany.bonus_system.util;

import by.jcompany.bonus_system.entity.Employee;
import by.jcompany.bonus_system.entity.User;
import org.hibernate.SessionFactory;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.hibernate.cfg.Configuration;

public class HibernateSessionFactory {
    private static SessionFactory sessionFactory;
    
    public static SessionFactory getSessionFactory() {
        if (sessionFactory == null) {
            try {
                Configuration configuration = new Configuration().configure();
                configuration.addAnnotatedClass(User.class);
                configuration.addAnnotatedClass(Employee.class);
                StandardServiceRegistryBuilder builder = new StandardServiceRegistryBuilder()
                    .applySettings(configuration.getProperties());
                sessionFactory = configuration.buildSessionFactory(builder.build());
                
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
        return sessionFactory;
    }
}