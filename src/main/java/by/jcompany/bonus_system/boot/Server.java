package by.jcompany.bonus_system.boot;

import java.net.ServerSocket;
import java.util.Scanner;

public class Server {
    public static boolean exit = false;
    public static String exitServerString = "exit";
    
    public static final int SERVER_PORT = 4040;
    
    public static void start() {
        ServerSocket serverSocket = null;
        int clientCount = 0;
        
        try {
            System.out.println("server starting...");
            System.out.println("for exit input \"" + exitServerString + "\"");
            serverSocket = new ServerSocket(SERVER_PORT);
            
            Thread exitThread = new Thread(() -> {
                while (!exit) {
                    Scanner in = new Scanner(System.in);
                    if (in.nextLine().equals(exitServerString)) {
                        exit = true;
                        System.out.print("Server will closed when next client was processed...");
                    }
                }
            });
            exitThread.start();
            
            while (!exit) {
                ClientHandler clientHandler = new ClientHandler(serverSocket.accept(), clientCount++);
                Thread clientThread = new Thread(clientHandler);
                clientThread.start();
            }
        } catch (Exception exception) {
            exception.printStackTrace();
        } finally {
            try {
                assert serverSocket != null;
                serverSocket.close();//закрытие сокета сервера
            } catch (Exception exception) {
                exception.printStackTrace();//вызывается метод исключения е
            }
        }
    }
}
