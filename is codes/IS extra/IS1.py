text = "Hello World"
mask = 127

print("Text: ", text)
print("Mask: ", mask)
print()
print(f"{'Char':<6} {'Ascii':<6} {'And':<8} {'Xor':<8}")
print("-" * 40)


for ch in text:
    ascii_value = ord(ch)
    print(f"{ch:<6} {ascii_value:<6} {ascii_value & mask:<8} {ascii_value^mask:<8}")
    
print()
encrypted = ''.join(chr(ord(c) ^ mask) for c in text)
print("Encrypted: ", repr(encrypted))

print("-"*20)
original = ''.join(chr(ord(c) ^ mask) for c in encrypted)
print("original: ", original)

    