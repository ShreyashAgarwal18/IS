def gcd(a,b):
    while b != 0:
        a,b = b,a % b
        
    return a

p = 3
q = 11

n = p*q

phi = (p-1) * (q-1)

e = 7


for i in range(1 , phi):
    if(e*i) % phi == 1:
        d = i
        break
    
    
msg = int(input("Enter message: "))

cipher = (msg ** e) % n
print("Encrypted msg: ", cipher)


plain = (cipher ** d) % n
print("Decrypted msg: ", plain)



