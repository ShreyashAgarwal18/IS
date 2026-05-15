// Assignment 1 - Information Security
// Perform AND and XOR with 127 on each character of "Hello World"

#include <iostream>   // for cin, cout (input/output)
#include <cstring>    // for strlen() function
using namespace std;

int main() {
    // Step 1: Declare the string and the key
    char str[] = "Hello World";   // our input string (each char is 1 byte)
    int n = strlen(str);          // n = number of characters in the string (here 11)
    int key = 127;                // the key value used for AND/XOR operations
                                  // 127 in binary = 01111111 (7 ones, MSB = 0)

    // Step 2: Display the original string and key
    cout << "Original String : " << str << endl;
    cout << "Key             : " << key << endl << endl;

    // Step 3: AND Operation
    // AND keeps a bit only if BOTH bits are 1.
    // Doing (char & 127) clears the 8th bit, keeps the lower 7 bits same.
    cout << "----- AND Operation with 127 -----" << endl;
    for (int i = 0; i < n; i++) {              // loop through every character
        char result = str[i] & key;            // bitwise AND of character and 127
        cout << str[i] << " & " << key << " = " << (int)result   // print as number
             << "  (" << result << ")" << endl;                   // and as character
    }

    // Step 4: XOR Operation
    // XOR gives 1 only when bits are DIFFERENT.
    // Doing (char ^ 127) flips the lower 7 bits.
    // XOR is REVERSIBLE: XORing twice with the same key gives the original back.
    cout << "\n----- XOR Operation with 127 -----" << endl;
    for (int i = 0; i < n; i++) {              // loop through every character
        char result = str[i] ^ key;            // bitwise XOR of character and 127
        cout << str[i] << " ^ " << key << " = " << (int)result   // print as number
             << "  (" << result << ")" << endl;                   // and as character
                                                                  // (may be unreadable
                                                                  // for control chars)
    }

    return 0;   // end of program
}
