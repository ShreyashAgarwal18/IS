def aes_encrypt(text,key):
    encrypted = ""
    
    for i in range(len(text)):
        ch = chr(ord(text[i]) ^ ord(key[i%len(key)]))
        encrypted += ch
        
        
    return encrypted



def aes_decrypt(cipher, key):
    decrypted = ""
    
    for i in range(len(cipher)):
        ch = chr(ord(cipher[i]) ^ ord(key[i%len(key)]))
        decrypted += ch
        
        
    return decrypted



plain_text = input("Enter Plain Text : ")
key = input("Enter Key : ")

cipher_text = aes_encrypt(plain_text, key)

print("\nEncrypted Text :", repr(cipher_text))

decrypted_text = aes_decrypt(cipher_text, key)

print("Decrypted Text :", decrypted_text)