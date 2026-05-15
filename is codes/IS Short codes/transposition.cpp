#include <iostream>
#include <string>
using namespace std;

// Encryption
string encrypt(string text, int key) {
    string cipher = "";

    for (int col = 0; col < key; col++) {
        for (int i = col; i < text.length(); i += key) {
            cipher += text[i];
        }
    }
    return cipher;
}

// Decryption
string decrypt(string cipher, int key) {
    int len = cipher.length();
    string text(len, ' ');

    int index = 0;

    for (int col = 0; col < key; col++) {
        for (int i = col; i < len; i += key) {
            text[i] = cipher[index++];
        }
    }
    return text;
}

int main() {
    int choice, key;
    string text;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // clear buffer

        switch (choice) {
        case 1:
            cout << "Enter message: ";
            getline(cin, text);

            cout << "Enter key (number of columns): ";
            cin >> key;

            cout << "\nEncrypted Text: " << encrypt(text, key) << endl;
            break;

        case 2:
            cout << "Enter cipher text: ";
            getline(cin, text);

            cout << "Enter key (number of columns): ";
            cin >> key;

            cout << "\nDecrypted Text: " << decrypt(text, key) << endl;
            break;

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }


    } while (choice != 3);

    return 0;
}
/* ===== MENU =====
1. Encrypt
2. Decrypt
3. Exit
Enter your choice: 1
Enter message: hello
Enter key (number of columns): 2

Encrypted Text: hloel

===== MENU =====
1. Encrypt
2. Decrypt
3. Exit
Enter your choice: 2
Enter cipher text: hloel
Enter key (number of columns): 2

Decrypted Text: hello
*/