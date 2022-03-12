import csv
import sys
import random
import re

# Ensure correct argv line

if len(sys.argv)!= 3:
    print("Error !")
    sys.exit(1)


sequences = {}
with open(sys.argv[1]) as file:
    reader = csv.reader(file)
    for row in reader:
        DNAs = row
        DNAs.pop(0)
        break
with open (sys.argv[2]) as dnafile:
    dna = dnafile.read()
    for row in dnafile:
        dnalist = row

for item in DNAs:
    sequences[item] = 0

for STR in DNAs:
    groups = re.findall(rf'(?:{STR})+', dna)
    #print(groups)
    if len(groups) > 0:
        largest = max(groups, key=len)
        maximum = len(largest)//len(STR)
    #print(len(largest)//len(STR))
    #print(maximum)
        sequences[STR] += maximum
#print(sequences)



with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        match = 0
        for DNA in sequences:
            if sequences[DNA] == int(row[DNA]):
                match += 1
        if match == len(sequences):
            print(row['name'])
            exit()
    print("No match")