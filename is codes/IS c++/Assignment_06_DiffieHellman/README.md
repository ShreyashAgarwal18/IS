# Assignment 6 – Diffie-Hellman Key Exchange (HTML + JavaScript)

## Problem Statement
Implement the **Diffie–Hellman Key Exchange** mechanism using **HTML and JavaScript**. The end user is one party (**Alice**) and the JavaScript application is the other party (**Bob**).

---

## 1. Aim
To implement the **Diffie-Hellman Key Exchange Algorithm** in HTML + JavaScript and demonstrate how two parties can agree on a shared secret key over an insecure channel without ever sending the key itself.

---

## 2. Theory (Simple)

### What is Diffie-Hellman?
**Diffie-Hellman (DH)** is a method for two parties to **safely agree on a secret key** while communicating over a **public (insecure) channel**. It was invented in **1976 by Whitfield Diffie and Martin Hellman** — the world's first published public-key protocol.

It does **not** encrypt messages — it only helps two people **share the same secret key**, which they can then use with a symmetric cipher like AES.

### The Idea (Color-Mixing Analogy)
Imagine Alice and Bob want to share a secret colour, but anyone watching can see what they exchange.

1. Both publicly agree on a starting **yellow** colour.
2. Alice secretly picks **red** and mixes → orange. She sends **orange** to Bob.
3. Bob secretly picks **blue** and mixes → green. He sends **green** to Alice.
4. Alice mixes her secret red with Bob's green → **brown**.
5. Bob mixes his secret blue with Alice's orange → **brown**.

Both reach the same secret **brown**, but an eavesdropper (who saw only yellow, orange and green) cannot easily reconstruct it.

DH replaces "colours and mixing" with **modular exponentiation**.

### How DH Works (Math)

**Public values (known to everyone):**
- `p` – a large prime number
- `g` – a generator (small base, e.g., 2 or 5)

**Step 1 – Alice picks a secret `a`** (private)
- Alice computes: `A = g^a mod p`
- Alice sends **A** to Bob.

**Step 2 – Bob picks a secret `b`** (private)
- Bob computes: `B = g^b mod p`
- Bob sends **B** to Alice.

**Step 3 – Both compute the shared secret:**
- Alice: `S = B^a mod p`
- Bob:   `S = A^b mod p`

Both end up with the **same value S** because:
```
B^a mod p = (g^b)^a mod p = g^(a*b) mod p
A^b mod p = (g^a)^b mod p = g^(a*b) mod p
```

### Worked Example
Public: `p = 23`, `g = 5`
Alice: secret `a = 6` → `A = 5^6 mod 23 = 8`
Bob:   secret `b = 15` → `B = 5^15 mod 23 = 19`
Shared:
- Alice → `19^6 mod 23 = 2`
- Bob   → `8^15 mod 23 = 2`

Both get **shared secret = 2**.

### Why is DH Secure?
An eavesdropper sees `p, g, A, B`. To find the secret, they must solve:
> "Given g, p, and `g^a mod p`, find `a`."

This is the **Discrete Logarithm Problem**, which is **computationally infeasible** for large primes (typically 2048-bit).

---

## 3. Algorithm

```
1. Both parties agree on public values: prime p and generator g.
2. Alice picks a private secret a; computes A = g^a mod p; sends A to Bob.
3. Bob picks a private secret b; computes B = g^b mod p; sends B to Alice.
4. Alice computes shared key: S = B^a mod p
5. Bob computes shared key:   S = A^b mod p
6. Both now share the same secret key S without ever transmitting it.
```

---

## 4. Files
- `index.html` – page layout and form fields
- `style.css`  – simple styling (Alice = pink box, Bob = green result box)
- `script.js`  – modPow function and Diffie-Hellman logic
- `README.md`  – this file

### How to Run
1. Open `index.html` in any web browser (double-click or right-click → Open With).
2. Enter the public values `p` and `g` (defaults: 23 and 5).
3. Enter Alice's secret `a`.
4. Click **Start Key Exchange** — Bob's secret is generated randomly.
5. The page shows public keys exchanged, both computed secrets, and confirms they match.

---

## 5. Sample Output
```
Public values: p = 23,  g = 5
Alice's secret a = 6
Bob's secret   b = 15  (randomly chosen)

Alice sends: A = 5^6 mod 23 = 8
Bob sends:   B = 5^15 mod 23 = 19

Alice computes: S = 19^6 mod 23 = 2
Bob computes:   S = 8^15 mod 23  = 2

Shared Secret Key = 2  (Match!)
```

---

## 6. Observation
1. Both parties end up with the **same shared key** without ever transmitting it.
2. Even if an attacker captures `p`, `g`, `A`, and `B`, they cannot easily compute the secret.
3. Each run produces a **different shared key** because Bob's secret `b` is random.
4. Diffie-Hellman provides **only key agreement** — not encryption or authentication.
5. JavaScript's `BigInt` is used to handle large numbers safely.

