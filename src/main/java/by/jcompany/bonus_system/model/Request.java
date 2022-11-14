package by.jcompany.bonus_system.model;

import com.google.gson.Gson;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.io.Serializable;

@NoArgsConstructor
@Getter
@Setter
public class Request implements Serializable {
    private String requestType;
    private String requestString;
    
    public Request(String requestType, Object requestObject) {
        this.requestType = requestType;
        Gson gson = new Gson();
        this.requestString = gson.toJson(requestObject);
    }
}