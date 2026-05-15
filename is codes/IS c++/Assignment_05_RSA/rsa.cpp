// Assignment 5 - Information Security
// Implementation of RSA Algorithm (Asymmetric / Public-Key Cryptography)
//
// RSA is based on the difficulty of factoring large numbers.
// Steps:
//   1. Pick two prime numbers p and q
//   2. Compute n = p*q  and  phi = (p-1)*(q-1)
//   3. Choose e such that gcd(e, phi) = 1
//   4. Compute d such that (d * e) mod phi = 1
//   5. Public key  = (e, n)   Private key = (d, n)
//   6. Encrypt: c = m^e mod n
//   7. Decrypt: m = c^d mod n

#include <iostream>
using namespace std;

// ============================================================
// HELPER 1 : GCD (Greatest Common Divisor) using Euclid's algo
// ============================================================
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// ============================================================
// HELPER 2 : Modular exponentiation -> (base^exp) mod m
// Uses square-and-multiply method (fast and avoids overflow)
// ============================================================
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)              // if exponent is odd
            result = (result * base) % mod;
        exp = exp / 2;                 // halve the exponent
        base = (base * base) % mod;    // square the base
    }
    return result;
}

// ============================================================
// HELPER 3 : Modular inverse of e mod phi
// Find d such that (d * e) mod phi == 1
// (Simple brute-force search — fine for small numbers)
// ============================================================
long long modInverse(long long e, long long phi) {
    for (long long d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;        // no inverse found (shouldn't happen if e is coprime)
}

// ============================================================
// HELPER 4 : Check if a number is prime
// ============================================================
bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// ============================================================
// MAIN : RSA Key Generation, Encryption, Decryption
// ============================================================
int main() {
    long long p, q;

    // -------- STEP 1: Take two prime numbers from the user --------
    cout << "=== RSA Algorithm ===\n\n";
    cout << "Enter two prime numbers (p and q) : ";
    cin >> p >> q;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Error: Both numbers must be prime!\n";
        return 1;
    }

    // -------- STEP 2: Compute n and phi(n) --------
    long long n = p * q;                  // modulus
    long long phi = (p - 1) * (q - 1);    // Euler's totient

    cout << "\nn   = p * q       = " << n << endl;
    cout << "phi = (p-1)*(q-1) = " << phi << endl;

    // -------- STEP 3: Choose e (public exponent) --------
    // e must satisfy: 1 < e < phi  AND  gcd(e, phi) = 1
    long long e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    cout << "e   (public)      = " << e << endl;

    // -------- STEP 4: Compute d (private exponent) --------
    long long d = modInverse(e, phi);
    cout << "d   (private)     = " << d << endl;

    cout << "\nPublic Key  : (e=" << e << ", n=" << n << ")" << endl;
    cout << "Private Key : (d=" << d << ", n=" << n << ")" << endl;

    // -------- STEP 5: Take plaintext message --------
    long long m;
    cout << "\nEnter the plaintext message (number < " << n << ") : ";
    cin >> m;

    if (m >= n) {
        cout << "Error: message must be less than n!\n";
        return 1;
    }

    // -------- STEP 6: Encryption  c = m^e mod n --------
    long long c = modPow(m, e, n);
    cout << "\nEncrypted (cipher) = " << c << endl;

    // -------- STEP 7: Decryption  m = c^d mod n --------
    long long decrypted = modPow(c, d, n);
    cout << "Decrypted (plain)  = " << decrypted << endl;

    cout << "\nNote: Decrypted should match the original message.\n";
    return 0;
}
