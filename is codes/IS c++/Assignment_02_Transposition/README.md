# Assignment 2 – Transposition Cipher (Encryption & Decryption)

## Problem Statement
Write a C++ program to perform **Encryption** and **Decryption** using the **Transposition Technique**.

---

## 1. Aim
To learn how the **Columnar Transposition Cipher** works and implement encryption and decryption using it in C++.

---

## 2. Theory (Simple)

### What is a Transposition Cipher?
A **Transposition Cipher** is a type of cipher where the **letters of the message are rearranged (shuffled)** in a specific order. The original letters are **not changed**, only their **positions** are changed.

> Example: `HELLO` → `HLOEL` (same letters, different order)

This is **different from substitution ciphers** (like Caesar Cipher) where letters are **replaced** by other letters.

### Types of Transposition Cipher
1. **Rail Fence Cipher** – Letters are written in a zig-zag pattern.
2. **Columnar Transposition Cipher** – Letters are written in rows and read column by column. ← *(used in this program)*

### Columnar Transposition – Step by Step
**Plaintext:** `HelloWorld`
**Key (columns):** 4

**Step 1 – Write message row by row in a matrix of 4 columns:**
```
H  e  l  l
o  W  o  r
l  d  x  x      (x = padding to fill the matrix)
```

**Step 2 – Read the matrix column by column to get the ciphertext:**
```
Column 1: H o l
Column 2: e W d
Column 3: l o x
Column 4: l r x
```
**Ciphertext:** `HolEWdloxlrx`

**Step 3 – Decryption** is the reverse:
- Write ciphertext column by column into the matrix.
- Read row by row to get back the plaintext.

### Why use Transposition Cipher?
- Hides the message by changing letter order.
- Letter frequency is preserved, so it can be combined with substitution for stronger encryption.
- Used as a building block in modern algorithms like DES (Permutation step).

---

## 3. Algorithm

### Encryption
```
1. Start
2. Read message and key (number of columns)
3. Calculate rows = ceil(length / key)
4. Fill the matrix row by row with message characters
   (use 'x' for empty cells)
5. Read the matrix column by column to form the ciphertext
6. Display ciphertext
7. Stop
```

### Decryption
```
1. Start
2. Read ciphertext
3. Fill the matrix column by column
4. Read the matrix row by row to get the plaintext
5. Display plaintext
6. Stop
```

---

## 4. Program File
- `transposition.cpp` – C++ source code

### How to Run
```bash
g++ transposition.cpp -o transposition
./transposition
```

---

## 5. Sample Output
```
Enter the message : HelloWorld
Enter the key (number of columns) : 4

Matrix (filled row-wise):
H e l l
o W o r
l d x x

Encrypted Message : HolEWdloxlrx
Decrypted Message : HelloWorldxx
```

---

## 6. Observation
1. The encrypted message contains the **same letters** as the original — only the **order** is different.
2. Padding character `x` is added to fill the last row of the matrix.
3. Decryption works perfectly when the **same key** (number of columns) is used.
4. Without knowing the key, it is hard to read the message.

---

## 7. Conclusion
We successfully implemented **Encryption and Decryption** using the **Columnar Transposition Cipher** in C++. We learned that transposition rearranges letters using a key, and the same key is required for decryption.

---

## 8. Advantages and Disadvantages

### Advantages
- Simple and easy to implement.
- Hides the structure of the message.
- Can be combined with substitution for stronger encryption.

### Disadvantages
- Letter frequency is preserved → can be broken using **frequency analysis**.
- Weak against **brute-force** attacks (small key space).
- Padding can give hints to attackers.

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is a cipher?**
   A **cipher** is a **method or algorithm** for converting plaintext into ciphertext (encryption) and back (decryption). A cipher uses a key to control the transformation. Classical ciphers (Caesar, Vigenère, Transposition) are simple; modern ciphers (AES, RSA) are mathematically complex and computer-based.

2. **What is plaintext?**
   **Plaintext** is the **original readable message** before any encryption is applied. It can be any data — text, image, file — in its natural unencrypted form. Anyone can read plaintext directly without a key.

3. **What is ciphertext?**
   **Ciphertext** is the **encrypted, unreadable form** of the plaintext, produced by applying an encryption algorithm with a key. Without the key, ciphertext should appear as random data and reveal nothing about the original. For example, "HelloWorld" with columnar transposition becomes "HoleWdloxlrx".

4. **What is encryption?**
   **Encryption** is the process of **converting plaintext into ciphertext** using a cryptographic algorithm and a key. The goal is **confidentiality** — only authorized parties with the correct key can decrypt and read the original message. Examples: AES, DES, RSA, our columnar transposition.

5. **What is decryption?**
   **Decryption** is the **reverse of encryption** — converting ciphertext back into the original plaintext using the appropriate key. In symmetric ciphers (like our transposition), the same key is used for both. In asymmetric ciphers, a different key (private) is used.

6. **What is a key?**
   A **key** is a **secret value** that controls the encryption/decryption process. Without the right key, an attacker cannot read the ciphertext (in a well-designed cipher). For our transposition cipher, the key is the **number of columns** (e.g., 4) used in the matrix.

