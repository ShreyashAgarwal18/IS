# Assignment 5 – RSA Algorithm (Public-Key Cryptography)

## Problem Statement
Write a C++ program to implement the **RSA Algorithm** for encryption and decryption.

---

## 1. Aim
To study and implement the **RSA (Rivest–Shamir–Adleman)** asymmetric-key cryptography algorithm in C++.

---

## 2. Theory (Simple)

### What is RSA?
**RSA** is the **first practical public-key cryptosystem**, invented in 1977 by **Ron Rivest, Adi Shamir and Leonard Adleman** at MIT. It is based on the mathematical difficulty of **factoring the product of two large prime numbers**.

| Property | Value |
|----------|-------|
| Type | Asymmetric (public-key) |
| Based on | Integer factorization problem |
| Uses | Encryption, Digital Signatures, Key Exchange |
| Common key size | 2048 or 4096 bits |

### Symmetric vs Asymmetric
| Symmetric (DES, AES) | Asymmetric (RSA) |
|----------------------|------------------|
| Same key for both | Different keys (public + private) |
| Fast | Slower |
| Key exchange is hard | Key exchange is easy |
| Used for bulk encryption | Used for key exchange & signatures |

### Why "Public Key"?
- Each user has **two keys**:
  - **Public key** – shared with everyone (used to encrypt)
  - **Private key** – kept secret (used to decrypt)
- Anyone can encrypt a message using your public key.
- Only you can decrypt it using your private key.

### RSA Step-by-Step

**Step 1 – Pick two prime numbers:** `p` and `q` (large primes in real use).

**Step 2 – Compute `n` and `phi`:**
- `n = p * q` → modulus
- `phi(n) = (p-1) * (q-1)` → Euler's totient function

**Step 3 – Choose `e` (public exponent):**
- `1 < e < phi`
- `gcd(e, phi) = 1` (e and phi must be coprime)

**Step 4 – Compute `d` (private exponent):**
- `(d * e) mod phi = 1`
- d is the **modular inverse** of e mod phi

**Step 5 – Keys:**
- Public key  = `(e, n)`
- Private key = `(d, n)`

**Step 6 – Encryption:**
- Ciphertext: `c = m^e mod n`
  (m is the plaintext as a number, m < n)

**Step 7 – Decryption:**
- Plaintext: `m = c^d mod n`

### Worked Example
Let `p = 7`, `q = 11`, message `m = 9`.

- `n = 7 * 11 = 77`
- `phi = 6 * 10 = 60`
- Choose `e = 7` (gcd(7, 60) = 1)
- Compute `d` such that `(7 * d) mod 60 = 1` → `d = 43`
- **Public key** = (7, 77), **Private key** = (43, 77)

**Encrypt:** `c = 9^7 mod 77 = 37`
**Decrypt:** `m = 37^43 mod 77 = 9` ✔

### Why is RSA Secure?
- An attacker has the public key `(e, n)`.
- To find `d`, they need to know `phi(n)`.
- To find `phi(n)`, they need to factor `n` into `p * q`.
- For very large `n` (2048 bits ≈ 617 digits), factoring is **computationally infeasible**.

---

## 3. Algorithm

### Key Generation
```
1. Choose two large prime numbers p and q
2. Compute n = p * q
3. Compute phi(n) = (p-1) * (q-1)
4. Choose e such that 1 < e < phi and gcd(e, phi) = 1
5. Compute d such that (d * e) mod phi = 1
6. Public key  = (e, n)
   Private key = (d, n)
```

### Encryption
```
c = m^e mod n     (m is plaintext as number, m < n)
```

### Decryption
```
m = c^d mod n
```

---

## 4. Program File
- `rsa.cpp` – C++ source code

### How to Run
```bash
g++ rsa.cpp -o rsa
./rsa
```

The program asks for:
1. Two prime numbers `p` and `q`
2. A plaintext number `m` (must be less than `n`)

