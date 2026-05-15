// Assignment 2 - Information Security
// Encryption and Decryption using Transposition Technique (Columnar)

#include <iostream>   // for cin, cout
#include <cstring>    // for strlen()
using namespace std;

int main() {
    // ============ INPUT SECTION ============
    char msg[100];    // array to store the input message (max 100 characters)
    int key;          // key = number of columns in the matrix

    cout << "Enter the message : ";
    cin.getline(msg, 100);    // read the full line including spaces

    cout << "Enter the key (number of columns) : ";
    cin >> key;

    int len = strlen(msg);                // length of the message
    int rows = (len + key - 1) / key;     // number of rows needed (ceiling division)
                                          // example: len=10, key=4 -> rows=3

    // 2D matrix to hold the message in row-column form
    char matrix[20][20];
    int k = 0;        // index for the message string

    // ============ STEP 1: Fill the matrix ROW BY ROW ============
    // We write the plain message into the matrix, going left to right, top to bottom.
    // If message is shorter than rows*key, we add 'x' as padding.
    for (int i = 0; i < rows; i++) {              // outer loop = rows
        for (int j = 0; j < key; j++) {           // inner loop = columns
            if (k < len)
                matrix[i][j] = msg[k++];          // place next character
            else
                matrix[i][j] = 'x';               // padding character
        }
    }

    // ============ STEP 2: Show the matrix ============
    cout << "\nMatrix (filled row-wise):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // ============ STEP 3: ENCRYPTION ============
    // Read the matrix COLUMN BY COLUMN to produce the ciphertext.
    // This shuffles the order of letters → encryption.
    char cipher[100];
    k = 0;
    for (int j = 0; j < key; j++) {               // outer loop = columns first
        for (int i = 0; i < rows; i++) {          // inner loop = rows inside each col
            cipher[k++] = matrix[i][j];           // pick character from current column
        }
    }
    cipher[k] = '\0';                             // end the cipher string

    cout << "\nEncrypted Message : " << cipher << endl;

    // ============ STEP 4: DECRYPTION ============
    // To decrypt, do the OPPOSITE:
    // (a) Write the ciphertext into the matrix COLUMN BY COLUMN.
    char decryptMatrix[20][20];
    k = 0;
    for (int j = 0; j < key; j++) {               // fill column by column
        for (int i = 0; i < rows; i++) {
            decryptMatrix[i][j] = cipher[k++];
        }
    }

    // (b) Now read the matrix ROW BY ROW to recover the original message.
    char plain[100];
    k = 0;
    for (int i = 0; i < rows; i++) {              // read row by row
        for (int j = 0; j < key; j++) {
            plain[k++] = decryptMatrix[i][j];
        }
    }
    plain[k] = '\0';                              // end the plain string

    cout << "Decrypted Message : " << plain << endl;

    return 0;   // end of program
}