---

## 7. Conclusion
We successfully implemented the **Diffie-Hellman Key Exchange** in HTML + JavaScript. The user (Alice) and the browser (Bob) independently compute the **same shared secret key** without ever transmitting it, proving the elegance of public-key key agreement.

---

## 8. Strengths and Weaknesses

### Strengths
- Allows safe key sharing over insecure channels.
- Forms the basis of modern protocols like TLS, SSH, IPsec.
- Mathematically simple yet powerful.

### Weaknesses
- **No authentication** – vulnerable to **Man-in-the-Middle (MITM)** attack (an attacker can pretend to be Bob to Alice and Alice to Bob).
- Requires large primes (≥ 2048 bits) for real security.
- Needs to be combined with digital signatures or certificates to prevent MITM.

---

## 9. Viva Questions (40)

### Basic Theory
1. **What is Diffie-Hellman?**
   **Diffie-Hellman (DH)** is a **cryptographic key exchange protocol** that allows two parties to **safely agree on a shared secret key** over an **insecure (public) channel** — even if an eavesdropper sees all the messages exchanged. It was the first published public-key cryptographic protocol and revolutionized cryptography.

2. **Who invented Diffie-Hellman?**
   Diffie-Hellman was invented by **Whitfield Diffie and Martin Hellman** in **1976** (with major contributions from Ralph Merkle), published in their landmark paper *"New Directions in Cryptography"*. They received the **2015 Turing Award** for this work — often called the most important cryptographic invention of the 20th century.

3. **Is DH used for encryption or key exchange?**
   DH is used **only for key exchange (key agreement)**, not for encryption itself. After both parties derive the **shared secret**, they use it as a key for a **symmetric cipher** (like AES) to actually encrypt their messages. DH establishes the shared secret; AES (or similar) does the encryption.

4. **Is DH symmetric or asymmetric?**
   DH is **asymmetric** — each party has a **secret (private) value** and exchanges a **derived (public) value**. It's part of public-key cryptography. However, the **output** of DH is a single **shared symmetric key** — typically used afterward with symmetric encryption.

5. **What is a key exchange algorithm?**
   A **key exchange algorithm** is a protocol that **enables two (or more) parties to securely share a secret key** that they can later use for symmetric encryption. The challenge is doing this **over an insecure channel** where eavesdroppers may be listening. Examples: **Diffie-Hellman, Elliptic-Curve DH (ECDH), RSA key transport**.

6. **What problem does DH solve?**
   DH solves the **key distribution problem** — historically, two parties had to **physically meet** or use a **trusted courier** to share an encryption key. DH allows them to **derive the same secret key without ever transmitting it**, even over public channels — making secure communication scalable on the internet.

7. **Does DH provide authentication?**
   **No** — DH provides **only key agreement**, not authentication. There's no way for Alice to verify she's actually exchanging keys with Bob (and not an impostor). This is why DH alone is **vulnerable to Man-in-the-Middle attacks** — and why TLS combines DH with **digital signatures or certificates** for authentication.

8. **What attack is DH vulnerable to without authentication?**
   Without authentication, DH is vulnerable to **Man-in-the-Middle (MITM)** attack. An attacker (Mallory) can intercept Alice's and Bob's messages, **establish separate DH keys with each**, and then **decrypt and re-encrypt** every message between them — silently reading and modifying communications. Defended against by combining DH with certificates or signatures.

9. **What mathematical problem makes DH secure?**
   DH security relies on the **Discrete Logarithm Problem (DLP)**: **given `g`, `p`, and `g^x mod p`, find `x`**. While computing `g^x mod p` is easy (modular exponentiation), the **reverse (finding `x`) is computationally hard** for large prime `p`. This asymmetry is the foundation of DH's security.

10. **What is a generator (g) in DH?**
    A **generator `g`** is a number (typically small, like 2 or 5) used as the **base of the modular exponentiation**. Mathematically, `g` should be a **primitive root modulo p** — meaning `g^1, g^2, ..., g^(p-1)` mod p produce all values from 1 to p-1. Both parties must agree on `p` and `g` publicly.

### DH Math
11. **What is the formula Alice uses to compute her public key?**
    Alice computes her public key as **`A = g^a mod p`**, where `a` is her **secret** (private) integer chosen randomly. She **sends `A` to Bob** over the public channel — anyone can see `A`, but they cannot easily recover `a` from it (DLP).

12. **What is the formula Bob uses?**
    Bob computes his public key as **`B = g^b mod p`**, where `b` is his **secret** integer. He **sends `B` to Alice**. Now Alice has `B` and Bob has `A` — both derived from secrets that neither party shared.

