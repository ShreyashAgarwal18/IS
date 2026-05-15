def des_encrypt(text, key):
    encrypted = ""
    
    for i in range(len(text)):
        
        x = ord(text[i]) ^ ord(key[i % len(key)])
        
        x = (x << 1) % 256
        
        encrypted += chr(x)
        
    return encrypted


def des_decrypt(cipher, key):
    
    decrypted = ""
    
    for i in range(len(cipher)):
        
        x = (ord(cipher[i]) >> 1)
        
        x = x ^ ord(key[i % len(key)])
        
        decrypted += chr(x)
        
    
    return decrypted

text = input("Enter Plain Text : ")
key = input("Enter Key : ")

cipher = des_encrypt(text, key)

print("\nEncrypted Text :", repr(cipher))

plain = des_decrypt(cipher, key)

print("Decrypted Text :", plain)

