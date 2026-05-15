public class MD5Own {

    static int[] s = {
        7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
        5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
        4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
        6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
    };

    static int[] K = new int[64];

    static {
        for (int i = 0; i < 64; i++) {
            K[i] = (int)(long)((1L << 32) * Math.abs(Math.sin(i + 1)));
        }
    }

    static int leftRotate(int x, int c) {
        return (x << c) | (x >>> (32 - c));
    }

    static String md5(String input) {
        byte[] msg = input.getBytes();
        int originalLen = msg.length;
        int newLen = originalLen + 1;

        while ((newLen % 64) != 56) {
            newLen++;
        }

        byte[] padded = new byte[newLen + 8];

        for (int i = 0; i < originalLen; i++) {
            padded[i] = msg[i];
        }

        padded[originalLen] = (byte)0x80;

        long bitLen = (long)originalLen * 8;

        for (int i = 0; i < 8; i++) {
            padded[newLen + i] = (byte)(bitLen >>> (8 * i));
        }

        int a0 = 0x67452301;
        int b0 = 0xEFCDAB89;
        int c0 = 0x98BADCFE;
        int d0 = 0x10325476;

        for (int offset = 0; offset < padded.length; offset += 64) {

            int[] M = new int[16];

            for (int i = 0; i < 16; i++) {
                int index = offset + i * 4;
                M[i] = ((padded[index] & 0xff)) |
                       ((padded[index + 1] & 0xff) << 8) |
                       ((padded[index + 2] & 0xff) << 16) |
                       ((padded[index + 3] & 0xff) << 24);
            }

            int A = a0, B = b0, C = c0, D = d0;

            for (int i = 0; i < 64; i++) {
                int F = 0, g = 0;

                if (i < 16) {
                    F = (B & C) | (~B & D);
                    g = i;
                } else if (i < 32) {
                    F = (D & B) | (~D & C);
                    g = (5 * i + 1) % 16;
                } else if (i < 48) {
                    F = B ^ C ^ D;
                    g = (3 * i + 5) % 16;
                } else {
                    F = C ^ (B | ~D);
                    g = (7 * i) % 16;
                }

                int temp = D;
                D = C;
                C = B;
                B = B + leftRotate(A + F + K[i] + M[g], s[i]);
                A = temp;
            }

            a0 += A;
            b0 += B;
            c0 += C;
            d0 += D;
        }

        return toHex(a0) + toHex(b0) + toHex(c0) + toHex(d0);
    }

    static String toHex(int n) {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < 4; i++) {
            String hex = Integer.toHexString((n >>> (8 * i)) & 0xff);
            if (hex.length() == 1) sb.append("0");
            sb.append(hex);
        }

        return sb.toString().toUpperCase();
    }

    public static void main(String[] args) {
        String input = "Hello World";
        String hash = md5(input);

        System.out.println("Input: " + input);
        System.out.println("MD5 Digest: " + hash);
    }
}