13. **How does Alice compute the shared secret?**
    Alice computes the **shared secret** as **`S = B^a mod p`** — using Bob's public key `B` and her own secret `a`. This works because `S = (g^b)^a mod p = g^(a×b) mod p`.

14. **How does Bob compute the shared secret?**
    Bob computes the **shared secret** as **`S = A^b mod p`** — using Alice's public key `A` and his own secret `b`. This gives `S = (g^a)^b mod p = g^(a×b) mod p` — **the same value Alice computed**.

15. **Why do both parties get the same secret?**
    Because of the **commutative property of exponents**: **`(g^a)^b = (g^b)^a = g^(a×b) mod p`**. Both Alice and Bob compute `g^(a×b) mod p` independently — even though neither knows the other's secret, they end up with the same value.

16. **What is the public information in DH?**
    The **public information** in DH is: **`p` (prime)**, **`g` (generator)**, **`A = g^a mod p` (Alice's public key)**, and **`B = g^b mod p` (Bob's public key)**. An eavesdropper sees all of these but **cannot derive the shared secret** (assuming DLP is hard).

17. **What is the secret information in DH?**
    The **secret information** in DH consists of: **`a` (Alice's private secret)**, **`b` (Bob's private secret)**, and **`S` (the final shared secret key)**. None of these are ever transmitted — `a` and `b` stay with their respective parties, and `S` is independently derived by both.

18. **What is `mod p`?**
    **`mod p` (modulo p)** is the **mathematical operation that returns the remainder** after dividing by `p`. For example, `17 mod 5 = 2` (since 17 = 3×5 + 2). All DH calculations are done modulo `p`, keeping results in the range `[0, p-1]`. This **modular arithmetic** is what makes the discrete log problem hard.

19. **Why is a large prime p needed?**
    A **large prime `p`** is needed to make the **Discrete Logarithm Problem** computationally infeasible. With small `p` (e.g., 23 like in our example), an attacker can solve DLP by brute force in seconds. With large `p` (2048+ bits), the best known algorithms (Number Field Sieve) take longer than the age of the universe.

20. **What is the typical size of p in real systems?**
    In real systems, **`p` is typically 2048 bits or larger** (about 600+ decimal digits). NIST recommends **at least 2048 bits** for current security and **3072 or 4096 bits** for long-term protection. Standard DH groups (RFC 3526, RFC 7919) are predefined for interoperability.

### Program-Specific
21. **What technologies are used in this program?**
    The program uses **HTML** (form structure), **CSS** (styling — colored boxes for Alice/result), and **JavaScript** (DH math, button handler, dynamic display). It's a **client-side single-page web app** that runs entirely in the browser without a server.

22. **Who plays Alice in this program?**
    **Alice is the user** — entering her secret integer `a` in the form. The user types in the inputs (`p`, `g`, `a`) and clicks the button to start the exchange. This is what makes the demo interactive.

23. **Who plays Bob?**
    **Bob is the JavaScript code** running in the browser. When the button is clicked, JS picks Bob's secret `b` randomly, computes Bob's public key `B`, and computes Bob's shared secret. The browser plays the second party in the protocol.

24. **How is Bob's secret generated?**
    Bob's secret `b` is generated **randomly** using JavaScript's `Math.random()`, scaled to the range **`[2, p-2]`**. This is **not cryptographically secure** randomness — fine for a demo but real systems use **`crypto.getRandomValues()`** (or server-side CSPRNGs).

25. **What JavaScript feature handles large numbers?**
    **`BigInt`** — a built-in JavaScript type that can represent arbitrarily large integers (no max value limit, unlike standard `Number` which is limited to 2^53). Essential for cryptographic operations involving large numbers like modular exponentiation. Created by appending `n` (e.g., `5n`) or via `BigInt()`.

26. **What does the `modPow()` function do?**
    `modPow(base, exp, mod)` **computes `(base^exp) mod m` efficiently** using the **square-and-multiply algorithm**. Time complexity is O(log exp). It avoids computing the huge intermediate value `base^exp` (which could overflow even `BigInt` for large exponents). This is the workhorse function for any DH or RSA implementation.

27. **Why use square-and-multiply?**
    Square-and-multiply **avoids computing the huge intermediate `base^exp`** by **applying mod at each step** while iterating over the binary representation of `exp`. For 2048-bit numbers, naive computation would require billions of multiplications; square-and-multiply needs only ~2048. **Both faster and avoids overflow**.

28. **What does the user input?**
    The user inputs **three values**: the **prime `p`** (e.g., 23), the **generator `g`** (e.g., 5), and **Alice's secret `a`** (e.g., 6). The form has default values pre-filled so it works on the first click.

