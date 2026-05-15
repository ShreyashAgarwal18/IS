import java.security.*;
import java.security.spec.*;
import javax.crypto.Cipher;
import java.math.BigInteger;
import java.util.Scanner;

public class RSA {

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter prime number p: ");
        BigInteger p = new BigInteger(scanner.next());

        System.out.print("Enter prime number q: ");
        BigInteger q = new BigInteger(scanner.next());

        BigInteger n   = p.multiply(q);
        BigInteger phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));

        System.out.println("n = p * q = " + n);
        System.out.println("phi(n) = " + phi);

        System.out.print("Enter value of e (1 < e < phi, gcd(e, phi) = 1): ");
        BigInteger e = new BigInteger(scanner.next());

        if (!e.gcd(phi).equals(BigInteger.ONE)) {
            System.out.println("Invalid e! gcd(e, phi) must be 1.");
            return;
        }

        BigInteger d = e.modInverse(phi);

        System.out.println("\nPublic Key  : (" + e + ", " + n + ")");
        System.out.println("Private Key : (" + d + ", " + n + ")");

        System.out.print("\nEnter message (number < " + n + "): ");
        BigInteger msg = new BigInteger(scanner.next());

        RSAPublicKeySpec  pubSpec  = new RSAPublicKeySpec(n, e);
        RSAPrivateKeySpec privSpec = new RSAPrivateKeySpec(n, d);

        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PublicKey  publicKey  = keyFactory.generatePublic(pubSpec);
        PrivateKey privateKey = keyFactory.generatePrivate(privSpec);

        Cipher encCipher = Cipher.getInstance("RSA/ECB/NoPadding");
        encCipher.init(Cipher.ENCRYPT_MODE, publicKey);
        byte[] encryptedBytes = encCipher.doFinal(msg.toByteArray());
        BigInteger encrypted  = new BigInteger(1, encryptedBytes);

        Cipher decCipher = Cipher.getInstance("RSA/ECB/NoPadding");
        decCipher.init(Cipher.DECRYPT_MODE, privateKey);
        byte[] decryptedBytes = decCipher.doFinal(encryptedBytes);
        BigInteger decrypted  = new BigInteger(1, decryptedBytes);

        System.out.println("\nOriginal Message  : " + msg);
        System.out.println("Encrypted Message : " + encrypted);
        System.out.println("Decrypted Message : " + decrypted);

        scanner.close();
    }
}