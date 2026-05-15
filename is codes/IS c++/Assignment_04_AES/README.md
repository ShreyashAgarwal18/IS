# Assignment 4 – AES (Advanced Encryption Standard) Algorithm

## Problem Statement
Write a C++ program to implement the **AES Algorithm** for encryption and decryption.

---

## 1. Aim
To study and implement the **Advanced Encryption Standard (AES)** algorithm in C++ and verify its encryption and decryption.

---

## 2. Theory (Simple)

### What is AES?
**AES (Advanced Encryption Standard)** is a **symmetric-key block cipher** standardized by NIST in 2001 to replace DES. It was designed by Belgian cryptographers **Joan Daemen and Vincent Rijmen** (originally called **Rijndael**).

| Property | Value |
|----------|-------|
| Block size | **128 bits** (16 bytes) |
| Key sizes | **128, 192, or 256 bits** |
| Number of rounds | **10 / 12 / 14** (for 128/192/256 bit keys) |
| Structure | **Substitution-Permutation Network (SPN)** |
| Type | Symmetric |

This program implements **AES-128** (10 rounds, 128-bit key).

### Why AES?
- Replaced DES because DES's 56-bit key was too small.
- Faster and more secure than DES/3DES.
- Used worldwide: HTTPS, WiFi (WPA2/3), file encryption, banking, military.

### The State (4×4 Matrix)
The 16-byte block is arranged as a **4×4 matrix of bytes** called the **state**, in column-major order:
```
| s0  s4  s8  s12 |
| s1  s5  s9  s13 |
| s2  s6  s10 s14 |
| s3  s7  s11 s15 |
```

### AES Round Operations
Each round (except last) performs **4 transformations**:

**1. SubBytes** – Each byte is replaced using a fixed lookup table called **S-box**. Provides non-linearity (confusion).

**2. ShiftRows** – Rows of the state are rotated:
- Row 0: no shift
- Row 1: shift left by 1
- Row 2: shift left by 2
- Row 3: shift left by 3

**3. MixColumns** – Each column is multiplied by a fixed matrix in GF(2^8). Provides diffusion. *(skipped in the last round)*

**4. AddRoundKey** – State is XORed with the round key.

### AES-128 Structure
```
Plaintext (16 bytes)
        |
   AddRoundKey  (with original key)
        |
  9 main rounds (SubBytes, ShiftRows, MixColumns, AddRoundKey)
        |
  Final round (SubBytes, ShiftRows, AddRoundKey)   <- no MixColumns
        |
   Ciphertext (16 bytes)
```

### Key Expansion
The 16-byte key is expanded into **11 round keys** (176 bytes total) using:
- **RotWord** – rotate 4 bytes left
- **SubWord** – apply S-box to each byte
- **Rcon** – XOR with round constant

### Decryption
Decryption uses the **inverse operations** in reverse order:
- InvShiftRows, InvSubBytes, InvMixColumns, AddRoundKey
- Round keys used in **reverse order** (K10 → K0)

---

## 3. Algorithm

### Encryption
```
1. Copy plaintext into 4x4 state matrix.
2. AddRoundKey (with K0).
3. For round = 1 to 9:
       SubBytes
       ShiftRows
       MixColumns
       AddRoundKey (with Ki)
4. Final round (round 10):
       SubBytes
       ShiftRows
       AddRoundKey (with K10)
5. Output state = ciphertext.
```

### Decryption
```
1. Copy ciphertext into state matrix.
2. AddRoundKey (with K10).
3. For round = 9 down to 1:
       InvShiftRows
       InvSubBytes
       AddRoundKey (with Ki)
       InvMixColumns
4. Final round:
       InvShiftRows
       InvSubBytes
       AddRoundKey (with K0)
5. Output state = plaintext.
```

---

## 4. Program File
- `aes.cpp` – C++ source code

### How to Run
```bash
g++ aes.cpp -o aes
./aes
```

### Code Sections
The code is split into 6 well-commented sections:
1. **AES Tables** – S-box, Inverse S-box, Rcon.
2. **Helpers** – `xtime` (GF multiplication), `printHex`.
3. **AES Transformations** – `subBytes`, `shiftRows`, `mixColumns`, `addRoundKey` (and inverses).
4. **Key Expansion** – `keyExpansion()` produces 11 round keys.
5. **Encrypt / Decrypt** – `aesEncrypt()` and `aesDecrypt()`.
6. **Main Driver** – encrypts and decrypts the standard FIPS-197 test vector.

---

## 5. Sample Output
```
=== AES-128 Algorithm Demonstration ===

Plaintext  : 3243f6a8885a308d313198a2e0370734
Key        : 2b7e151628aed2a6abf7158809cf4f3c

Ciphertext : 3925841d02dc09fbdc118597196a0b32
Decrypted  : 3243f6a8885a308d313198a2e0370734
```
This matches the official **FIPS-197 Appendix B test vector** — confirming a correct AES-128 implementation.