7. **What are the two main types of classical ciphers?**
   The two main types are **Substitution ciphers** (which replace letters with other letters, like Caesar cipher: A→D, B→E, etc.) and **Transposition ciphers** (which rearrange letters without changing them, like our columnar transposition). They form the basis of all classical cryptography.

8. **What is a Substitution cipher?**
   A **Substitution cipher** **replaces each letter of the plaintext with a different letter** (or symbol). The substitution can be simple (Caesar shift) or complex (Vigenère, polyalphabetic). The original letters are **changed**, but their positions are preserved.

9. **What is a Transposition cipher?**
   A **Transposition cipher** **rearranges (shuffles) the positions of letters** without changing them. The original letters all remain in the ciphertext but in a different order. Examples: **Rail Fence**, **Columnar Transposition**, **Route Cipher**, **Double Transposition**.

10. **Difference between substitution and transposition?**
    **Substitution** **changes the letters** themselves (HELLO → KHOOR with Caesar +3) but keeps positions. **Transposition** **changes the positions** of letters but keeps the letters themselves (HELLO → HLOEL with rearrangement). Modern ciphers (AES, DES) combine both for stronger security.

### Transposition Cipher Specific
11. **Name some types of transposition ciphers.**
    Common types include: **Rail Fence Cipher** (zig-zag pattern across rails), **Columnar Transposition** (rows-then-columns matrix — used in our program), **Route Cipher** (read in a specific path/spiral), **Double Transposition** (apply transposition twice for stronger security), and **Myszkowski Transposition** (a variant with repeated key letters).

12. **What is a Rail Fence Cipher?**
    The **Rail Fence Cipher** writes the message in a **zig-zag pattern** across multiple horizontal lines ("rails") and then reads each rail row by row to produce the ciphertext. For example, with 3 rails: "HELLO WORLD" → reads off as "HOLELWRDLO". Simple but easily broken with frequency analysis and known number of rails.

13. **What is a Columnar Transposition Cipher?**
    A **Columnar Transposition Cipher** writes the plaintext **row by row into a matrix with a fixed number of columns**, then reads the columns to produce ciphertext. The number of columns (and optionally a column ordering) is the key. Our program implements this with a key = number of columns.

14. **What is the key in Columnar Transposition?**
    The **key** is the **number of columns** in the matrix (in the simple version) or the **column read order** (in the keyed version, where columns are read based on alphabetical order of a keyword). Our program uses the simple version where the key = column count (e.g., 4).

15. **What is padding in transposition?**
    **Padding** means **adding extra characters** (like 'x', 'z', or null) to **fill incomplete cells** in the last row of the matrix. It ensures the matrix is rectangular and the encryption/decryption logic works uniformly. We use lowercase `x` as padding.

16. **Why do we use padding?**
    Padding ensures the matrix is **completely filled** even when the message length is not a multiple of the key (number of columns). Without padding, the last row would have empty cells, complicating the column-reading logic. The padding character should ideally be obvious so it can be removed after decryption.

17. **Is Transposition cipher symmetric or asymmetric?**
    Transposition is a **symmetric cipher** — the **same key (number of columns)** is used for both encryption and decryption. This is similar to most classical ciphers. Asymmetric cryptography (RSA, ECC) is a much later invention (1970s) and uses different keys.

18. **Are letter frequencies preserved in transposition?**
    **Yes** — transposition ciphers **preserve letter frequencies** because they only rearrange letters, never replace them. Same letters appear, just in different positions. This is a major **weakness** — an attacker can apply **frequency analysis** to detect patterns (e.g., 'E' is the most common letter in English).

19. **Can transposition cipher be broken?**
    **Yes** — transposition ciphers can be broken by: **(1) brute force** on the key (try all column counts, especially if the message is short), **(2) frequency analysis** combined with anagram solving, or **(3) statistical analysis** of bigrams/trigrams. Computers can break simple transposition ciphers in seconds.

20. **How can we make transposition stronger?**
    To strengthen transposition: **(1)** use a **larger key** (more columns, harder to brute force), **(2)** apply **multiple rounds** of transposition with different keys (Double Transposition is harder to break), **(3)** **combine with substitution** (most modern ciphers do this), or **(4)** use **keyed column ordering** to add complexity.

### Program-Specific
21. **What language is used in this program?**
    The implementation is in **C++**. C++ provides convenient string handling via `cin.getline()`, easy 2D array support, and compile-time efficiency. Python or Java would also work — the algorithm is language-agnostic.

22. **What is the input to the program?**
    The program takes **two inputs**: **(1)** the **message string** (the plaintext to encrypt), and **(2)** the **key** (a positive integer representing the number of columns in the matrix). For example, with message "HelloWorld" and key 4, the matrix is 3 rows × 4 columns.

23. **What is the size of the matrix?**
    The matrix has **`rows × key`** dimensions, where `rows = ceil(length / key)` (rounded up). For "HelloWorld" (length 10) with key 4: rows = ceil(10/4) = 3, so the matrix is 3×4 = 12 cells (with 2 padding characters).

