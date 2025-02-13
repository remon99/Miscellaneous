import math
import random
import string

def permute_string(plaintext, positions):
    permuted_string = [''] * len(plaintext)

    for i, pos in enumerate(positions):
        permuted_string[i] = plaintext[pos]

    return ''.join(permuted_string)

def find_row_and_column(n):
    row = math.isqrt(n)
    col = n // row
    if n % row != 0:
        col += 1
    return row, col

def gk(n):
    return random.sample(range(n), n)

def enc(plaintext,key):
    ciphertext = []
    total_length = row * col

    current_len = len(plaintext)
    pad_needed = total_length - current_len
    if pad_needed > 0 :
        pad = string.ascii_lowercase[-pad_needed:]
        plaintext+=pad
    segments = [plaintext[i*col : (i+1)*col] for i in range(row)]
    print(segments)
    for i in range(col):
      pos = key.index(i)
      for j in range(row):
        ciphertext.append(segments[j][pos])
    #print(ciphertext)
    return ''.join(ciphertext)

def dec(ciphertext,key):
    plaintext = []
    segments = [ciphertext[i*row : (i+1)*row] for i in range(col)]
    print(segments)
    transposed = [''.join(row) for row in zip(*segments)]
    print(transposed)

    for i in range(len(transposed)):
        s = transposed[i]
        temp = permute_string(s,key)
        #print(temp)
        plaintext.append(temp)

    return ''.join(plaintext)

    return 0


plaintext = 'attackispostponeduntiltwoam'
row, col = find_row_and_column(len(plaintext))
print(row,col)
key = gk(col)
print(key)
ciphertext = enc(plaintext,key)
pln= dec(ciphertext,key)
print(pln)