---

## 6. Observation
1. AES processes one **128-bit block** of data at a time.
2. The same key encrypts and decrypts (symmetric).
3. Encryption uses 10 rounds; decryption uses 10 inverse rounds with reversed round keys.
4. **MixColumns is skipped in the last round** — by design, so decryption can mirror the structure.
5. AES exhibits a strong **avalanche effect** (1-bit input change → ~50% bits change in output).

---

## 7. Conclusion
We successfully implemented the **AES-128 algorithm** in C++. The program correctly encrypts a 128-bit plaintext block using a 128-bit key with 10 rounds and decrypts the ciphertext back to the original plaintext.

---

## 8. AES vs DES

| Feature | DES | AES |
|---------|-----|-----|
| Block size | 64 bits | 128 bits |
| Key size | 56 bits | 128 / 192 / 256 bits |
| Rounds | 16 | 10 / 12 / 14 |
| Structure | Feistel | Substitution-Permutation Network |
| Speed | Slower | Faster |
| Security | Broken (1999) | Secure |
| Year | 1977 | 2001 |

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is AES?**
   **AES (Advanced Encryption Standard)** is a **symmetric-key block cipher** that became the U.S. federal standard for data encryption in 2001, replacing DES. It uses a **Substitution-Permutation Network (SPN)** structure with 10–14 rounds depending on the key size. AES is widely used in HTTPS, WiFi (WPA2/3), file encryption, banking, and government secure communications.

2. **Who designed AES?**
   AES was designed by two Belgian cryptographers: **Joan Daemen** and **Vincent Rijmen**. They submitted their cipher (originally called **Rijndael**) to the **NIST AES competition** (1997–2001) where it won out of 15 candidates. The competition was open and public — a major shift from DES's secretive design.

3. **What was AES originally called?**
   AES was originally called **Rijndael** (pronounced "rain-doll"), a portmanteau of its inventors' names — **Rij**men + **Dae**men. The original Rijndael supported various block and key sizes; the **AES standard fixed the block size at 128 bits** while allowing keys of 128, 192, or 256 bits.

4. **In which year was AES standardized?**
   AES was standardized in **2001** by NIST as **FIPS PUB 197**. The selection process took 4 years (1997–2001) and involved public cryptanalysis of 15 candidate algorithms. The choice was announced on October 2, 2000, and AES became the official standard on November 26, 2001.

5. **Why was AES introduced?**
   AES was introduced to **replace DES**, whose **56-bit key** had become too short — it was brute-forced in **22 hours by Deep Crack in 1999**. NIST needed a new cipher with a much larger key space, better resistance to modern attacks, and faster software performance. AES delivers all three.

6. **What is the block size of AES?**
   AES has a fixed block size of **128 bits (16 bytes)**, regardless of which key size is used. The block is arranged as a **4×4 matrix of bytes** called the **state**, which the algorithm transforms across rounds. The 128-bit block contrasts with DES's 64-bit block, providing better security against birthday attacks.

7. **What key sizes does AES support?**
   AES supports **three key sizes**: **128 bits (AES-128)**, **192 bits (AES-192)**, and **256 bits (AES-256)**. Larger keys provide greater security but require more rounds and computation. AES-128 is the most common choice; AES-256 is used for top-secret data and crypto-paranoid applications.

8. **How many rounds does AES use?**
   The number of rounds depends on the key size: **10 rounds for AES-128**, **12 rounds for AES-192**, and **14 rounds for AES-256**. More rounds = more security but slower performance. The round count was carefully chosen to provide a security margin against known attacks.

9. **Is AES symmetric or asymmetric?**
   AES is a **symmetric cipher** — the **same key** is used for both encryption and decryption. Both communicating parties must securely share the key in advance. Symmetric ciphers like AES are typically **much faster** than asymmetric ones (RSA), so AES is used for bulk data encryption while RSA is used for key exchange.

10. **What structure does AES use?**
    AES uses a **Substitution-Permutation Network (SPN)** — alternating layers of **substitution (SubBytes via S-box)** for confusion and **permutation (ShiftRows + MixColumns)** for diffusion, with key mixing (AddRoundKey). This contrasts with DES's Feistel structure. SPNs are typically more parallelizable than Feistel networks.

### AES Operations
11. **What are the 4 main steps in an AES round?**
    Each AES round has **4 transformations**: **(1) SubBytes** (S-box substitution — non-linearity), **(2) ShiftRows** (row rotation — diffusion within rows), **(3) MixColumns** (matrix multiply in GF(2^8) — diffusion across columns), **(4) AddRoundKey** (XOR with round key). The final round skips MixColumns.