### Functions in the Code
| Function | Purpose |
|----------|---------|
| `gcd(a, b)` | Greatest Common Divisor (Euclid's algorithm) |
| `modPow(base, exp, mod)` | Computes (base^exp) mod m using square-and-multiply |
| `modInverse(e, phi)` | Finds d such that (e*d) mod phi = 1 |
| `isPrime(n)` | Checks if a number is prime |

---

## 5. Sample Output
```
=== RSA Algorithm ===

Enter two prime numbers (p and q) : 7 11

n   = p * q       = 77
phi = (p-1)*(q-1) = 60
e   (public)      = 7
d   (private)     = 43

Public Key  : (e=7, n=77)
Private Key : (d=43, n=77)

Enter the plaintext message (number < 77) : 9

Encrypted (cipher) = 37
Decrypted (plain)  = 9
```

---

## 6. Observation
1. RSA uses **two different keys** (public and private) – this is the essence of asymmetric cryptography.
2. The same algorithm performs both encryption and decryption — only the key changes.
3. Decryption recovers the exact original message: `(m^e)^d mod n = m`.
4. The security of RSA depends entirely on the **size of the prime numbers**.
5. RSA is **slow** compared to AES, so in practice it is used to exchange a small AES key, not for bulk encryption.

---

## 7. Conclusion
We successfully implemented the **RSA algorithm** in C++. The program performs key generation, encryption, and decryption, demonstrating the working principle of asymmetric public-key cryptography.

---

## 8. Applications of RSA
- **HTTPS / SSL / TLS** – web security (key exchange)
- **Digital Signatures** – verifying authenticity
- **Email encryption** – PGP, S/MIME
- **SSH** – secure remote login
- **VPN** – secure tunnels
- **Cryptocurrency** – key generation in some protocols

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is RSA?**
   **RSA** is the **first practical public-key (asymmetric) cryptography algorithm**, invented in 1977. It is based on the **mathematical hardness of factoring large composite numbers** into their prime factors. RSA is used worldwide for **secure key exchange, digital signatures, and small-data encryption** — including in HTTPS/TLS, PGP, and SSH.

2. **Who invented RSA?**
   RSA was invented by **Ron Rivest, Adi Shamir, and Leonard Adleman** at **MIT in 1977**. They published it in 1978 in the paper *"A Method for Obtaining Digital Signatures and Public-Key Cryptosystems"*. They later won the **2002 Turing Award** for this work. Interestingly, a similar algorithm had been independently discovered earlier (1973) by Clifford Cocks at GCHQ, but it was classified.

3. **What does RSA stand for?**
   **RSA** stands for the **initials of its three inventors**: **R**ivest, **S**hamir, and **A**dleman. The naming convention of using inventor initials for cryptographic algorithms is common (e.g., DSA, ECDSA).

4. **Is RSA symmetric or asymmetric?**
   RSA is **asymmetric** — it uses **two different keys**: a **public key** (shared with everyone, used for encryption or signature verification) and a **private key** (kept secret by the owner, used for decryption or signing). This solves the **key distribution problem** that plagues symmetric encryption.

5. **What is the public key?**
   The **public key** is the **part of the key pair that is shared openly** with anyone who wants to communicate with you. In RSA, it consists of `(e, n)` where `e` is the public exponent and `n` is the modulus. Anyone can use it to **encrypt** a message that only the holder of the private key can decrypt.

6. **What is the private key?**
   The **private key** is the **secret part of the key pair**, kept confidential by the owner. In RSA, it is `(d, n)` where `d` is the private exponent. It's used to **decrypt** messages encrypted with the corresponding public key, or to **digitally sign** messages.

7. **On which mathematical problem is RSA based?**
   RSA is based on the **integer factorization problem** — the **computational difficulty of factoring a large composite number `n` into its two prime factors `p` and `q`**. While multiplying two large primes is fast, factoring their product is infeasibly slow for sufficiently large primes (current attacks can factor up to ~829-bit numbers as of 2020).

8. **What is the difference between symmetric and asymmetric?**
   **Symmetric encryption** uses **one shared key** for both encryption and decryption (fast, but key distribution is hard). **Asymmetric encryption** uses **two different keys** (public + private) — slower, but solves the key exchange problem. In practice, **hybrid systems** use asymmetric for key exchange and symmetric for bulk data.

9. **Why is RSA called public-key cryptography?**
   RSA is called **public-key cryptography** because the **encryption key (the "public key") is made publicly available** — anyone can know it. Only the corresponding **private key** can decrypt. This was a revolutionary idea (introduced by Diffie & Hellman in 1976), enabling secure communication without prior key exchange.

10. **Is RSA secure?**
    **Yes** — RSA is **secure when used with sufficiently large keys (2048 bits or more)** and proper padding schemes (like **OAEP for encryption** and **PSS for signatures**). However, **RSA-1024 is now considered weak**, and **RSA will be vulnerable to quantum computers** (Shor's algorithm) when sufficiently large quantum computers exist.

### RSA Math
11. **What is `n` in RSA?**
    `n` is the **modulus** of the RSA system, computed as **`n = p × q`** where `p` and `q` are two large secret prime numbers. It's part of both the public key `(e, n)` and the private key `(d, n)`. In real RSA, `n` is a **2048 or 4096-bit number** (huge — about 600+ decimal digits).

12. **What is `phi(n)`?**
    **`phi(n)` (Euler's totient function)** is the **count of integers from 1 to n-1 that are coprime to n**. For `n = p × q` (product of two primes), `phi(n) = (p-1) × (q-1)`. It's needed to compute the private key `d`. **`phi(n)` must be kept secret** — knowing it allows finding `d`.

13. **What is `e`?**
    `e` is the **public exponent** — chosen such that **`1 < e < phi(n)`** AND **`gcd(e, phi(n)) = 1`** (coprime to phi). Common choices: **3, 17, 65537 (=2^16 + 1)** — these are popular because they are small primes that make encryption fast. **65537 is the most common** in practice (FIPS recommended).

14. **What is `d`?**
    `d` is the **private exponent** — the **modular inverse of `e` mod `phi(n)`**, satisfying **`(d × e) mod phi(n) = 1`**. It's computed using the **Extended Euclidean Algorithm**. Because computing `d` requires knowing `phi(n)`, and `phi(n)` requires factoring `n`, recovering `d` is as hard as factoring.

15. **What is the formula for encryption?**
    Encryption: **`c = m^e mod n`** — raise the plaintext `m` (treated as a number) to the power `e` modulo `n`. The result `c` is the ciphertext. This uses the **public key `(e, n)`** — anyone can encrypt; only the private-key holder can decrypt.

16. **What is the formula for decryption?**
    Decryption: **`m = c^d mod n`** — raise the ciphertext `c` to the power `d` modulo `n`. This recovers the original plaintext `m`. Decryption uses the **private key `(d, n)`** — only the owner can decrypt.

17. **Why must `m < n`?**
    Because all operations are **modulo n**, the results are in the range **0 to n-1**. If `m ≥ n`, the modular reduction would lose information: `m mod n` and `m + k×n` would both encrypt to the same ciphertext, making decryption ambiguous.

18. **What is GCD?**
    **GCD (Greatest Common Divisor)** is the **largest positive integer that divides two given integers without remainder**. For example, `gcd(12, 18) = 6`. **Euclid's algorithm** computes GCD efficiently: `gcd(a, b) = gcd(b, a mod b)`. GCD is needed to verify that `e` is coprime with `phi(n)`.

19. **What does it mean to be coprime?**
    Two integers are **coprime (relatively prime)** if their **GCD is 1** — meaning they share no common factors other than 1. For example, 9 and 10 are coprime. In RSA, we need `gcd(e, phi(n)) = 1` so that `e` has a modular inverse `d`.

20. **What is modular inverse?**
    The **modular inverse** of `e` modulo `phi` is a number `d` such that **`(e × d) mod phi = 1`**. It exists if and only if `gcd(e, phi) = 1`. Computed using the **Extended Euclidean Algorithm** (or by brute force for small numbers as in our program). In RSA, `d` is the private exponent.

### Algorithm Steps
21. **What are the key generation steps in RSA?**
    Key generation steps: **(1)** Choose two large random primes `p` and `q`. **(2)** Compute `n = p × q`. **(3)** Compute `phi(n) = (p-1)(q-1)`. **(4)** Choose `e` coprime to `phi(n)` (commonly 65537). **(5)** Compute `d = modular_inverse(e, phi(n))`. Then **public key = (e, n)** and **private key = (d, n)**.

22. **What is the size of RSA keys in real use?**
    Real-world RSA keys are typically **2048 or 4096 bits**. **1024-bit RSA is deprecated** (considered too weak for new systems). NIST recommends **at least 2048 bits** until at least 2030, and **3072 or 4096 bits** for longer-term security. The TLS 1.3 standard uses 2048+ bit keys.

23. **Why are large prime numbers used in RSA?**
    Large primes are used because **factoring `n = p × q` is computationally infeasible when `p` and `q` are large** (e.g., 1024-bit primes giving a 2048-bit modulus). With small primes, anyone could quickly factor `n`, recover `phi(n)`, compute `d`, and break the encryption. Security depends entirely on the prime size.

24. **What is Euler's totient function?**
    **Euler's totient function `phi(n)`** counts the **positive integers up to `n` that are coprime to `n`**. For prime `p`, `phi(p) = p - 1`. For two distinct primes `p` and `q`, `phi(pq) = (p-1)(q-1)`. Euler's theorem (basis of RSA): **`a^phi(n) ≡ 1 (mod n)`** for `gcd(a, n) = 1`.

25. **What is Fermat's Little Theorem (relation to RSA)?**
    **Fermat's Little Theorem** states: if `p` is prime, then **`a^(p-1) ≡ 1 (mod p)`** for any `a` not divisible by `p`. Euler generalized this for composite `n`: **`a^phi(n) ≡ 1 (mod n)`**. This is the **mathematical foundation of RSA's correctness** — it's why `(m^e)^d ≡ m (mod n)` works.

26. **What is modular exponentiation?**
    **Modular exponentiation** is the operation of **computing `(base^exp) mod m` efficiently** using the **square-and-multiply algorithm**. It avoids computing the huge intermediate value `base^exp` (which could have millions of digits) by **applying mod at each step**. Time complexity: O(log exp) — very fast.

27. **Why use modular exponentiation instead of normal power?**
    Without modular exponentiation, computing `m^e` for large `e` would produce **astronomically huge intermediate numbers** (overflowing any data type). For example, with 2048-bit RSA, `m^e` could have **~10^600 digits!** Modular exponentiation keeps numbers within `[0, n-1]`, making the computation feasible.

### Program-Specific
28. **What language is used in this program?**
    The program is implemented in **C++**. C++ has `long long` for moderately large integers, but for real RSA (2048+ bits), you need a **bignum library** like **GMP, OpenSSL BN, or Java's BigInteger**. Our small-number example just demonstrates the concept.

29. **What input does the program take?**
    The program takes **three inputs**: **(1)** a prime number `p`, **(2)** another prime number `q`, and **(3)** a plaintext message `m` (as an integer less than `n = p×q`). The program checks that `p` and `q` are prime, generates the keys, and encrypts/decrypts `m`.

30. **Which data type stores big numbers in this program?**
    Our program uses **`long long`** (64-bit signed integer, range up to ~9.2 × 10^18). This is enough for small primes (~10000) for educational purposes, but **woefully inadequate for real RSA** (which needs 2048+ bit numbers — about 617 digits).

31. **What does the `modPow` function do?**
    `modPow(base, exp, mod)` **computes `(base^exp) mod m` efficiently** using the **square-and-multiply algorithm** — looping over the binary representation of `exp`, squaring at each step and multiplying when an exponent bit is 1. Time complexity is O(log exp), making it usable for very large exponents.

32. **What does `gcd()` use?**
    The `gcd()` function uses **Euclid's algorithm** — the recursive identity **`gcd(a, b) = gcd(b, a mod b)`** with base case `gcd(a, 0) = a`. This algorithm dates back to **Euclid (~300 BCE)** and is one of the oldest algorithms still in use, running in O(log(min(a, b))) time.

33. **What does `modInverse()` find?**
    `modInverse(e, phi)` **finds `d` such that `(e × d) mod phi = 1`**. Our implementation uses **brute force** (iterate `d = 1, 2, ...` until the condition holds) — fine for small numbers but inefficient. Real RSA implementations use the **Extended Euclidean Algorithm**, which is O(log phi).

### Security and Concepts
34. **Can RSA be broken?**
    RSA can theoretically be broken **only if the modulus `n` can be factored** into its primes `p` and `q`. For **2048-bit `n`, factoring is currently infeasible** with classical computers (estimated to take longer than the age of the universe). However, **quantum computers running Shor's algorithm could break RSA in polynomial time** — driving the move toward post-quantum cryptography.

35. **What is a digital signature?**
    A **digital signature** is a cryptographic technique to **verify the authenticity and integrity** of a digital message — proving who signed it and that it hasn't been tampered with. It's the digital equivalent of a handwritten signature but provides much stronger guarantees (non-repudiation). Used in software updates, contracts, certificates, etc.

36. **How does RSA digital signature work?**
    To sign: the **sender hashes the message** (e.g., with SHA-256) and **encrypts the hash with their private key** — producing the signature. To verify: the **receiver decrypts the signature with the sender's public key** to get the hash, then **hashes the message** themselves and compares. If they match, the signature is valid.

37. **What is hybrid encryption?**
    **Hybrid encryption** combines **asymmetric and symmetric** ciphers: the receiver's RSA public key is used to **encrypt a small symmetric key (e.g., AES-256 key)**, and that AES key is used to **encrypt the actual data** (which is typically large). Combines the **convenience** of asymmetric (no shared key needed) with the **speed** of symmetric.

38. **What attacks exist on RSA?**
    RSA attacks include: **(1) Integer factorization** (the main one — currently infeasible for 2048+ bits), **(2) Chosen-ciphertext attacks** (defeated by **OAEP padding**), **(3) Timing attacks** (exploit decryption time variations — defeated by constant-time implementations), **(4) Coppersmith's attack** (small `e` and short messages), **(5) Side-channel attacks** (power, EM emissions). Quantum attack: **Shor's algorithm** (future threat).

39. **What is PKI?**
    **PKI (Public Key Infrastructure)** is the **system of policies, hardware, software, and trusted authorities (CAs)** that manages **digital certificates** to associate public keys with identities. PKI enables HTTPS, code signing, email signing, and authenticated communications. The most common element you see is **TLS certificates** issued by Certificate Authorities like Let's Encrypt, DigiCert, etc.

40. **Where is RSA used in real life?**
    RSA is used in **HTTPS/TLS** (key exchange and certificates), **Digital signatures** (signed software, PDFs, emails), **PGP/GPG** (encrypted email), **SSH** (public-key authentication), **VPNs** (key exchange), **Cryptocurrency** (some wallets), **Smart cards**, **Code signing** (Windows updates, app stores), and **Government PKI systems**. Most TLS uses RSA or ECC for key exchange.

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Bruce Schneier – *Applied Cryptography*
- Rivest, Shamir, Adleman – *A Method for Obtaining Digital Signatures and Public-Key Cryptosystems* (1978)
- Atul Kahate – *Cryptography and Network Security*
