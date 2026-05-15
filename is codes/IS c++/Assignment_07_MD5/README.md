# Assignment 7 – MD5 Message Digest (Java)

## Problem Statement
Calculate the **message digest** of a text using the **MD5 Algorithm** in Java.

---

## 1. Aim
To compute the message digest (hash) of a given text using the **MD5 (Message Digest 5)** algorithm in Java and understand the concept of cryptographic hash functions.

---

## 2. Theory (Simple)

### What is a Message Digest?
A **message digest** (also called a **hash**) is a **fixed-size string** that represents the original data. No matter how big or small the input is, the output is always the **same length**.

> Think of it like a fingerprint of the data — unique, fixed-size, and (for good hash functions) extremely hard to forge.

### What is a Hash Function?
A **cryptographic hash function** takes any input and produces a fixed-size output with these properties:

| Property | Meaning |
|----------|---------|
| **Deterministic** | Same input → always the same output |
| **Fast** | Easy to compute |
| **One-way** | Cannot reverse the hash to get the original input |
| **Avalanche effect** | A tiny input change → completely different output |
| **Collision resistant** | Hard to find two inputs with the same hash |

### What is MD5?
**MD5 (Message Digest Algorithm 5)** is a hash function designed by **Ronald Rivest** in **1991**.

| Property | Value |
|----------|-------|
| Output size | **128 bits** (16 bytes / 32 hex chars) |
| Block size | 512 bits |
| Number of rounds | 64 (4 rounds × 16 operations) |
| Designer | Ron Rivest, MIT |
| Year | 1991 |

### How MD5 Works (High Level)
1. **Padding** – Pad the input so its length ≡ 448 (mod 512).
2. **Append length** – Append the 64-bit length of the original message.
3. **Initialize 4 buffers (A, B, C, D)** with fixed constants.
4. **Process each 512-bit block** through 4 rounds (16 operations each = 64 ops).
   Each round uses one of four non-linear functions: F, G, H, I.
5. **Final output** = A || B || C || D = 128-bit hash.

### Why Use Hash Functions?
- **Password storage** – store hashes, not passwords.
- **File integrity** – verify a file hasn't been changed.
- **Digital signatures** – sign the hash, not the whole file.
- **Data deduplication** – identify duplicate files by hash.

### Avalanche Effect Example
| Input | MD5 Hash |
|-------|----------|
| `Hello World` | `b10a8db164e0754105b7a99be72e3fe5` |
| `hello World` | `e59ff97941044f85df5297e1c302d260` |

Just lowercasing one letter completely changes the hash.

---

## 3. Algorithm (MD5 in Java)
```
1. Take input text from the user.
2. Get an instance of the MD5 hash function (java.security.MessageDigest).
3. Pass the input bytes to the hash function (md.update()).
4. Compute the 16-byte (128-bit) digest (md.digest()).
5. Convert the bytes to a 32-character hexadecimal string.
6. Display the original text and the MD5 hash.
```

---

## 4. Program File
- `MD5.java` – Java source code

### How to Run
```bash
javac MD5.java
java MD5
```
Then type any text and press Enter. The 32-character MD5 hash will be shown.

### Key Java Classes Used
| Class | Purpose |
|-------|---------|
| `java.security.MessageDigest` | Built-in class for hash algorithms (MD5, SHA-1, SHA-256, etc.) |
| `MessageDigest.getInstance("MD5")` | Returns an MD5 hash object |
| `md.update(bytes)` | Feeds input bytes to the hash function |
| `md.digest()` | Returns the final 16-byte hash |
| `String.format("%02x", b)` | Converts a byte to 2-digit hex |

---

## 5. Sample Output
```
=== MD5 Message Digest ===
Enter the text : Hello World

Original Text  : Hello World
Length (bytes) : 16
MD5 Hash (hex) : b10a8db164e0754105b7a99be72e3fe5
```

