KEY = 6

def encrypt(text):
    text = text.upper().replace(" ", "")
    while len(text) % KEY != 0:
        text += "X"
        
    rows = len(text) // KEY
    
    grid = []
    
    for r in range(rows):
        grid.append(list(text[r * KEY : r * KEY + KEY]))
        
    cipher = ""
    for c in range(KEY):
        for r in range(rows):
            cipher += grid[r][c]
    return cipher


def decrypt(cipher):
    rows = len(cipher) // KEY
    
    grid = [['' for _ in range(KEY)] for _ in range(rows)]
    index = 0
    for c in range(KEY):
        for r in range(rows):
            grid[r][c] = cipher[index]
            index += 1
            
    plain = ""
    for r in range(rows):
        for c in range(KEY):
            plain += grid[r][c]
    return plain


plain_text = "HELLO WORLD THIS IS TRANSPOSITION"

print("Transposition technique: ")
print("Plain text: ", plain_text)
print("Key: ", KEY)

encrypted = encrypt(plain_text)
print("Encrypted: ", repr(encrypted))

decrypted = decrypt(encrypted)
print("Decrypted: ", decrypted)
     