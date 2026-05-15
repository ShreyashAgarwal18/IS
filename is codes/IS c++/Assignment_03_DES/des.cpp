// Assignment 3 - Information Security
// Implementation of DES (Data Encryption Standard) Algorithm
//
// DES takes a 64-bit plaintext block and a 64-bit key (56 bits used)
// and produces a 64-bit ciphertext block using 16 rounds of Feistel.

#include <iostream>
#include <string>
#include <bitset>
using namespace std;

// =========================================================
// SECTION 1 : DES STANDARD TABLES
// (these are fixed values defined in the DES specification)
// =========================================================

// Initial Permutation (IP) - rearranges 64 input bits
int IP[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};

// Final Permutation (IP^-1) - inverse of IP
int FP[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};

// Expansion E - expands 32 bits to 48 bits
int E[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};

// Permutation P - end of f-function
int P[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};

// PC-1: 64-bit key -> 56-bit (drops parity bits)
int PC1[56] = {
 57,49,41,33,25,17,9, 1,58,50,42,34,26,18,
 10,2,59,51,43,35,27, 19,11,3,60,52,44,36,
 63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
 14,6,61,53,45,37,29,  21,13,5,28,20,12,4
};

// PC-2: 56-bit -> 48-bit round key
int PC2[48] = {
 14,17,11,24,1,5,   3,28,15,6,21,10,
 23,19,12,4,26,8,   16,7,27,20,13,2,
 41,52,31,37,47,55, 30,40,51,45,33,48,
 44,49,39,56,34,53, 46,42,50,36,29,32
};

// Left shifts per round (key schedule)
int SHIFTS[16] = {1,1,2,2,2,2,2,2, 1,2,2,2,2,2,2,1};

// Eight S-boxes (each 4 rows x 16 cols) - core non-linear substitution
int S[8][4][16] = {
 {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
  {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
  {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
  {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
 {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
  {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
  {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
  {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
 {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
  {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
  {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
  {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
 {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
  {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
  {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
  {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
 {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
  {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
  {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
  {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
 {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
  {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
  {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
  {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
 {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
  {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
  {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
  {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
 {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
  {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
  {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
  {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// =========================================================
// SECTION 2 : HELPER FUNCTIONS
// =========================================================

// Apply a permutation table to a binary string
string permute(string input, int *table, int n) {
    string output = "";
    for (int i = 0; i < n; i++)
        output += input[table[i] - 1];     // table values are 1-based
    return output;
}

// Left circular shift of a binary string by 'shifts' positions
string leftShift(string input, int shifts) {
    return input.substr(shifts) + input.substr(0, shifts);
}

// XOR two binary strings of the same length
string xorStrings(string a, string b) {
    string result = "";
    for (int i = 0; i < (int)a.size(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

// Convert hex string to binary string
string hexToBin(string hex) {
    string bin = "";
    for (char c : hex) {
        int val = (c >= '0' && c <= '9') ? c - '0' : (toupper(c) - 'A' + 10);
        bin += bitset<4>(val).to_string();
    }
    return bin;
}

// Convert binary string to hex string
string binToHex(string bin) {
    string hex = "";
    for (int i = 0; i < (int)bin.size(); i += 4) {
        bitset<4> b(bin.substr(i, 4));
        int val = (int)b.to_ulong();
        hex += (val < 10) ? ('0' + val) : ('A' + val - 10);
    }
    return hex;
}

// =========================================================
// SECTION 3 : KEY SCHEDULE
// Generate 16 round keys (each 48 bits) from the main 64-bit key
// =========================================================
void generateKeys(string key, string roundKeys[16]) {
    // Step 1: Apply PC-1 to get 56-bit key
    string key56 = permute(key, PC1, 56);

    // Step 2: Split into two halves of 28 bits each
    string C = key56.substr(0, 28);
    string D = key56.substr(28, 28);

    // Step 3: For each round, do left shifts and apply PC-2
    for (int i = 0; i < 16; i++) {
        C = leftShift(C, SHIFTS[i]);
        D = leftShift(D, SHIFTS[i]);
        roundKeys[i] = permute(C + D, PC2, 48);   // 48-bit round key
    }
}

// =========================================================
// SECTION 4 : F-FUNCTION (the heart of DES)
// Takes 32-bit half + 48-bit round key -> produces 32-bit output
// =========================================================
string fFunction(string R, string roundKey) {
    // Step 1: Expand 32-bit R to 48 bits using E table
    string expanded = permute(R, E, 48);

    // Step 2: XOR with the round key
    string xored = xorStrings(expanded, roundKey);

    // Step 3: Apply 8 S-boxes (each takes 6 bits, gives 4 bits)
    string sboxOutput = "";
    for (int i = 0; i < 8; i++) {
        string block = xored.substr(i * 6, 6);
        int row = (block[0] - '0') * 2 + (block[5] - '0');             // 1st & 6th bit
        int col = (block[1] - '0') * 8 + (block[2] - '0') * 4 +
                  (block[3] - '0') * 2 + (block[4] - '0');             // middle 4 bits
        sboxOutput += bitset<4>(S[i][row][col]).to_string();
    }

    // Step 4: Apply P permutation to the 32-bit output
    return permute(sboxOutput, P, 32);
}

// =========================================================
// SECTION 5 : DES ENCRYPT / DECRYPT
// =========================================================
string desProcess(string input, string roundKeys[16], bool encrypt) {
    // Step 1: Apply Initial Permutation
    string ip = permute(input, IP, 64);

    // Step 2: Split into Left (32 bits) and Right (32 bits)
    string L = ip.substr(0, 32);
    string R = ip.substr(32, 32);

    // Step 3: 16 Feistel rounds
    for (int i = 0; i < 16; i++) {
        // For decryption, use round keys in REVERSE order
        string key = encrypt ? roundKeys[i] : roundKeys[15 - i];

        string newR = xorStrings(L, fFunction(R, key));
        L = R;          // new Left = old Right
        R = newR;       // new Right = old Left XOR f(old Right, key)
    }

    // Step 4: Combine R+L (note the swap!) and apply Final Permutation
    return permute(R + L, FP, 64);
}

// =========================================================
// SECTION 6 : MAIN DRIVER
// =========================================================
int main() {
    // Plaintext (16 hex chars = 64 bits) and Key (16 hex chars = 64 bits)
    string plaintextHex = "123456ABCD132536";
    string keyHex       = "AABB09182736CCDD";

    cout << "=== DES Algorithm Demonstration ===\n\n";
    cout << "Plaintext (hex) : " << plaintextHex << endl;
    cout << "Key       (hex) : " << keyHex << endl;

    // Convert hex inputs to 64-bit binary strings
    string plaintext = hexToBin(plaintextHex);
    string key       = hexToBin(keyHex);

    // Generate 16 round keys from the main key
    string roundKeys[16];
    generateKeys(key, roundKeys);

    // ENCRYPTION
    string cipher = desProcess(plaintext, roundKeys, true);
    cout << "\nCiphertext (hex): " << binToHex(cipher) << endl;

    // DECRYPTION
    string decrypted = desProcess(cipher, roundKeys, false);
    cout << "Decrypted (hex) : " << binToHex(decrypted) << endl;

    cout << "\nNote: Decrypted should match the original plaintext.\n";
    return 0;
}