### More Test Cases
| Input        | MD5 Hash |
|--------------|----------|
| `""` (empty) | `d41d8cd98f00b204e9800998ecf8427e` |
| `abc`        | `900150983cd24fb0d6963f7d28e17f72` |
| `Hello World`| `b10a8db164e0754105b7a99be72e3fe5` |

---

## 6. Observation
1. The **output is always 128 bits (32 hex chars)**, no matter the input length.
2. The same input always produces the same hash.
3. Even a **single character change** produces a totally different hash (avalanche effect).
4. The hash is a **one-way function** — there is no way to get back the original message.
5. Java's built-in `MessageDigest` class makes MD5 very simple to use.

---

## 7. Conclusion
We successfully implemented the **MD5 message digest** algorithm in Java using the built-in `MessageDigest` class. We verified that any input produces a fixed 128-bit hash and observed the avalanche effect.

---

## 8. Difference Between Encryption and Hashing

| Encryption | Hashing |
|------------|---------|
| Two-way (can decrypt) | One-way (cannot reverse) |
| Output size = input size | Output is fixed size |
| Uses a key | No key |
| Used for confidentiality | Used for integrity |
| Examples: AES, RSA | Examples: MD5, SHA-256 |

---

## 9. Is MD5 Still Secure?

**No.** MD5 is **broken** for security purposes:
- **Collision attacks** found in 2004 (Wang et al.) — two different inputs with the same hash can be created in seconds.
- **Chosen-prefix collisions** demonstrated in 2008 (used to forge SSL certificates).

MD5 should **NOT** be used for:
- Password storage
- Digital signatures
- SSL/TLS certificates

It is still acceptable for:
- Non-security checksums (file integrity in trusted environments)
- Educational purposes
- Legacy systems

**Modern alternatives:** SHA-256, SHA-3, BLAKE2, BLAKE3.

---

## 10. Viva Questions (40)

### Basic Theory
1. **What is a message digest?**
   A **message digest** (also called a **hash**) is a **fixed-length string** that uniquely represents the original data — like a digital "fingerprint". Regardless of input size (a single character or a 1 GB file), the digest is always the same length. For MD5, the digest is exactly **128 bits (32 hex characters)**.

2. **What is a hash function?**
   A **hash function** is a mathematical function that takes **any size input** and produces a **fixed-size output**. A **cryptographic hash function** has additional properties: **deterministic** (same input → same output), **one-way** (cannot reverse), **avalanche effect** (small input change → totally different output), and **collision-resistant** (hard to find two inputs with the same hash).

3. **What is MD5?**
   **MD5 (Message Digest Algorithm 5)** is a **widely-used cryptographic hash function** that produces a **128-bit hash** from any input. It was designed in 1991 by Ron Rivest. While historically important and still used for non-security checksums, MD5 is **considered cryptographically broken** since 2004 due to practical collision attacks.

4. **Who designed MD5?**
   MD5 was designed by **Ron Rivest** at **MIT in 1991** — the same Rivest who co-invented RSA. He has designed many cryptographic algorithms (RSA, RC4, RC5, RC6, MD2, MD4, MD5, MD6). MD5 was the successor to MD4 (which had been broken).

5. **In which year was MD5 designed?**
   MD5 was designed in **1991** and published as **RFC 1321** in **April 1992** by Rivest. It quickly became the de facto standard hash function for many years (1990s–early 2000s) before being replaced by SHA-1 and then SHA-256.

6. **What is the output size of MD5?**
   MD5 produces a **128-bit (16-byte) output**, displayed as **32 hexadecimal characters** (each hex digit = 4 bits). For example, the MD5 of "Hello World" is `b10a8db164e0754105b7a99be72e3fe5` — exactly 32 hex chars long. The fixed output is the defining feature of any hash function.

7. **What is the block size of MD5?**
   MD5 processes input in **512-bit (64-byte) blocks**. Longer messages are split into 512-bit blocks; shorter ones are padded to fill a 512-bit block. Each block is processed through 64 operations updating four 32-bit buffers.

