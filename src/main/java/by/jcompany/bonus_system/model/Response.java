package by.jcompany.bonus_system.model;

import com.google.gson.Gson;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.io.Serializable;

@NoArgsConstructor
@Getter
@Setter
public class Response implements Serializable {
    public String responseStatus;
    public String responseString;
    
    public Response(String responseStatus, Object responseObject) {
        this.responseStatus = responseStatus;
        Gson gson = new Gson();
        this.responseString = gson.toJson(responseObject);
    }
}