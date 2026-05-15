# Assignment 1 – AND / XOR Operation on a String

## Problem Statement
Write a C++ program that contains a string "Hello World". Perform **AND** and **XOR** operation with **127** on each character of the string and display the result.

---

## 1. Aim
To learn how bitwise **AND** and **XOR** operations work on characters and to understand their use in cryptography.

---

## 2. Theory (Simple)

### What is a Character?
Every character (like `H`, `e`, `l`) is stored in the computer as a number called **ASCII value**.
For example:
- `H` = 72
- `e` = 101
- `l` = 108
- `o` = 111
- space = 32

These numbers are stored in **binary** (0s and 1s) using 8 bits.
Example: `H` = 72 = `01001000`

### Bitwise Operators
A bitwise operator works on each **bit** of a number.

#### AND ( & )
Result is 1 only if **both** bits are 1.

| A | B | A & B |
|---|---|-------|
| 0 | 0 |   0   |
| 0 | 1 |   0   |
| 1 | 0 |   0   |
| 1 | 1 |   1   |

#### XOR ( ^ )
Result is 1 only if **bits are different**.

| A | B | A ^ B |
|---|---|-------|
| 0 | 0 |   0   |
| 0 | 1 |   1   |
| 1 | 0 |   1   |
| 1 | 1 |   0   |

### Why 127?
- 127 in binary = `01111111`
- It has 7 ones and the highest bit is 0.
- **AND with 127** → keeps the last 7 bits same, clears the 8th bit.
- **XOR with 127** → flips the last 7 bits.

### Example: Character `H`
```
H   = 72  = 0 1 0 0 1 0 0 0
127       = 0 1 1 1 1 1 1 1
------------------------------ AND
Result    = 0 1 0 0 1 0 0 0  =  72  =  'H'

H   = 72  = 0 1 0 0 1 0 0 0
127       = 0 1 1 1 1 1 1 1
------------------------------ XOR
Result    = 0 0 1 1 0 1 1 1  =  55  =  '7'
```

### Important Property of XOR
If we XOR a value with the same key **twice**, we get the original value back.
That is why **XOR is used in encryption** — the same key encrypts and decrypts.

---

## 3. Algorithm
```
1. Start
2. Take the string str = "Hello World"
3. Set key = 127
4. For each character in str:
       a. Calculate result = character AND 127
       b. Display the result
5. For each character in str:
       a. Calculate result = character XOR 127
       b. Display the result
6. Stop
```

---

## 4. Program File
- `and_xor.cpp` – C++ source code

### How to Run
```bash
g++ and_xor.cpp -o and_xor
./and_xor
```

---

## 5. Sample Output
```
Original String : Hello World
Key             : 127

----- AND Operation with 127 -----
H & 127 = 72  (H)
e & 127 = 101 (e)
l & 127 = 108 (l)
l & 127 = 108 (l)
o & 127 = 111 (o)
  & 127 = 32  ( )
W & 127 = 87  (W)
o & 127 = 111 (o)
r & 127 = 114 (r)
l & 127 = 108 (l)
d & 127 = 100 (d)

----- XOR Operation with 127 -----
H ^ 127 = 55  (7)
e ^ 127 = 26
l ^ 127 = 19
...
```

---

## 6. Observation
1. After **AND with 127**, the string remains the **same** ("Hello World"), because all characters are below 128.
2. After **XOR with 127**, the string changes into **different (mostly unprintable) characters** — this is like simple encryption.
3. If we XOR the result again with 127, we get back "Hello World" — proves XOR is **reversible**.

---

## 7. Conclusion
We successfully performed AND and XOR operations with 127 on the string "Hello World". We learned that **AND** is used to mask bits and **XOR** is widely used in cryptography because it is reversible.

---

## 8. Where XOR is Used in Real Life
- One-Time Pad (OTP)
- DES, AES encryption algorithms
- RC4 stream cipher
- Parity bit checking
- Swapping two numbers without a temp variable

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is Information Security?**
   **Information Security (InfoSec)** is the practice of **protecting information and information systems** from unauthorized access, use, disclosure, disruption, modification, or destruction. Its goals are summarized in the **CIA triad** — Confidentiality, Integrity, and Availability. It involves technical controls (encryption, firewalls), administrative controls (policies), and physical controls (locks, biometrics).

