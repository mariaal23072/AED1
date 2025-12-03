f = open("log.txt","r")

'''
line = f.readline() #leer linea a linea

while line:
    print(line)
    line = f.readline()
'''

for line in f:
    print(line)


f.close()

from modulo import fun
