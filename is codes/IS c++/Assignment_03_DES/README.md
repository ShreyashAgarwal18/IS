# Assignment 3 – DES (Data Encryption Standard) Algorithm

## Problem Statement
Write a C++ program to implement the **DES Algorithm** for encryption and decryption.

---

## 1. Aim
To study and implement the **Data Encryption Standard (DES)** symmetric-key block cipher in C++ and verify encryption and decryption.

---

## 2. Theory (Simple)

### What is DES?
**DES (Data Encryption Standard)** is a **symmetric-key block cipher** designed by IBM in 1975 and adopted by NIST as a federal standard in 1977.

| Property | Value |
|----------|-------|
| Block size | **64 bits** (8 bytes) |
| Key size | **64 bits** (only 56 used, 8 are parity) |
| Number of rounds | **16** |
| Structure | **Feistel network** |
| Type | Symmetric (same key for encrypt/decrypt) |

### Why DES?
- First widely-used encryption standard for civilian/commercial use.
- Foundation of modern symmetric cryptography.
- Inspired Triple DES (3DES) and modern ciphers like AES.

### Main Steps of DES
```
                 Plaintext (64 bits)
                        |
                Initial Permutation (IP)
                        |
                  L0   |   R0   (32 + 32 bits)
                        |
              16 Feistel Rounds
                  (using 16 round keys K1..K16)
                        |
                 32-bit Swap (R16 || L16)
                        |
            Final Permutation (IP^-1)
                        |
                 Ciphertext (64 bits)
```

### One Feistel Round
```
Li = R(i-1)
Ri = L(i-1) XOR f(R(i-1), Ki)
```
Where `f` is the DES round function.

### The f-function (heart of DES)
1. **Expansion (E):** 32 bits → 48 bits using E-table.
2. **Key XOR:** XOR with 48-bit round key Ki.
3. **S-box substitution:** 8 S-boxes convert 48 bits → 32 bits (each S-box: 6 bits → 4 bits).
4. **Permutation (P):** Permute the 32 bits.

### Key Schedule
- Original 64-bit key → **PC-1** → 56-bit key.
- Split into two halves C0, D0 (28 bits each).
- For each round, **left-shift** both halves by 1 or 2 bits.
- Combine and apply **PC-2** to get a 48-bit round key.
- Repeat 16 times → 16 round keys.

### Decryption
DES decryption uses the **same algorithm** as encryption but applies the **round keys in reverse order** (K16 → K1).

---

## 3. Algorithm
```
ENCRYPTION:
1. Convert plaintext and key to binary (64 bits each).
2. Apply Initial Permutation (IP) to plaintext.
3. Split into L0 (left 32 bits) and R0 (right 32 bits).
4. Generate 16 round keys K1..K16 from the main key.
5. For i = 1 to 16:
       Li = R(i-1)
       Ri = L(i-1) XOR f(R(i-1), Ki)
6. Combine R16 || L16 (32-bit swap).
7. Apply Final Permutation (IP^-1) to get the ciphertext.

DECRYPTION:
Same as encryption, but use round keys in reverse: K16, K15, ..., K1.
```

---

## 4. Program File
- `des.cpp` – C++ source code

### How to Run
```bash
g++ des.cpp -o des
./des
```

### Code Sections
The code is split into 6 well-commented sections:
1. **DES Standard Tables** – IP, FP, E, P, PC-1, PC-2, S-boxes, shift schedule.
2. **Helper Functions** – `permute`, `leftShift`, `xorStrings`, `hexToBin`, `binToHex`.
3. **Key Schedule** – `generateKeys()` produces 16 round keys.
4. **F-function** – the Feistel round function with E, XOR, S-box, P.
5. **DES Encrypt/Decrypt** – `desProcess()` does both based on a flag.
6. **Main Driver** – runs encryption then decryption to verify.

---

## 5. Sample Output
```
=== DES Algorithm Demonstration ===

Plaintext (hex) : 123456ABCD132536
Key       (hex) : AABB09182736CCDD

Ciphertext (hex): C0B7A8D05F3A829C
Decrypted (hex) : 123456ABCD132536
```
The decrypted text matches the original plaintext — encryption and decryption are working correctly.

---

## 6. Observation
1. DES encrypts a 64-bit block of plaintext into a 64-bit block of ciphertext.
2. The **same key** is used for both encryption and decryption (symmetric).
3. Decryption uses the **same algorithm** with round keys reversed.
4. Even a small change in plaintext or key causes large changes in ciphertext (**avalanche effect**).
5. The S-boxes provide **non-linearity** (confusion) and the permutations provide **diffusion** — Shannon's two key principles.

---