2. **What is the CIA triad?**
   The CIA triad is the foundation of information security: **Confidentiality** ensures data is accessible only to authorized users (achieved via encryption and access control); **Integrity** ensures data is not tampered with (achieved via hashing and digital signatures); **Availability** ensures data and services are accessible when needed (achieved via redundancy, backups, and DDoS protection). All security mechanisms ultimately serve one or more of these three goals.

3. **What is plaintext?**
   **Plaintext** is the **original readable message** before any encryption is applied. It can be a text, file, image, or any data in its natural form. For example, "Hello World" is plaintext that anyone can read directly.

4. **What is ciphertext?**
   **Ciphertext** is the **encrypted (unreadable) version** of the plaintext, produced by applying an encryption algorithm with a key. Without the key, ciphertext should appear as random data and reveal nothing about the original message. For example, "Hello World" XORed with 127 produces a ciphertext that's mostly unreadable control characters.

5. **What is encryption?**
   **Encryption** is the process of **converting plaintext into ciphertext** using a cryptographic algorithm and a key. Its purpose is to **protect confidentiality** — only someone with the correct key can decrypt and read the message. Examples include AES, DES, RSA, and our simple XOR cipher.

6. **What is decryption?**
   **Decryption** is the **reverse process of encryption** — converting ciphertext back into the original plaintext using the appropriate key. In symmetric cryptography (like XOR or AES), the same key encrypts and decrypts. In asymmetric (like RSA), a different key is used.

7. **What is a key in cryptography?**
   A **key** is a **secret value** used by a cryptographic algorithm to control encryption and decryption. Without the key, an attacker shouldn't be able to read the ciphertext. Keys can be a number, a string, or a sequence of bits — for example, our program uses **127** as the key for AND/XOR operations.

8. **What is symmetric encryption?**
   **Symmetric encryption** uses the **same key for both encryption and decryption** — both sender and receiver must share this key securely. It's typically **fast** and used for bulk data encryption. Examples: **AES, DES, 3DES, RC4, ChaCha20**. The XOR-with-127 in this program is a primitive symmetric cipher.

9. **What is asymmetric encryption?**
   **Asymmetric encryption** uses **two different keys** — a **public key** (shared with everyone) for encryption and a **private key** (kept secret) for decryption. It solves the **key distribution problem** of symmetric encryption. Examples: **RSA, ECC, Diffie-Hellman**. It's slower than symmetric, so often used to securely exchange a symmetric key.

10. **What is cryptography?**
    **Cryptography** is the **science of securing information** using mathematical techniques — converting plaintext into ciphertext (encryption) and back (decryption). It also covers integrity (hashing), authentication (signatures, MACs), and key exchange protocols. Modern cryptography relies on computational hardness assumptions like factoring large numbers.

### Bitwise Operators
11. **List bitwise operators in C++.**
    The bitwise operators in C++ are: **`&` (AND)**, **`|` (OR)**, **`^` (XOR)**, **`~` (NOT/complement)**, **`<<` (left shift)**, and **`>>` (right shift)**. These operate on the **individual bits** of integer types — useful for low-level operations like masking, flag manipulation, and cryptography.

12. **What is the AND operator?**
    The AND operator **`&`** produces a 1 in each bit position only if **both** input bits are 1, otherwise 0. It's commonly used for **masking** — to clear specific bits or extract a subset of bits from a number. Example: `0b11010110 & 0b00001111 = 0b00000110` (extracts the lower 4 bits).

13. **What is the OR operator?**
    The OR operator **`|`** produces a 1 in each bit position if **at least one** input bit is 1. It's used for **setting specific bits** without disturbing others. Example: `0b00001100 | 0b10000000 = 0b10001100` (sets the highest bit).

14. **What is the XOR operator?**
    The XOR operator **`^`** (Exclusive OR) produces a 1 only when the two bits are **different**. It's used in cryptography (one-time pad, AES round operations), parity checking, and toggling bits. Crucially, XOR is **its own inverse**: `(A^B)^B = A`, which is why it's central to symmetric encryption.