24. **Why do we use `(len + key - 1) / key` for rows?**
    The expression `(len + key - 1) / key` is the standard idiom for **ceiling integer division** in C++. Regular integer division `len/key` rounds down — which would lose data. Adding `key-1` before dividing ensures we round **up** to fit all characters in the matrix.

25. **What padding character is used?**
    Our program uses **lowercase 'x'** as the padding character. The choice is arbitrary — any rare or distinguishable character works. Common alternatives: 'z', '_', '*', or null bytes. The padding should be removable after decryption (or visible as filler).

26. **What header files are used?**
    Our program uses **`<iostream>`** for input/output (cin, cout) and **`<cstring>`** for the `strlen()` function to compute message length. C-style strings are used for simplicity, but `<string>` could be used for std::string instead.

27. **Which function reads the input message?**
    The program uses **`cin.getline(msg, 100)`** to read the input — it reads up to 99 characters (or until a newline) **including spaces**. This is important because `cin >> msg` would stop at the first whitespace, losing parts of multi-word messages.

28. **How does encryption read the matrix?**
    Encryption reads the matrix **column by column** (top to bottom, left to right). After filling the matrix row-wise with the plaintext, we traverse it in column-major order to produce the ciphertext. This shuffling of order is what creates the encryption.

29. **How does decryption fill the matrix?**
    Decryption is the reverse: we **fill the matrix column by column** with the ciphertext, then **read it row by row** to recover the plaintext. The same key (column count) must be used, otherwise the decrypted output will be wrong.

30. **What happens if key is greater than message length?**
    If key > message length, the matrix has only **one row**, and many cells get padded. The "encryption" mostly just adds padding without much shuffling — the cipher provides no real security in this case. The key should always be smaller than the message length for meaningful encryption.

### Cryptography Concepts
31. **What is the CIA triad?**
    The CIA triad is the foundation of information security: **Confidentiality** (data accessible only to authorized users), **Integrity** (data not tampered with), and **Availability** (data and services accessible when needed). All security mechanisms support one or more of these three principles.

32. **What is symmetric encryption?**
    **Symmetric encryption** uses the **same key** for both encryption and decryption — both sender and receiver must share this secret key. It's typically **fast** and used for bulk data. Examples: **AES, DES, 3DES, RC4**, and our transposition cipher.

33. **What is asymmetric encryption?**
    **Asymmetric encryption** uses **two different keys** — a **public key** (shared) for encryption and a **private key** (secret) for decryption. It solves the key distribution problem of symmetric encryption. Examples: **RSA, ECC, Diffie-Hellman**. Slower than symmetric, often used to exchange a symmetric key.

34. **What is cryptanalysis?**
    **Cryptanalysis** is the **study of analyzing and breaking** cryptographic systems — recovering plaintext or keys without authorization. Techniques include **brute force**, **frequency analysis**, **differential cryptanalysis**, **linear cryptanalysis**, and **side-channel attacks**. It's the "offensive" side of cryptography.

35. **What is frequency analysis?**
    **Frequency analysis** is a cryptanalysis technique that **analyzes the frequency of letters or symbols** in the ciphertext to deduce the plaintext. Since letter frequencies in natural language are predictable (E ≈ 12%, T ≈ 9%, etc.), this works against substitution and transposition ciphers — but **fails against modern ciphers** that produce random-looking ciphertext.

36. **What is a brute-force attack?**
    A **brute-force attack** tries **every possible key** until the correct one is found. The time required depends on the **key space** (number of possible keys). For a 56-bit key (DES), that's 2^56 ≈ 72 quadrillion keys — feasible with modern hardware. For 128-bit AES keys, it's infeasible (2^128).

37. **Where is transposition used in modern cryptography?**
    Transposition lives on in modern ciphers as the **permutation/diffusion step**: in **DES**, the **P-box** permutes bits; in **AES**, **ShiftRows** rotates rows of the state. Modern algorithms combine **substitution** (S-boxes for confusion) with **permutation** (P-boxes for diffusion) — Shannon's principles.

38. **Is transposition cipher used today?**
    Transposition by itself is **not used today** for serious encryption — too easily broken. However, **transposition steps** are integral parts of modern cipher designs (AES, DES) where they provide **diffusion**. So the technique survives within larger algorithms.

39. **Difference between block cipher and stream cipher?**
    A **block cipher** encrypts data in **fixed-size blocks** (e.g., AES = 128 bits, DES = 64 bits) using complex multi-round operations. A **stream cipher** encrypts data **one bit or byte at a time** by XORing with a generated keystream (RC4, ChaCha20). Block ciphers are versatile (multiple modes); stream ciphers are typically faster.

40. **What is the disadvantage of Columnar Transposition?**
    The main disadvantage is that **letter frequencies are unchanged** — making it **vulnerable to frequency analysis**. Other weaknesses: **small key space** (limited number of column counts), **anagram attacks** (try to rearrange ciphertext into a meaningful message), and **predictable padding** giving hints. These are why classical ciphers are no longer used.

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Atul Kahate – *Cryptography and Network Security*
- Behrouz A. Forouzan – *Cryptography and Network Security*