12. **What is SubBytes?**
    **SubBytes** replaces each byte of the state with another byte from a **fixed 256-entry S-box (lookup table)**. This is the **non-linear step** — providing **confusion** by hiding the relationship between input and output. The S-box is constructed from the multiplicative inverse in GF(2^8) followed by an affine transformation.

13. **What is ShiftRows?**
    **ShiftRows** **rotates each row of the 4×4 state** to the left by a different amount: **row 0 by 0**, **row 1 by 1**, **row 2 by 2**, **row 3 by 3** positions. This provides **horizontal diffusion** — bytes spread across columns, ensuring that subsequent MixColumns mixes data from different parts of the state.

14. **What is MixColumns?**
    **MixColumns** multiplies **each column of the state** (4 bytes) by a **fixed 4×4 matrix in GF(2^8)** (the finite field of 256 elements). This provides **vertical diffusion** — each output byte depends on all 4 input bytes of the column. Combined with ShiftRows, every output bit depends on all input bits within a few rounds.

15. **What is AddRoundKey?**
    **AddRoundKey** is the simplest step: **XOR the state with the round key** (both 128 bits). This is the only step where the key is mixed into the data — without AddRoundKey, all the other transformations would be public and the ciphertext would be predictable.

16. **Which step is skipped in the last round?**
    The **MixColumns step is skipped in the last (10th, 12th, or 14th) round**. So the last round only has **SubBytes, ShiftRows, and AddRoundKey**. This exception is intentional and important for the structure of the cipher.

17. **Why is MixColumns skipped in the last round?**
    MixColumns is skipped in the last round so that **encryption and decryption have a parallel structure** — making it easier to implement decryption with similar code. If MixColumns were the last operation, decryption would require an extra inverse step that breaks symmetry.

18. **What is the AES State?**
    The **AES state** is a **4×4 matrix of bytes (16 bytes = 128 bits)** that represents the data being processed. All AES operations (SubBytes, ShiftRows, etc.) act on the state. By convention, bytes are stored in **column-major order** — column 0 first, then column 1, etc.

19. **What is the S-box?**
    The **AES S-box** is a **fixed 256-entry lookup table** that maps each byte (0-255) to another byte. It provides the **non-linearity** essential for security. The S-box is **carefully constructed** to resist linear and differential cryptanalysis — built from the multiplicative inverse in GF(2^8) plus an affine transformation.

20. **What is GF(2^8)?**
    **GF(2^8)** is the **Galois Field of 256 elements** — a finite field used for AES arithmetic. Each byte (0-255) is treated as a polynomial of degree ≤ 7 over GF(2), with arithmetic done modulo the irreducible polynomial **x^8 + x^4 + x^3 + x + 1** (= 0x11B). MixColumns and the S-box both operate in GF(2^8).

### Key Expansion
21. **What is Key Expansion?**
    **Key Expansion (Key Schedule)** is the process of **deriving multiple round keys from the single original master key**. AES-128 expands its 128-bit key into **11 round keys (176 bytes total)**. Each round of AES uses a unique round key for the AddRoundKey step.

22. **How many round keys does AES-128 use?**
    AES-128 uses **11 round keys** — **1 initial round key** (for the pre-round AddRoundKey) plus **10 round keys** (one per round). Total = 11 × 128 bits = **1408 bits = 176 bytes** of round-key material.

23. **What are the steps in Key Expansion?**
    The key expansion uses these operations on each new 4-byte word: **(1) RotWord** (rotate word bytes left), **(2) SubWord** (apply S-box to each byte), **(3) XOR with Rcon** (round constant), **(4) XOR with the word from 4 positions back**. This creates strong cryptographic dependencies between round keys.

24. **What is RotWord?**
    **RotWord** is a **cyclic left rotation** of a 4-byte word by 1 byte. For example, `[a0, a1, a2, a3]` becomes `[a1, a2, a3, a0]`. It's used in key expansion to mix bytes across positions before applying the S-box.

25. **What is SubWord?**
    **SubWord** **applies the AES S-box** to each byte of a 4-byte word. So `[a0, a1, a2, a3]` becomes `[S(a0), S(a1), S(a2), S(a3)]`. This provides non-linearity in the key expansion, similar to SubBytes in encryption rounds.

26. **What is Rcon?**
    **Rcon (Round Constant)** is an **array of constants** used in key expansion to **prevent symmetry** in the round keys. Each Rcon[i] = `[2^(i-1), 0, 0, 0]` in GF(2^8). Without Rcon, similar round keys would lead to security weaknesses.

27. **Total bytes of round keys in AES-128?**
    AES-128 produces **176 bytes** of round keys: **11 round keys × 16 bytes per key = 176 bytes**. These are typically computed once when the cipher is initialized and stored for use in the encryption/decryption rounds.