8. **How many rounds does MD5 use?**
   MD5 uses **4 rounds**, with **16 operations per round** = **64 operations total per 512-bit block**. Each round uses one of four non-linear functions (F, G, H, I) and a different constant. The final state of A, B, C, D after all blocks gives the 128-bit hash.

9. **Is MD5 reversible?**
   **No** — MD5 is a **one-way function**. You cannot recover the original input from the hash. This is by design — many different inputs can map to the same output (in theory), and the algorithm uses non-invertible operations. However, **rainbow tables** can store precomputed hashes of common inputs to "reverse" them by lookup.

10. **Is MD5 symmetric or asymmetric?**
    **Neither** — MD5 is a **hash function**, not an encryption algorithm. There's **no key involved** at all. Hashing is a third category alongside symmetric and asymmetric cryptography. Hash functions provide **integrity** (not confidentiality).

### Properties
11. **What is the avalanche effect?**
    The **avalanche effect** is the property where a **tiny change in input** (even a single bit) causes a **drastic change in the output** (typically 50% of bits flip). For example: `MD5("Hello") = 8b1a9953c4611296a827abf8c47804d7` vs `MD5("hello") = 5d41402abc4b2a76b9719d911017c592` — completely different.

12. **What is collision resistance?**
    **Collision resistance** is the **difficulty of finding two different inputs that produce the same hash**. A good hash function should make collisions infeasible to find. **MD5 is no longer collision-resistant** — collisions can be found in seconds (Wang et al. 2004). SHA-256 is still considered collision-resistant.

13. **What is preimage resistance?**
    **Preimage resistance** means it's **infeasible to find any input that produces a given hash**. In other words, given hash `h`, you cannot find `x` such that `H(x) = h`. This is the **one-way property**. MD5 is still considered preimage-resistant (although weakened); SHA-256 is strongly preimage-resistant.

