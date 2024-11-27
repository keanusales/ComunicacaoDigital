from crc import encoder, decoder

data, gen = 0b1101011011, 0b10011
res1 = encoder(data, gen)
print(f"Resposta: {bin(res1)}")
res2 = decoder(res1, gen)
print(f"Checagem: {bin(res2)}")