### Decryption
28. **How does AES decryption work?**
    AES decryption uses the **inverse transformations** (InvSubBytes, InvShiftRows, InvMixColumns) applied in **reverse order** with **round keys reversed** (K10 → K0). It produces the original plaintext from the ciphertext. There are equivalent inverse cipher implementations that can use the same code structure as encryption with adjusted constants.

29. **What is the inverse of SubBytes?**
    The **inverse of SubBytes** uses the **Inverse S-box** — a separate 256-entry lookup table where each entry undoes the corresponding S-box mapping. So if `S[x] = y`, then `InvS[y] = x`. The inverse S-box is precomputed and stored.

30. **What is the inverse of ShiftRows?**
    The **inverse of ShiftRows** **rotates each row to the right** by the same amount it was rotated left during encryption: row 0 by 0, row 1 by 1, row 2 by 2, row 3 by 3 positions to the right. This restores the original positions.

### Security and Concepts
31. **Is AES secure today?**
    **Yes** — AES is **considered secure** for all practical purposes. **No practical attack on full-round AES exists**. The best known attacks (related-key attacks on AES-256, biclique attacks) only marginally improve over brute force and require unrealistic conditions. AES is approved by NSA for **TOP SECRET** information (with 192 or 256-bit keys).

32. **What is the avalanche effect?**
    The **avalanche effect** is the property that **a tiny change in input** (1 bit of plaintext or key) causes **a large change in output** (~50% of ciphertext bits flip). AES has very strong avalanche — typically achieves full diffusion within just 2 rounds, providing excellent security against differential attacks.

33. **What are confusion and diffusion?**
    **Confusion** is hiding the **relationship between the key and the ciphertext** — making the relationship complex (provided by AES's S-box). **Diffusion** is spreading the **influence of one input bit over many output bits** (provided by ShiftRows + MixColumns). Together they make ciphertext appear random.

34. **Who introduced confusion and diffusion?**
    **Claude Shannon** introduced the concepts of **confusion and diffusion** in his **1949 paper "Communication Theory of Secrecy Systems"**. Shannon also formalized perfect secrecy (One-Time Pad). His principles guide all modern symmetric ciphers (AES, DES, Twofish, etc.).

35. **What is a block cipher mode?**
    A **mode of operation** defines how a block cipher (like AES) is **applied to data longer than one block**. Common modes: **ECB** (insecure, identical blocks → identical ciphertext), **CBC** (chains blocks via XOR), **CTR** (turns block cipher into stream cipher), **GCM** (CTR + authentication = AEAD). Modern systems prefer **GCM**.

36. **Which is the most secure AES mode for messaging?**
    **GCM (Galois/Counter Mode)** is the most secure and widely-recommended AES mode. It provides both **confidentiality** (encryption via CTR mode) AND **authentication** (via Galois MAC) — making it an **Authenticated Encryption with Associated Data (AEAD)** scheme. Used in TLS 1.2/1.3, WireGuard VPN, and many modern protocols.

37. **What is the difference between AES and DES?**
    **AES** has larger blocks (128 vs 64 bits), larger keys (128/192/256 vs 56 bits), uses SPN (vs Feistel), is faster in software, and is **secure** (vs DES being broken since 1999). AES has fewer but more complex rounds (10/12/14 vs 16). AES was designed openly; DES was modified in secret by NSA.

38. **What is brute-force on AES-128?**
    A brute-force attack on AES-128 would require trying **2^128 ≈ 3.4 × 10^38** keys. Even with **all the world's computing power running for billions of years**, brute-forcing AES-128 is **practically impossible**. AES-256 (2^256 keys) is post-quantum brute-force resistant.

39. **Where is AES used in real life?**
    AES is used **everywhere modern encryption is needed**: **HTTPS/TLS** (web traffic), **WPA2/WPA3** (WiFi), **full-disk encryption** (BitLocker, FileVault, LUKS), **VPNs** (WireGuard, OpenVPN), **messaging apps** (WhatsApp, Signal), **banking transactions**, **government communications**, **5G mobile networks**, and **cryptocurrency wallets**.

40. **Difference between AES-128 and AES-256?**
    **AES-128** uses a **128-bit key** and **10 rounds**; **AES-256** uses a **256-bit key** and **14 rounds**. AES-256 provides a **larger security margin** (especially against future quantum computers via Grover's algorithm). It's slightly **slower** (~40% more rounds = more computation) but considered necessary for top-secret data.

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Bruce Schneier – *Applied Cryptography*
- NIST FIPS PUB 197 – AES specification
- Joan Daemen, Vincent Rijmen – *The Design of Rijndael*