15. **What is the NOT operator?**
    The NOT operator **`~`** (also called the **bitwise complement**) inverts every bit — 0 becomes 1 and vice versa. Example: `~0b00001111 = 0b11110000`. It's used in masking operations to create inverted masks.

16. **Truth table of AND?**
    The truth table of AND is: **`0 AND 0 = 0`**, **`0 AND 1 = 0`**, **`1 AND 0 = 0`**, **`1 AND 1 = 1`**. So output is 1 only when both inputs are 1 — like a logical "and" condition.

17. **Truth table of XOR?**
    The truth table of XOR is: **`0 XOR 0 = 0`**, **`0 XOR 1 = 1`**, **`1 XOR 0 = 1`**, **`1 XOR 1 = 0`**. Output is 1 when exactly one of the inputs is 1 — i.e., the inputs differ. This "difference detector" property makes XOR useful for comparison and toggling.

18. **What is `A ^ A`?**
    `A ^ A = 0` for any value A — because every bit of A is identical to itself, so XOR produces 0. This property is used in algorithms like **finding a unique element** in an array where everything else appears twice, or **clearing a register** efficiently.

19. **What is `A ^ 0`?**
    `A ^ 0 = A` for any value A — because XOR with 0 doesn't change any bit. This is the **identity element** of the XOR operation. Combined with `A^A=0`, these properties define XOR as a perfect reversible operation.

20. **Is XOR commutative?**
    Yes — XOR is **commutative** (`A ^ B = B ^ A`) and also **associative** (`(A ^ B) ^ C = A ^ (B ^ C)`). These properties make XOR ideal for building reversible cryptographic primitives — the order of XOR operations doesn't matter for the final result.

### About this Program
21. **Why did we use 127?**
    127 in binary is **`01111111`** — the **largest 7-bit value** with the MSB (8th bit) being 0. **AND with 127** clears the 8th bit (useful to convert extended ASCII to standard ASCII). **XOR with 127** flips the lower 7 bits — a simple form of encryption that scrambles printable characters into mostly unprintable ones.

22. **What is 127 in binary?**
    127 in binary is **`01111111`** — seven 1s with the most significant bit (MSB) being 0. It is `2^7 - 1`, the maximum 7-bit unsigned integer. This pattern of all-1s in the lower 7 bits makes it useful as a 7-bit mask.

23. **What is 127 in hex?**
    127 in hexadecimal is **`0x7F`** — the largest 7-bit value (0x7F = 127 decimal). Hex is convenient for representing bytes because each hex digit corresponds to 4 binary bits. So `0x7F` = `0111 1111` in binary.

24. **What is the ASCII value of `H`?**
    The ASCII value of 'H' is **72** (decimal), which is **`0x48`** in hex or **`01001000`** in binary. ASCII is a 7-bit encoding where uppercase A=65, B=66, ..., Z=90 — so H is the 8th letter, A+7 = 65+7 = 72.

25. **What is the ASCII value of space?**
    The ASCII value of space is **32** (decimal), or **`0x20`** in hex. It's the **first printable character** in ASCII (codes 0–31 are control characters like newline, tab, etc.).

26. **Size of `char` in C++?**
    A `char` in C++ is **1 byte (8 bits)** — guaranteed by the C++ standard. It can hold values from -128 to 127 (signed) or 0 to 255 (unsigned). This makes it perfect for storing single ASCII characters or raw bytes for encryption.

27. **What happens after AND with 127 on "Hello World"?**
    The string **remains unchanged** as "Hello World" — because every character in standard ASCII (printable English) has values **below 128**, so the 8th bit is already 0. ANDing with 127 (which has the 8th bit as 0) clears that bit but doesn't affect the lower 7 bits, leaving the value the same.

28. **What happens after XOR with 127?**
    Each character becomes a **different character** because the lower 7 bits get flipped. For example, 'H' (72 = `01001000`) becomes (`00110111` = 55 = '7'). Most XOR results land in the **non-printable control character range** (0–31), so they look like garbage in the terminal.

