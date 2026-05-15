import java.util.Scanner;

public class TranspositionCipher {

    static String encrypt(String text, int key) {
        String cipher = "";
        int col = key;
        int row = text.length() / col;

        if (text.length() % col != 0)
            row++;

        while (text.length() < row * col)
            text += 'x';

        for (int j = 0; j < col; j++) {
            for (int i = j; i < row * col; i += col) {
                cipher += text.charAt(i);
            }
        }

        return cipher;
    }

    static String decrypt(String cipher, int key) {
        String plain = "";
        int col = key;
        int row = cipher.length() / col;

        char[][] grid = new char[20][20];
        int k = 0;

        for (int j = 0; j < col; j++) {
            for (int i = 0; i < row; i++) {
                grid[i][j] = cipher.charAt(k);
                k++;
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                plain += grid[i][j];
            }
        }

        return plain;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice, key;
        String text;

        System.out.println("   Transposition Cipher Program      ");

        System.out.print("\nEnter the key (number of columns): ");
        key = scanner.nextInt();
        scanner.nextLine();

        System.out.println("\n1. Encrypt");
        System.out.println("2. Decrypt");
        System.out.print("Enter choice: ");
        choice = scanner.nextInt();
        scanner.nextLine();

        if (choice == 1) {
            System.out.print("Enter plaintext: ");
            text = scanner.nextLine();

            String noSpace = "";
            for (int i = 0; i < text.length(); i++) {
                if (text.charAt(i) != ' ')
                    noSpace += text.charAt(i);
            }

            String result = encrypt(noSpace, key);
            System.out.println("\nPlaintext  : " + noSpace);
            System.out.println("Key        : " + key);
            System.out.println("Ciphertext : " + result);

        } else if (choice == 2) {
            System.out.print("Enter ciphertext: ");
            text = scanner.nextLine();

            String result = decrypt(text, key);
            System.out.println("\nCiphertext : " + text);
            System.out.println("Key        : " + key);
            System.out.println("Plaintext  : " + result);

        } else {
            System.out.println("Invalid choice!");
        }

        scanner.close();
    }
}