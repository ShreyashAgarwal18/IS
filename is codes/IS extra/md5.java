import java.security.MessageDigest;
import java.util.*;

public class md5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter text: ");
        String text = sc.nextLine();

        try{
                MessageDigest md = MessageDigest.getInstance("MD5");

                byte[] messageDigest = md.digest(text.getBytes());

                StringBuilder sb = new StringBuilder();

                for(byte b : messageDigest){
                    sb.append(String.format("%02x", b));
                }

                System.out.println("MD5 message digest: " + sb);
        }
        catch(Exception e){
            System.out.println("Error");
        }
    }
}
/*
Enter Text: Hello
MD5 Message Digest: 8b1a9953c4611296a827abf8c47804d7
*/