29. **Is AND reversible?**
    **No** — AND is **not reversible** in general. AND with 0 destroys information (clears the bit), so you cannot recover the original value. For example, `5 AND 0 = 0`, but you can't recover 5 from 0 alone. AND is used for masking/clearing, not encryption.

30. **Is XOR reversible?**
    Yes — XOR is **perfectly reversible**: XORing the result with the same key recovers the original. Mathematically: `(A ^ B) ^ B = A ^ (B ^ B) = A ^ 0 = A`. This involutory property is the foundation of all symmetric XOR-based cryptography (One-Time Pad, AES round functions, etc.).

31. **How to decrypt the XOR output?**
    To decrypt, simply **XOR each ciphertext character again with the same key (127)**. Because of XOR's reversible property, this returns the original character. This is why **the same algorithm encrypts and decrypts** in XOR-based ciphers — only the key matters.

32. **Why do some XOR outputs look strange in the terminal?**
    Because XOR with 127 may produce values **below ASCII 32**, which are **control characters** (newline, tab, bell, escape, etc.) that the terminal cannot render visually. They may show as `?`, blank, or trigger terminal effects. This is a display limitation, not a problem with the encryption.

### Cryptography
33. **Name a cipher that uses XOR.**
    XOR is at the heart of many ciphers: **One-Time Pad** (XOR with a random equal-length key), **RC4** (XOR with a generated keystream), **ChaCha20** (XOR with keystream), **AES** (XOR in AddRoundKey step), **DES** (XOR in the Feistel function), and **Stream ciphers** in general. XOR is the most fundamental cryptographic operation.

34. **What is One-Time Pad?**
    The **One-Time Pad (OTP)** is a cipher where plaintext is **XORed with a truly random key of equal length** that is used **only once**. It is the only cipher that is **provably unbreakable** (perfect secrecy, proved by Shannon in 1949). However, it requires distributing huge random keys securely, making it impractical for most uses.

35. **What is a stream cipher?**
    A **stream cipher** encrypts data **one bit or byte at a time** by XORing it with a pseudo-random **keystream** generated from a secret key. Examples: **RC4, ChaCha20, A5/1**. They're typically faster than block ciphers and used in TLS, WPA2 (RC4 in older versions), and mobile communications.

36. **What is a block cipher?**
    A **block cipher** encrypts data in **fixed-size blocks** (e.g., 64 bits for DES, 128 bits for AES) using complex multi-round operations. It's used with **modes of operation** (ECB, CBC, CTR, GCM) to encrypt longer messages. Examples: **AES, DES, 3DES, Blowfish**.

37. **Is XOR-with-127 a strong cipher?**
    **No** — it's extremely weak. The key is only **1 byte (8 bits)**, so brute force takes at most 256 tries. Worse, since XOR preserves character frequencies, **frequency analysis** would crack it instantly. It's an educational example, not a real cipher.

38. **How to make this XOR cipher stronger?**
    To make it stronger: **(1)** use a **long random key** (ideally as long as the plaintext, like One-Time Pad); **(2)** never reuse the key; **(3)** use **multiple rounds** of substitution and permutation (as in AES); or **(4)** use **proven modern ciphers** like AES-GCM or ChaCha20-Poly1305 instead.

39. **What is cryptanalysis?**
    **Cryptanalysis** is the **study of analyzing and breaking** cryptographic algorithms — finding ways to recover plaintext or keys without knowing the secret. Techniques include **brute force**, **frequency analysis**, **differential cryptanalysis**, **linear cryptanalysis**, and **side-channel attacks** (timing, power consumption).

40. **Other uses of XOR besides cryptography?**
    XOR is used in many areas beyond crypto: **Parity bit checking** (error detection), **CRC (Cyclic Redundancy Check)**, **RAID storage** (RAID-5 uses XOR for redundancy), **hashing** (in mixing functions), **graphics** (sprite blitting), **toggling flags**, and the famous trick of **swapping two variables without a temporary**: `a^=b; b^=a; a^=b;`.

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Atul Kahate – *Cryptography and Network Security*
- ASCII Table – www.asciitable.com