29. **What does the program output?**
    The program outputs: **Alice's public key `A`**, **Bob's public key `B`** (and Bob's randomly chosen secret `b`), **Alice's computed shared secret**, **Bob's computed shared secret**, and a **confirmation that they match** (the final shared key).

30. **Why are A, B and the secret displayed in a different color?**
    The **color coding** is for **clarity and learning**: **Alice's box is pink** (representing her side), the **result box is green** (representing successful agreement). It helps users visually track which values belong to whom.

### Concepts
31. **What is the difference between DH and RSA?**
    **DH** does **only key exchange** — it produces a shared secret key between two parties. **RSA** can do **encryption, decryption, AND digital signatures** — it's a more general-purpose asymmetric algorithm. In TLS, DH (or ECDH) is preferred for key exchange because it provides **forward secrecy**, while RSA is sometimes used for authentication.

32. **Can DH be used to encrypt messages?**
    **No** — DH itself doesn't encrypt anything. It produces a **shared secret key** that **both parties then use with a symmetric cipher** (like AES) to encrypt actual messages. So DH + AES is a typical hybrid setup. To directly encrypt with DH-style math, use the **ElGamal cryptosystem** (a related but distinct algorithm).

33. **What is the Discrete Logarithm Problem?**
    The **Discrete Logarithm Problem (DLP)** asks: given `g`, `p`, and `y = g^x mod p`, **find `x`**. While computing `g^x mod p` is easy (polynomial time), **finding `x` is believed to be hard** for large `p`. The best known algorithms (Pollard's rho, NFS) are sub-exponential. **Quantum computers can solve DLP in polynomial time** via Shor's algorithm.

34. **What is forward secrecy?**
    **Forward Secrecy (also called Perfect Forward Secrecy, PFS)** is a property where **compromise of long-term keys does not compromise past session keys**. Each session uses a fresh, ephemeral key (e.g., new DH exponents). So even if an attacker later steals the server's private key, they **cannot decrypt past recorded conversations**. Modern TLS (especially TLS 1.3) provides forward secrecy by default.

35. **What is Ephemeral Diffie-Hellman (DHE/ECDHE)?**
    **Ephemeral Diffie-Hellman (DHE for finite-field DH, ECDHE for elliptic-curve DH)** is a variant where **fresh DH key pairs are generated for every session** (rather than reusing long-term keys). This provides **forward secrecy**. It's the **standard in modern TLS** — every HTTPS connection uses ephemeral DH to derive session keys.

36. **What is Elliptic-Curve Diffie-Hellman (ECDH)?**
    **ECDH** is DH performed on **elliptic curves over finite fields** instead of the multiplicative group of integers mod p. It provides **the same security with much smaller key sizes** (256-bit ECC ≈ 3072-bit RSA security). **Faster, less bandwidth, less battery use**. Popular curves: **Curve25519, P-256, P-384**. Used in TLS 1.3, Signal, WhatsApp, modern SSH.

37. **How can MITM attacks on DH be prevented?**
    To prevent MITM, DH is **combined with authentication**: **(1) Digital Signatures** — each party signs their DH public key with their long-term private key (verified via certificates). **(2) Pre-shared keys** for password-authenticated DH (e.g., SRP, OPAQUE). **(3) Certificate-based authentication** (used in TLS). DH alone is NOT secure against MITM.

38. **Where is DH used in real life?**
    DH/ECDH is used in **HTTPS/TLS 1.3** (mandatory for forward secrecy), **SSH** (key exchange protocols), **IPsec/IKE** (VPNs), **End-to-end encrypted messaging** (Signal, WhatsApp, Telegram, iMessage), **WireGuard VPN**, **Tor**, and many other secure communication systems. It's the **foundation of secure session establishment** on the internet.

39. **Difference between key exchange and key transport?**
    **Key Exchange (DH)**: both parties **collaboratively compute** the shared key — neither party sends the actual key. Provides forward secrecy. **Key Transport (RSA)**: one party **picks the key and encrypts it** with the other's public key, sending it over. **Faster but no forward secrecy** (if private key is later stolen, all past traffic decrypts).

40. **Why is DH considered a foundation of modern cryptography?**
    DH was the **first published public-key cryptographic protocol** (1976), demonstrating that **secrets could be shared without prior physical exchange**. This idea fundamentally changed cryptography from a niche military discipline to the **basis of all modern internet security** (HTTPS, SSH, VPNs, end-to-end encryption). Diffie & Hellman won the 2015 Turing Award largely for this contribution.

---

## 10. References
- William Stallings – *Cryptography and Network Security*
- Bruce Schneier – *Applied Cryptography*
- Diffie & Hellman – *New Directions in Cryptography* (1976)
- Atul Kahate – *Cryptography and Network Security*
