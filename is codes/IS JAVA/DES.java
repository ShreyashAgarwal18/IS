import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import java.util.Scanner;

public class DES {

    static String encrypt(String plainHex, String keyHex) throws Exception {
        byte[] plainBytes = hexToBytes(plainHex);
        byte[] keyBytes   = hexToBytes(keyHex);

        DESKeySpec desKeySpec = new DESKeySpec(keyBytes);
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey secretKey = keyFactory.generateSecret(desKeySpec);

        Cipher cipher = Cipher.getInstance("DES/ECB/NoPadding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        byte[] encryptedBytes = cipher.doFinal(plainBytes);

        return bytesToHex(encryptedBytes);
    }

    static String decrypt(String cipherHex, String keyHex) throws Exception {
        byte[] cipherBytes = hexToBytes(cipherHex);
        byte[] keyBytes    = hexToBytes(keyHex);

        DESKeySpec desKeySpec = new DESKeySpec(keyBytes);
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey secretKey = keyFactory.generateSecret(desKeySpec);

        Cipher cipher = Cipher.getInstance("DES/ECB/NoPadding");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] decryptedBytes = cipher.doFinal(cipherBytes);

        return bytesToHex(decryptedBytes);
    }

    // Helper: hex string → byte array
    static byte[] hexToBytes(String hex) {
        int len = hex.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2)
            data[i / 2] = (byte) ((Character.digit(hex.charAt(i), 16) << 4)
                                 + Character.digit(hex.charAt(i + 1), 16));
        return data;
    }

    // Helper: byte array → hex string
    static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes)
            sb.append(String.format("%02X", b));
        return sb.toString();
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        int choice;

        System.out.println("1. Encrypt");
        System.out.println("2. Decrypt");
        System.out.print("Enter choice: ");
        choice = scanner.nextInt();

        if (choice == 1) {
            System.out.print("Enter Plaintext  (16 hex chars): ");
            String plaintext = scanner.next();
            System.out.print("Enter Key        (16 hex chars): ");
            String key = scanner.next();

            String ciphertext = encrypt(plaintext, key);

            System.out.println("\nPlaintext  : " + plaintext);
            System.out.println("Key        : " + key);
            System.out.println("Ciphertext : " + ciphertext);

        } else if (choice == 2) {
            System.out.print("Enter Ciphertext (16 hex chars): ");
            String ciphertext = scanner.next();
            System.out.print("Enter Key        (16 hex chars): ");
            String key = scanner.next();

            String plaintext = decrypt(ciphertext, key);

            System.out.println("\nCiphertext : " + ciphertext);
            System.out.println("Key        : " + key);
            System.out.println("Plaintext  : " + plaintext);

        } else {
            System.out.println("Invalid choice!");
        }

        scanner.close();
    }
}