from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad
import base64

def encrypt(message, key):
    cipher = DES.new(key, DES.MODE_ECB)
    
    padded_text = pad(message.encode(), DES.block_size)
    
    encrypted_bytes = cipher.encrypt(padded_text)
    
    encrypted_text = base64.b64encode(encrypted_bytes).decode()
    
    return encrypted_text


def decrypt(encrypted_text, key):
    
    cipher = DES.new(key, DES.MODE_ECB)
    
    encrypted_bytes = base64.b64decode(encrypted_text)
    
    decrypted_padded = cipher.decrypt(encrypted_bytes)
    
    decrypted_bytes = unpad(decrypted_padded, DES.block_size)
    
    decrypted_text = decrypted_bytes.decode()
    
    return decrypted_text
    
    
    
    
message = "Hello World"
key = b"JavaDES8"

print("=== DES Encryption and Decryption ===")
print("Original Message :", message)
print("Key              :", key.decode())


# Encrypt
encrypted = encrypt(message, key)
print("Encrypted Text   :", encrypted)

# Decrypt
decrypted = decrypt(encrypted, key)
print("Decrypted Text   :", decrypted)