## 7. Conclusion
We successfully implemented the **DES algorithm** in C++. The program correctly encrypts a 64-bit plaintext block using a 64-bit key with 16 Feistel rounds and decrypts the ciphertext back to the original plaintext.

---

## 8. Advantages and Disadvantages

### Advantages
- Well-studied and standardized.
- Fast in hardware.
- Strong avalanche effect.
- Foundation for many modern ciphers.

### Disadvantages
- **56-bit key is too short** — broken by brute-force in 1999 (~22 hours).
- Vulnerable to **differential** and **linear** cryptanalysis.
- Replaced by **3DES** and then by **AES** (2001).

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is DES?**
   **DES (Data Encryption Standard)** is a **symmetric-key block cipher** that encrypts 64-bit blocks of data using a 64-bit key (effectively 56 bits). It was the first widely-adopted encryption standard for civilian use and was the dominant cipher from 1977 to 2001 before being replaced by AES. DES uses a **Feistel network** structure with 16 rounds.

2. **Who designed DES?**
   DES was designed by **IBM in the early 1970s** (originally a cipher called **Lucifer** by Horst Feistel and Don Coppersmith). It was modified by the **NSA** (National Security Agency) — they shortened the key from 128 bits to 56 bits and tweaked the S-boxes (controversially). It was standardized by the U.S. **NIST** as **FIPS PUB 46** in 1977.

3. **What is the block size of DES?**
   DES has a **64-bit block size** — it processes plaintext in chunks of 8 bytes at a time. To encrypt longer data, you use a **mode of operation** (ECB, CBC, CTR) that defines how multiple blocks are linked. The 64-bit block is now considered too small (vulnerable to birthday attacks on certain modes).

4. **What is the key size of DES?**
   DES uses a **64-bit key**, but only **56 bits are used for security** — the remaining **8 bits are parity bits** (one per byte for error detection, not for cryptography). This 56-bit effective key length is the main reason DES became insecure (only 2^56 ≈ 72 quadrillion keys, brute-forceable).

5. **How many rounds does DES use?**
   DES uses **16 rounds** of the Feistel structure. Each round applies the f-function and XOR, mixing the data with a unique 48-bit round key. The 16-round count was chosen to provide adequate security with the period's computing power — fewer rounds were susceptible to attacks like differential cryptanalysis.

6. **Is DES symmetric or asymmetric?**
   DES is **symmetric** — the **same 64-bit key** is used for both encryption and decryption. This means both parties (sender and receiver) must securely share the key in advance. Modern symmetric ciphers (AES) use the same model but with longer keys.

7. **What structure does DES use?**
   DES uses a **Feistel network (Feistel cipher) structure** — the 64-bit block is **split into two 32-bit halves (L, R)**, and at each round, one half is transformed and XORed with the other. The Feistel structure has the elegant property that the **same algorithm encrypts and decrypts** (only round keys are reversed).

8. **Why is DES called a block cipher?**
   DES is a **block cipher** because it encrypts data in **fixed-size blocks (64 bits)** rather than one bit at a time. To encrypt arbitrary-length messages, you split the message into 64-bit blocks and apply DES to each, using a mode of operation. Stream ciphers (RC4) instead encrypt one bit/byte at a time.

9. **What is a Feistel network?**
   A **Feistel network** is a symmetric cipher structure where the block is **split into two halves (L, R)**, and each round computes `L_new = R_old`, `R_new = L_old XOR f(R_old, K_round)`. The function `f` doesn't need to be invertible — the structure itself ensures decryptability by reversing the round-key order. Used in DES, 3DES, Blowfish, Twofish.

10. **Who broke DES first?**
    DES was first publicly broken by the **Electronic Frontier Foundation (EFF)** with their custom **"Deep Crack" machine** in **1998**, which decrypted a DES-encrypted message in **~56 hours**. In 1999, with **Distributed.net + Deep Crack**, the time dropped to **~22 hours**. This proved DES's 56-bit key was inadequate against modern hardware.