14. **What is second preimage resistance?**
    **Second preimage resistance** means: given an input `x` and its hash `H(x)`, it's **infeasible to find a different input `x'` ≠ `x` such that `H(x') = H(x)`**. It's a stronger guarantee than collision resistance for a specific input. MD5's second preimage resistance is weaker than originally believed.

15. **What does "deterministic" mean?**
    **Deterministic** means the same input **always produces the same output** — there is no randomness involved. So `MD5("Hello") = b10a8db1...` every time, on every machine, in every language. This is essential for verification (you can independently compute the hash and check).

16. **Why is one-way property important?**
    The **one-way property** is critical for **password storage** — sites can store hashes instead of plain passwords. Even if the database leaks, attackers can't easily recover passwords. It's also essential for **digital signatures** (sign the hash, not the data) and **commitment schemes** (commit to a value without revealing it). However, fast hashes like MD5 can be brute-forced from common inputs.

### MD5 Algorithm
17. **What are the main steps of MD5?**
    The main steps: **(1) Padding** — pad the message so its length ≡ 448 mod 512. **(2) Append length** — append 64-bit length of original message → total = multiple of 512. **(3) Initialize 4 buffers** A, B, C, D with fixed constants. **(4) Process each 512-bit block** through 64 operations (4 rounds × 16 ops). **(5) Output** = A || B || C || D = 128 bits.

18. **What is padding in MD5?**
    **Padding** ensures the message length becomes a **multiple of 512 bits (64 bytes)**. The padding starts with a `1` bit followed by enough `0` bits to make the length **64 bits less than a multiple of 512** (so length ≡ 448 mod 512). The final 64 bits are filled with the original message length.

19. **What are the four MD5 buffers?**
    The **four 32-bit buffers** are named **A, B, C, D**, initialized to fixed constants in **little-endian**: `A=0x67452301`, `B=0xefcdab89`, `C=0x98badcfe`, `D=0x10325476`. After processing all blocks, the final values of A, B, C, D are concatenated to form the 128-bit hash.

20. **What are the four non-linear functions in MD5 rounds?**
    The four **non-linear bitwise functions** are: **F(B,C,D) = (B AND C) OR (NOT B AND D)**, **G(B,C,D) = (B AND D) OR (C AND NOT D)**, **H(B,C,D) = B XOR C XOR D**, **I(B,C,D) = C XOR (B OR NOT D)**. Each is used in one of the four rounds (16 operations each).

21. **How are blocks of MD5 processed?**
    Each 512-bit block is split into **16 32-bit words**. The block goes through **64 operations** (4 rounds × 16 ops): each operation **updates one of A, B, C, D** using the round's non-linear function, a 32-bit message word, a 32-bit constant, a left rotation, and the previous A. After 64 operations, the buffers are added to the start-of-block values to prepare for the next block.

### Java Program
22. **Which Java class is used for MD5?**
    The Java class **`java.security.MessageDigest`** provides hash function implementations including MD5, SHA-1, SHA-256, SHA-384, SHA-512. It's part of the standard JDK — no external library needed. The same class is used for all hash algorithms; you specify the algorithm by name in `getInstance()`.

23. **How do you get an MD5 instance?**
    Use **`MessageDigest md = MessageDigest.getInstance("MD5")`**. The `getInstance` method takes a string name of the algorithm and returns an instance configured for it. It can throw `NoSuchAlgorithmException` if the algorithm isn't available (very rare for standard algorithms like MD5).

24. **What does `md.update()` do?**
    `md.update(bytes)` **feeds input bytes into the hash function**. You can call it multiple times to **process input incrementally** (e.g., reading a large file in chunks). Internally, it accumulates the data into 512-bit blocks and processes them as they fill up.

25. **What does `md.digest()` return?**
    `md.digest()` **finalizes the hash and returns the 16-byte (128-bit) result** as a `byte[]`. It performs the final padding, processes the last block, and returns A || B || C || D. After calling `digest()`, the MessageDigest object is **reset and ready for a new hash** computation.

26. **How do you convert bytes to hex in Java?**
    A common idiom: **`String.format("%02x", byte & 0xff)`** — `%02x` formats as 2-digit lowercase hex, `& 0xff` converts a signed Java byte (-128 to 127) to an unsigned int (0 to 255). Loop over the byte array, append each hex digit to a `StringBuilder`. The result is a 32-character hex string.

27. **Why convert bytes to hex?**
    Raw bytes contain **non-printable characters** (control codes, binary data) that **can't be displayed or copy-pasted reliably**. **Hex encoding** converts every byte to **two readable characters (0-9, a-f)** — making the hash easy to print, store in databases, or share in URLs. Alternative: **Base64** (more compact but uses + / = symbols).

28. **What is the size of the digest array returned by `md.digest()`?**
    For MD5, `md.digest()` returns a **`byte[16]`** — exactly 16 bytes = 128 bits. For SHA-1, it would be `byte[20]`; for SHA-256, `byte[32]`. The size is determined by the algorithm.

### Hash vs Encryption
29. **Difference between hashing and encryption?**
    **Hashing**: **one-way**, **fixed-size output**, **no key**, used for **integrity verification**. **Encryption**: **two-way (reversible)**, **output size ≈ input size**, **uses a key**, used for **confidentiality**. Hashing makes a fingerprint; encryption makes a secret. They serve different purposes and are often used together.

30. **Can MD5 be used for password storage?**
    **No, NOT safely** — MD5 is **too fast** (modern GPUs can compute billions of MD5 hashes per second), making it easy to brute-force passwords from leaked hashes. Also, MD5 has known collision attacks. **Use specialized password hashing algorithms** like **bcrypt, scrypt, or Argon2** which are designed to be slow and memory-intensive.

31. **What is salting?**
    **Salting** is the practice of **adding a random unique value (the "salt") to each password before hashing**. So instead of `H(password)`, you store `H(salt + password)` and the salt. This prevents **rainbow table attacks** (precomputed hash tables) and ensures two users with the same password get different hashes. Salts should be **unique per password** and at least 16 bytes random.

### Security and Comparisons
32. **Is MD5 secure today?**
    **No** — MD5 is **considered cryptographically broken** for security purposes. Collision attacks have been demonstrated since 2004 (Wang et al.), and **chosen-prefix collisions** have been used to **forge SSL certificates** (2008, Sotirov et al.) and create **fake malware signatures**. Use **SHA-256 or SHA-3** for security-critical applications.

33. **What is a collision attack?**
    A **collision attack** is when an attacker finds **two different inputs that produce the same hash output**. For MD5, this is now trivial — collisions can be found in **seconds** on a normal computer. The danger: an attacker can create two documents with the same hash (e.g., a benign and a malicious version) and use the hash signature to legitimize the malicious one.

34. **When was MD5 first broken?**
    MD5 was **first practically broken in 2004** by **Xiaoyun Wang and her team** at Shandong University, who showed how to find collisions in just **one hour**. By 2008, **chosen-prefix collisions** were demonstrated (creating two distinct meaningful documents with the same MD5). MD5 has been deprecated for security purposes since.

35. **What hash functions are recommended today?**
    Modern recommended hash functions: **SHA-256 / SHA-512** (SHA-2 family — widely deployed, secure), **SHA-3 / Keccak** (newer, different design — won the SHA-3 competition), **BLAKE2** (faster than MD5 but secure), **BLAKE3** (even faster, parallelizable). For passwords specifically: **bcrypt, Argon2, scrypt**.

36. **What is the output size of SHA-256?**
    **SHA-256** produces a **256-bit (32-byte) output**, displayed as **64 hex characters**. It's the most widely-used member of the **SHA-2 family**. Used in **Bitcoin, TLS certificates, code signing**, and many other security-critical applications.

37. **What is SHA-1?**
    **SHA-1** is a hash function producing a **160-bit (20-byte) output**, designed by NSA and standardized in 1995. It was widely used until **practical collisions were demonstrated in 2017** (Google's "SHAttered" attack). **SHA-1 is now deprecated** for security; use SHA-256 or higher.

38. **What is HMAC?**
    **HMAC (Hash-based Message Authentication Code)** is a construction that **combines a hash function with a secret key** to produce a **MAC (Message Authentication Code)** — providing both integrity and authenticity. It's defined as `HMAC(K, m) = H((K' XOR opad) || H((K' XOR ipad) || m))`. Used in TLS, IPsec, JWT, AWS request signing.

### Applications
39. **Where is MD5 still used?**
    MD5 is still used (controversially) for: **(1) Non-security checksums** — verifying file downloads against accidental corruption (not malicious modification). **(2) Legacy systems** — older protocols and software that haven't migrated. **(3) Quick hash-based deduplication** in non-adversarial settings. **(4) Education** — teaching cryptographic hash concepts. **It should NOT be used for new security applications.**

40. **Why are hash functions important?**
    Hash functions are critical for: **(1) Data integrity** (verify data hasn't been modified), **(2) Password storage** (store hashes, not plaintext), **(3) Digital signatures** (sign the hash, not the entire document — much faster), **(4) Blockchain** (Bitcoin uses SHA-256 for block hashes), **(5) Deduplication** (identify duplicate files by hash), **(6) Indexing in hash tables**, **(7) Commitment schemes** in cryptographic protocols.

---

## 11. References
- William Stallings – *Cryptography and Network Security*
- Bruce Schneier – *Applied Cryptography*
- RFC 1321 – *The MD5 Message-Digest Algorithm* (Rivest, 1992)
- Java Documentation – `java.security.MessageDigest`
- Atul Kahate – *Cryptography and Network Security*
