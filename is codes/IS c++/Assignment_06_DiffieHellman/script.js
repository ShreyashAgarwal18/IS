// Assignment 6 - Diffie-Hellman Key Exchange
// Alice = the user (enters values), Bob = this JavaScript program

// ============================================================
// Helper: Modular exponentiation -> (base^exp) mod m
// Avoids huge numbers by taking mod at every step.
// ============================================================
function modPow(base, exp, mod) {
    let result = 1n;
    base = BigInt(base) % BigInt(mod);
    exp = BigInt(exp);
    mod = BigInt(mod);
    while (exp > 0n) {
        if (exp % 2n === 1n) {              // if exponent is odd
            result = (result * base) % mod;
        }
        exp = exp / 2n;                     // halve the exponent
        base = (base * base) % mod;         // square the base
    }
    return result;
}

// ============================================================
// Main function: runs when "Start Key Exchange" is clicked
// ============================================================
function startExchange() {

    // -------- Step 1: Read public values (p, g) --------
    const p = parseInt(document.getElementById("p").value);
    const g = parseInt(document.getElementById("g").value);

    // -------- Step 2: Read Alice's secret --------
    const a = parseInt(document.getElementById("a").value);

    // -------- Step 3: Bob picks his own random secret 'b' --------
    // (random integer between 2 and p-2)
    const b = Math.floor(Math.random() * (p - 3)) + 2;

    // -------- Step 4: Both compute their public keys --------
    // A = g^a mod p   (Alice -> Bob)
    // B = g^b mod p   (Bob   -> Alice)
    const A = modPow(g, a, p);
    const B = modPow(g, b, p);

    // -------- Step 5: Each computes the shared secret --------
    // Alice does:  S = B^a mod p
    // Bob does:    S = A^b mod p
    // Both should be equal!
    const aliceSecret = modPow(B, a, p);
    const bobSecret   = modPow(A, b, p);

    // -------- Step 6: Display all the values on the page --------
    document.getElementById("A").textContent = A.toString();
    document.getElementById("B").textContent = B.toString();
    document.getElementById("b").textContent = b;
    document.getElementById("aliceSecret").textContent = aliceSecret.toString();
    document.getElementById("bobSecret").textContent = bobSecret.toString();

    // -------- Step 7: Compare and show final message --------
    const finalMsg = document.getElementById("finalMsg");
    if (aliceSecret === bobSecret) {
        finalMsg.textContent =
            "Shared Secret Key = " + aliceSecret.toString() + " (Match!)";
        finalMsg.style.color = "#2ecc71";
    } else {
        finalMsg.textContent = "Mismatch! Something went wrong.";
        finalMsg.style.color = "red";
    }

    // Show the result box (hidden by default)
    document.getElementById("result").style.display = "block";
}