### DES Internals
11. **What is Initial Permutation (IP)?**
    The **Initial Permutation (IP)** is a **fixed bit permutation** applied to the 64-bit plaintext at the very start of DES — it rearranges the 64 input bits according to a specific table. It was added partly for hardware efficiency in 1970s hardware. It has **no cryptographic effect** on its own (it's public and reversible) but is part of the standard.

12. **What is Final Permutation?**
    The **Final Permutation (IP^-1)** is the **inverse** of the Initial Permutation, applied at the end of DES (after the 16 rounds and the final swap). It rearranges the bits back to undo IP's permutation. Like IP, it has no cryptographic effect — its purpose is structural.

13. **What is the f-function?**
    The **f-function** is the **heart of each DES round** — it takes the **32-bit right half (R)** and a **48-bit round key (K)** and produces a **32-bit output**. Internally, f does: **(1)** Expansion (32→48 bits), **(2)** XOR with round key, **(3)** S-box substitution (48→32 bits), **(4)** P-permutation. This is what provides confusion and diffusion.

14. **What are the steps inside f-function?**
    The f-function has **4 steps**: **(1) Expansion (E-table)** — expands 32 bits to 48 bits by duplicating some bits, **(2) XOR** with the 48-bit round key, **(3) S-box substitution** — eight S-boxes each convert 6 bits to 4 bits (48→32 bits), **(4) P-permutation** — rearranges the 32 output bits for diffusion.

15. **What is the Expansion table (E)?**
    The **Expansion table E** **expands the 32-bit right half to 48 bits** by **duplicating certain bits** according to a fixed permutation. This is necessary so that R can be XORed with the 48-bit round key. The duplicated bits also help spread input changes across multiple S-boxes (diffusion).

16. **What is an S-box?**
    An **S-box (Substitution box)** is a **lookup table** that maps 6 input bits to 4 output bits — providing **non-linearity** (confusion) in DES. There are **8 S-boxes** in DES, each different. They are the key source of DES's strength against linear cryptanalysis. The S-box design was carefully chosen by the NSA.

17. **How does an S-box pick its output?**
    Given a 6-bit input `b1 b2 b3 b4 b5 b6`: the **first and last bits (b1, b6)** form a **2-bit row index** (0–3); the **middle 4 bits (b2 b3 b4 b5)** form a **4-bit column index** (0–15). The S-box has 4 rows × 16 columns of 4-bit values. Look up `S[row][col]` to get the 4-bit output.

18. **What is the P permutation?**
    The **P-permutation** is a **fixed 32-bit permutation** applied at the end of the f-function, after the S-boxes. It scrambles the output bits to spread their influence across many positions in the next round — providing **diffusion**. Without P, S-box outputs would be limited to specific positions.

19. **What is PC-1?**
    **PC-1 (Permuted Choice 1)** is a **permutation in the key schedule** that takes the **64-bit input key** and produces a **56-bit key** by selecting 56 specific bits (and dropping the 8 parity bits). The 56 bits are then split into two 28-bit halves (C0, D0) for further processing.

20. **What is PC-2?**
    **PC-2 (Permuted Choice 2)** is a **permutation** that **selects 48 bits from the combined 56-bit (C+D) state** to form the **48-bit round key**. PC-2 is applied after the left-shifts of C and D in each round, producing K1, K2, …, K16 — one round key per round.

### Key Schedule and Rounds
21. **How are round keys generated?**
    Round keys are generated as follows: **(1)** Apply **PC-1** to the 64-bit master key → 56-bit key. **(2)** Split into 28-bit halves **C0, D0**. **(3)** For each round i (1–16), **left-shift** both halves by 1 or 2 bits (per the shift schedule). **(4)** Combine and apply **PC-2** to get the 48-bit round key Ki. Done 16 times for 16 round keys.

22. **How many round keys are used?**
    DES uses **16 round keys**, one per round. Each is **derived from the original 64-bit master key** through the key schedule. Storing all 16 round keys in advance avoids recomputing them per block.

23. **What is the size of each round key?**
    Each round key is **48 bits** — produced by PC-2 from the 56-bit (C+D) state. The round key XORs with the 48-bit expanded right half inside the f-function.

24. **How many bits are shifted in each round?**
    The left-shift amount per round follows the schedule: **1 bit** in rounds **1, 2, 9, 16**; **2 bits** in **all other rounds (3–8, 10–15)**. The total shifts per half over 16 rounds = 28 (which brings C and D back to their starting positions, useful for 3DES key reuse).

25. **How is decryption done in DES?**
    DES decryption uses the **same algorithm** as encryption — but the **round keys are applied in reverse order** (K16, K15, ..., K1 instead of K1, ..., K16). This works because of the **Feistel structure**: reversing keys reverses the rounds, recovering the plaintext.

26. **Why does DES use a swap at the end?**
    The **final swap** (R||L instead of L||R) before the Final Permutation makes the encryption and decryption processes **symmetric** — so the **same algorithm** can be used for both. Without it, separate encrypt/decrypt code paths would be needed.

27. **What is the avalanche effect?**
    The **avalanche effect** is the property that a **small change** in input (plaintext or key — even 1 bit) causes a **large change** in output (about 50% of ciphertext bits flip). It's a critical property for cryptographic security — DES has strong avalanche due to its 16 rounds, S-boxes, and permutations.

### Security
28. **Is DES secure today?**
    **No** — DES is **not secure for any modern application**. Its 56-bit key can be brute-forced in **hours** with specialized hardware (or **days** on consumer GPUs). NIST officially deprecated DES in 2005. Modern systems use **AES** (128–256 bit keys) instead.

29. **What is brute-force attack?**
    A **brute-force attack** tries **every possible key** until the correct one is found. For DES with a 56-bit key, that's **2^56 ≈ 7.2 × 10^16 keys** — about 72 quadrillion. Modern hardware (custom ASICs, GPU farms) can brute-force DES in **hours to days**, making it insecure.

30. **What replaced DES?**
    DES was first replaced by **3DES (Triple DES)** in the late 1990s as a stopgap, then by **AES (Advanced Encryption Standard)** in 2001 as the new official NIST standard. AES uses 128/192/256-bit keys and is much more secure and efficient.

31. **What is 3DES?**
    **3DES (Triple DES, also TDEA)** applies DES **three times** with **two or three keys**: typically `Encrypt(K3, Decrypt(K2, Encrypt(K1, plaintext)))`. With 3 different keys, the effective key length becomes 168 bits (or 112 bits with 2 keys due to meet-in-the-middle attacks). It's slower but much stronger than DES. Now also being phased out in favor of AES.

32. **What attacks work on DES?**
    Attacks on DES include: **(1) Brute force** (exhausting the 2^56 key space — practical since 1998), **(2) Differential cryptanalysis** (proposed by Biham & Shamir, 1990 — needs 2^47 chosen plaintexts), **(3) Linear cryptanalysis** (Matsui, 1993 — needs 2^43 known plaintexts), and **(4) Davies' attack** and others.

33. **What are weak keys in DES?**
    **Weak keys** are keys that produce **identical or simple round keys**, weakening the cipher. DES has **4 weak keys** (e.g., all-zeros, all-ones) where K1 = K2 = ... = K16, and **12 semi-weak keys** that come in pairs producing the same encryption. These are easily avoided by checking the key during use.

### Concepts
34. **What is confusion?**
    **Confusion** is a cryptographic principle that means **hiding the relationship between the key and the ciphertext** — making it hard for an attacker to deduce the key by analyzing ciphertext. It's typically achieved through **substitution operations (S-boxes)**. DES's S-boxes provide confusion.

35. **What is diffusion?**
    **Diffusion** is the principle that **each ciphertext bit should depend on many plaintext and key bits** — so changes propagate widely. It's typically achieved through **permutations and XOR operations**. DES's P-permutation, expansion, and Feistel structure all contribute to diffusion.

36. **Who introduced confusion and diffusion?**
    **Confusion and diffusion** were introduced by **Claude Shannon** in his seminal **1949 paper "Communication Theory of Secrecy Systems"**. Shannon also formalized the One-Time Pad's perfect secrecy. These two principles guide the design of all modern symmetric ciphers (DES, AES, etc.).

37. **What is a block cipher mode of operation?**
    A **mode of operation** defines **how a block cipher is applied to messages longer than one block**. Common modes: **ECB** (Electronic Codebook — encrypt each block independently, insecure for repeating data), **CBC** (Cipher Block Chaining — XOR with previous ciphertext), **CTR** (Counter), **CFB** (Cipher Feedback), **OFB** (Output Feedback), and **GCM** (Galois Counter Mode — adds authentication).

38. **Difference between block cipher and stream cipher?**
    A **block cipher** (DES, AES) encrypts data in **fixed-size blocks** with complex multi-round operations. A **stream cipher** (RC4, ChaCha20) encrypts data **bit-by-bit or byte-by-byte** by XORing with a generated keystream. Block ciphers are more versatile (multiple modes); stream ciphers are typically faster and need no padding.

39. **What is ECB mode?**
    **ECB (Electronic Codebook)** mode is the simplest mode: **each plaintext block is encrypted independently** with the same key. Its weakness: **identical plaintext blocks produce identical ciphertext blocks** — leaking patterns. ECB is **insecure for most data** and famously visible in encrypted images (the original image structure remains visible).

40. **Why is AES preferred over DES?**
    AES is preferred because: **(1)** larger keys (128/192/256 bits — vastly larger key space than DES's 56), **(2)** larger block size (128 bits — better for large data), **(3)** **faster in software** (DES was designed for 1970s hardware), **(4)** **more secure** — no practical attacks, **(5)** **modern design** (SPN structure with strong S-boxes), and **(6)** widely supported in modern hardware (Intel AES-NI).

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Bruce Schneier – *Applied Cryptography*
- NIST FIPS PUB 46-3 – DES specification
- Atul Kahate – *Cryptography and Network Security*
