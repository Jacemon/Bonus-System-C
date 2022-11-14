package by.jcompany.bonus_system.util;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class HashManager {
    public static byte[] getHash(String stringForHash) {
        MessageDigest digest;
        byte[] hash = null;
        try {
            digest = MessageDigest.getInstance("MD5");
            digest.reset();
            hash = digest.digest(stringForHash.getBytes(StandardCharsets.UTF_8));
        } catch (NoSuchAlgorithmException exception) {
            exception.printStackTrace();
        }
        return hash;
    }
}
