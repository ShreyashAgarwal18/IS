// Assignment 7 - Information Security
// Calculate the message digest of a text using the MD5 Algorithm in Java
//
// MD5 takes any input message and produces a fixed 128-bit (16-byte) hash.
// Output is usually shown as 32 hexadecimal characters.

import java.security.MessageDigest;     // built-in Java class for hashing
import java.util.Scanner;

public class MD5 {

    // ============================================================
    // Helper: Convert byte array to a hexadecimal string
    // (each byte -> two hex digits)
    // ============================================================
    public static String toHex(byte[] bytes) {
        StringBuilder hex = new StringBuilder();
        for (byte b : bytes) {
            // 0xff & b -> convert signed byte to unsigned int (0..255)
            // %02x   -> print as 2-digit lowercase hex
            hex.append(String.format("%02x", 0xff & b));
        }
        return hex.toString();
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) throws Exception {

        // -------- Step 1: Take input from the user --------
        Scanner sc = new Scanner(System.in);
        System.out.println("=== MD5 Message Digest ===");
        System.out.print("Enter the text : ");
        String text = sc.nextLine();

        // -------- Step 2: Get an instance of MD5 hash function --------
        MessageDigest md = MessageDigest.getInstance("MD5");

        // -------- Step 3: Pass the input bytes to the hash function --------
        md.update(text.getBytes());

        // -------- Step 4: Compute the digest (128 bits = 16 bytes) --------
        byte[] digest = md.digest();

        // -------- Step 5: Convert the 16 bytes to a 32-character hex string --------
        String hash = toHex(digest);

        // -------- Step 6: Display results --------
        System.out.println("\nOriginal Text  : " + text);
        System.out.println("Length (bytes) : " + digest.length);
        System.out.println("MD5 Hash (hex) : " + hash);

        sc.close();
    }
}
