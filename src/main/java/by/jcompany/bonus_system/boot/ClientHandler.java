package by.jcompany.bonus_system.boot;

import by.jcompany.bonus_system.model.Request;
import by.jcompany.bonus_system.model.Response;
import by.jcompany.bonus_system.entity.User;
import com.google.gson.Gson;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

class ClientHandler implements Runnable {
    private final int clientNumber;
    private final Socket socket;
    private final ObjectInputStream objectInputStream;
    private final ObjectOutputStream objectOutputStream;
    
    private final Gson gson = new Gson();
    
    ClientHandler(Socket clientSocket, int clientNumber) throws IOException {
        this.clientNumber = clientNumber;
        System.out.println("connection established with client #" + clientNumber + "...");
        
        socket = clientSocket;
        objectInputStream = new ObjectInputStream(socket.getInputStream());
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
    }
    
    @Override
    public void run() {
        try {
            Response serverResponse = null;
            Request clientRequest;
            
            do {
                try {
                    clientRequest = (Request) objectInputStream.readObject();
                    
                    String requestType = clientRequest.getRequestType();
                    String requestString = clientRequest.getRequestString();
                    
                    System.out.println("message received: '" +
                        requestType + " " +
                        requestString + "'");
    
                    
                    if (requestType.equals("QUIT")) {
                        break;
                    }
                    
                    switch (requestType) {
                        case "CREATE_USER" -> {
                            User user = gson.fromJson(requestString, User.class);
                            ClientFunctions.createUser(user);
                            serverResponse = new Response("OK", "User created");
                        }
                        case "READ_ALL_USERS" -> {
                        }
                    }
                } catch (IOException exception) {
                    serverResponse = new Response("ERROR", "Server file invalid!");
                    System.out.println(serverResponse);
                }
                
                objectOutputStream.writeObject(serverResponse);
            } while (true);
        } catch (Exception exception) {
            exception.printStackTrace();
        } finally {
            try {
                assert objectInputStream != null;
                objectInputStream.close();
                assert objectOutputStream != null;
                objectOutputStream.close();
                socket.close();
                
                System.out.println("connection closed with client #" + clientNumber + "...");
            } catch (Exception exception) {
                exception.printStackTrace();
            }
        }
    }
}