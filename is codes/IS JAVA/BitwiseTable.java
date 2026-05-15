import java.util.Scanner;

public class BitwiseTable {

    public static void main(String[] args) {
        String str = "Hello World";
        int mask = 127;

        System.out.printf("%-10s%-8s%-11s%s%n", "Char", "ASCII", "AND(127)", "XOR(127)");
        System.out.println("-".repeat(35));

        for (char c : str.toCharArray()) {
            String label = (c == ' ') ? "(space)" : String.valueOf(c);
            System.out.printf("%-10s%-8d%-11d%d%n", label, (int)c, c & mask, c ^ mask);
        }
    }
}